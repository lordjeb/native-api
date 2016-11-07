#include "CppUnitTest.h"
#include <Windows.h>
#include "ntdll.h"
#include "handle.hpp"
#include <sddl.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace nativeapitests
{
    TEST_CLASS(WnfTests)
    {
    public:
        static Nt::NtApi _nt;
        //std::wstring _directoryName;
        //UNICODE_STRING _DirectoryName;
        //OBJECT_ATTRIBUTES _DirectoryObjectAttributes;

        //TEST_METHOD_INITIALIZE(TestMethodSetUp)
        //{
        //    // Create directory for testing
        //    wchar_t* pProfileDirectory;
        //    Assert::AreEqual(S_OK, SHGetKnownFolderPath(FOLDERID_Profile, 0, nullptr, &pProfileDirectory));
        //    _directoryName = L"\\??\\" + std::wstring(pProfileDirectory) + L"\\NativeApiLibTests";
        //    CoTaskMemFree(pProfileDirectory);

        //    _nt.RtlInitUnicodeString(&_DirectoryName, _directoryName.c_str());
        //    InitializeObjectAttributes(&_DirectoryObjectAttributes, &_DirectoryName, OBJ_CASE_INSENSITIVE, nullptr, nullptr);

        //    Nt::unique_nt_handle dirHandle;
        //    IO_STATUS_BLOCK iosb;
        //    Assert::AreEqual(STATUS_SUCCESS, _nt.NtCreateFile(dirHandle.get_address_of(), FILE_GENERIC_WRITE, &_DirectoryObjectAttributes, &iosb, 0, FILE_ATTRIBUTE_DIRECTORY, 0, FILE_CREATE, FILE_DIRECTORY_FILE, nullptr, 0));
        //}

        //TEST_METHOD_CLEANUP(TestMethodCleanUp)
        //{
        //    Assert::AreEqual(STATUS_SUCCESS, _nt.NtDeleteFile(&_DirectoryObjectAttributes));
        //}

        TEST_METHOD(FileOperations)
        {
            PSECURITY_DESCRIPTOR pSD = nullptr;
            auto br = ConvertStringSecurityDescriptorToSecurityDescriptor(L"D:(A;CI;0x1f0013;;;SY)(A;CI;0x1f0013;;;S-1-15-2-1)(A;CI;0x1f0013;;;BA)", SDDL_REVISION_1, &pSD, nullptr);
            Assert::AreEqual(TRUE, br);

            Nt::WNF_STATE_NAME StateName;
            auto status = _nt.NtCreateWnfStateName(&StateName, Nt::WnfPersistentStateName, Nt::WnfDataScopeSystem, FALSE, nullptr, 4, pSD);
            Assert::AreEqual(STATUS_SUCCESS, status);
            if (NT_SUCCESS(status))
            {
                status = _nt.NtDeleteWnfStateName(&StateName);
                //Assert::AreEqual(STATUS_SUCCESS, status);
            }

            if (pSD)
            {
                LocalFree(pSD);
            }
        }
    };

    Nt::NtApi WnfTests::_nt;
}
