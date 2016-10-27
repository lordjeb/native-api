#include "CppUnitTest.h"
#include <stdio.h>
#include <Windows.h>
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
        static wchar_t _username[MAX_PATH + 1];
        static wchar_t _userSid[MAX_PATH + 1];
        wchar_t _keyName[MAX_PATH];
        UNICODE_STRING _KeyName;
        OBJECT_ATTRIBUTES _KeyObjectAttributes;

        TEST_CLASS_INITIALIZE(SetUp)
        {
            DWORD cchUsername = _countof(_username);
            SID_NAME_USE sidNameUse;
            PSID pSidBuffer = nullptr;
            DWORD cbSidBuffer = 0;
            wchar_t* pReferencedDomainName = nullptr;
            DWORD cchReferencedDomainName = 0;
            wchar_t* pStringSid = nullptr;

            __try
            {
                // Get the username and SID so we can get access to registry areas that we have rights to...
                Assert::AreNotEqual(FALSE, GetUserName(_username, &cchUsername));

                Assert::AreEqual(FALSE, LookupAccountName(nullptr, _username, nullptr, &cbSidBuffer, nullptr, &cchReferencedDomainName, &sidNameUse));
                Assert::AreEqual(122UL, GetLastError());

                pSidBuffer = new BYTE[ cbSidBuffer ];
                Assert::IsNotNull(pSidBuffer);

                pReferencedDomainName = new wchar_t[ cchReferencedDomainName ];
                Assert::IsNotNull(pReferencedDomainName);

                Assert::AreNotEqual(FALSE, LookupAccountName(nullptr, _username, pSidBuffer, &cbSidBuffer, pReferencedDomainName, &cchReferencedDomainName, &sidNameUse));

                Assert::AreNotEqual(FALSE, ConvertSidToStringSid(pSidBuffer, &pStringSid));

                wcscpy_s(_userSid, pStringSid);
            }
            __finally
            {
                if (pStringSid)
                {
                    LocalFree(pStringSid);
                }

                if (pReferencedDomainName)
                {
                    delete[] pReferencedDomainName;
                }

                if (pSidBuffer)
                {
                    delete[] pSidBuffer;
                }
            }
        }

        TEST_METHOD_INITIALIZE(TestMethodSetUp)
        {
            swprintf_s(_keyName, L"\\REGISTRY\\USER\\%s\\Software\\NativeApiLibTests", _userSid);
            _nt.RtlInitUnicodeString(&_KeyName, _keyName);
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

        TEST_METHOD(NotifyTester)
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
    wchar_t RegistryTests::_username[MAX_PATH + 1] = { 0 };
    wchar_t RegistryTests::_userSid[MAX_PATH + 1] = { 0 };
}
