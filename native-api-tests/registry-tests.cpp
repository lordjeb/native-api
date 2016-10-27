#include "CppUnitTest.h"
#include <stdio.h>
#include <Windows.h>
#include <lmcons.h>
#include <sddl.h>
#include "ntdll.h"
#include "handle.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace nativeapitests
{
    VOID NTAPI SetEventApcRoutine(_In_ PVOID ApcContext, _In_ PIO_STATUS_BLOCK IoStatusBlock, _In_ ULONG Reserved)
    {
        SetEvent(*static_cast<PHANDLE>(ApcContext));
    }

    TEST_CLASS(RegistryTests)
    {
    public:
        static Nt::NtApi _nt;
        static std::wstring _userSid;
        std::wstring _keyName;
        UNICODE_STRING _KeyName;
        OBJECT_ATTRIBUTES _KeyObjectAttributes;

        TEST_CLASS_INITIALIZE(SetUp)
        {
            // Get the username and SID so we can get a name for registry areas that we have rights to...
            //

            wchar_t username[UNLEN + 1];
            DWORD cchUsername = _countof(username);
            Assert::AreNotEqual(FALSE, GetUserName(username, &cchUsername));

            SID_NAME_USE sidNameUse;
            DWORD cbSidBuffer = 0;
            DWORD cchReferencedDomainName = 0;
            Assert::AreEqual(FALSE, LookupAccountName(nullptr, username, nullptr, &cbSidBuffer, nullptr, &cchReferencedDomainName, &sidNameUse));
            Assert::AreEqual(122UL, GetLastError());

            std::vector<BYTE> sidBuffer(cbSidBuffer);
            std::vector<wchar_t> referencedDomainName(cchReferencedDomainName);
            Assert::AreNotEqual(FALSE, LookupAccountName(nullptr, username, &sidBuffer[0], &cbSidBuffer, &referencedDomainName[0], &cchReferencedDomainName, &sidNameUse));

            wchar_t* pStringSid;
            Assert::AreNotEqual(FALSE, ConvertSidToStringSid(&sidBuffer[0], &pStringSid));
            _userSid = pStringSid;
            LocalFree(pStringSid);
        }

        TEST_METHOD_INITIALIZE(TestMethodSetUp)
        {
            // Create registry key for testing
            _keyName = L"\\REGISTRY\\USER\\" + _userSid + L"\\Software\\NativeApiLibTests";
            _nt.RtlInitUnicodeString(&_KeyName, _keyName.c_str());
            InitializeObjectAttributes(&_KeyObjectAttributes, &_KeyName, OBJ_CASE_INSENSITIVE, nullptr, nullptr);

            ULONG ulDisposition;
            Nt::unique_nt_handle keyHandle;
            Assert::AreEqual(STATUS_SUCCESS, _nt.NtCreateKey(keyHandle.get_address_of(), KEY_ALL_ACCESS, &_KeyObjectAttributes, 0, nullptr, REG_OPTION_VOLATILE, &ulDisposition));
        }

        TEST_METHOD_CLEANUP(TestMethodCleanUp)
        {
            Nt::unique_nt_handle keyHandle;
            Assert::AreEqual(STATUS_SUCCESS, _nt.NtOpenKey(keyHandle.get_address_of(), KEY_ALL_ACCESS, &_KeyObjectAttributes));
            Assert::AreEqual(STATUS_SUCCESS, _nt.NtDeleteKey(keyHandle.get()));
        }

        TEST_METHOD(ClosingInvalidHandleReturnsSuccess)
        {
            auto hTest = INVALID_HANDLE_VALUE;
            Assert::AreEqual(STATUS_SUCCESS, _nt.NtClose(hTest));
        }

        TEST_METHOD(ClosingNullHandleReturnsError)
        {
            HANDLE hTest = nullptr;
            Assert::AreEqual(STATUS_INVALID_HANDLE, _nt.NtClose(hTest));
        }

        TEST_METHOD(OpenKeySucceeds)
        {
            HANDLE hKey;
            Assert::AreEqual(STATUS_SUCCESS, _nt.NtOpenKey(&hKey, KEY_READ, &_KeyObjectAttributes));
        }

        TEST_METHOD(OpenKeyExFailsWhenBackupPrivilegeNotEnabled)
        {
            Nt::unique_nt_handle keyHandle;
            Assert::AreEqual(STATUS_ACCESS_DENIED, _nt.NtOpenKeyEx(keyHandle.get_address_of(), KEY_READ, &_KeyObjectAttributes, REG_OPTION_BACKUP_RESTORE));
        }

        TEST_METHOD(ValueOperations)
        {
            unsigned long bufferSize = 256;

            Nt::unique_nt_handle keyHandle;
            Assert::AreEqual(STATUS_SUCCESS, _nt.NtOpenKey(keyHandle.get_address_of(), KEY_ALL_ACCESS, &_KeyObjectAttributes));

            // Set
            UNICODE_STRING valueName = RTL_CONSTANT_STRING(L"TestValue");
            ULONG valueData = 42;
            Assert::AreEqual(STATUS_SUCCESS, _nt.NtSetValueKey(keyHandle.get(), &valueName, 0, REG_DWORD, &valueData, sizeof(valueData)));

            // Query
            std::vector<BYTE> valueInformationBuffer(bufferSize);
            auto pValueFullInformation = reinterpret_cast<Nt::KEY_VALUE_FULL_INFORMATION*>(&valueInformationBuffer[0]);
            ULONG cbInformation;
            Assert::AreEqual(STATUS_SUCCESS, _nt.NtQueryValueKey(keyHandle.get(), &valueName, Nt::KeyValueFullInformation, pValueFullInformation, bufferSize, &cbInformation));
            Assert::AreEqual(ULONG(REG_DWORD), pValueFullInformation->Type);
            Assert::AreEqual(ULONG(sizeof(DWORD)), pValueFullInformation->DataLength);

            // Enum
            Assert::AreEqual(STATUS_SUCCESS, _nt.NtEnumerateValueKey(keyHandle.get(), 0, Nt::KeyValueFullInformation, pValueFullInformation, bufferSize, &cbInformation));
            Assert::AreEqual(ULONG(REG_DWORD), pValueFullInformation->Type);

            Assert::AreEqual(STATUS_NO_MORE_ENTRIES, _nt.NtEnumerateValueKey(keyHandle.get(), 1, Nt::KeyValueFullInformation, pValueFullInformation, bufferSize, &cbInformation));


            // Delete
            Assert::AreEqual(STATUS_SUCCESS, _nt.NtDeleteValueKey(keyHandle.get(), &valueName));
        }

        TEST_METHOD(ChangeNotifications)
        {
            Nt::unique_nt_handle keyHandle;
            Assert::AreEqual(STATUS_SUCCESS, _nt.NtOpenKey(keyHandle.get_address_of(), KEY_ALL_ACCESS, &_KeyObjectAttributes));
            auto hEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
            IO_STATUS_BLOCK iosb;
            Assert::AreEqual(STATUS_PENDING, _nt.NtNotifyChangeKey(keyHandle.get(), nullptr, static_cast<PIO_APC_ROUTINE>(SetEventApcRoutine), &hEvent, &iosb, REG_NOTIFY_CHANGE_NAME | REG_NOTIFY_CHANGE_LAST_SET, TRUE, nullptr, 0, TRUE));

            UNICODE_STRING ValueName = RTL_CONSTANT_STRING(L"TestValue");
            Assert::AreEqual(STATUS_SUCCESS, _nt.NtSetValueKey(keyHandle.get(), &ValueName, 0, REG_SZ, ValueName.Buffer, ValueName.Length + sizeof(wchar_t)));

            // Cause the thread to enter an alterable state so that it can call the APC routine(s)
            Assert::AreEqual(static_cast<DWORD>(WAIT_IO_COMPLETION), SleepEx(0, TRUE));
            Assert::AreEqual(static_cast<DWORD>(WAIT_OBJECT_0), WaitForSingleObject(hEvent, INFINITE));
            Assert::AreEqual(STATUS_NOTIFY_ENUM_DIR, iosb.Status);
        }
    };

    Nt::NtApi RegistryTests::_nt;
    std::wstring RegistryTests::_userSid;
}
