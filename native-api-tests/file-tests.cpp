#include "CppUnitTest.h"
#include <Windows.h>
#include <ShlObj.h>
#include "ntdll.h"
#include "handle.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace nativeapitests
{
    TEST_CLASS(FileTests)
    {
    public:
        static Nt::NtApi _nt;
        std::wstring _directoryName;
        UNICODE_STRING _DirectoryName;
        OBJECT_ATTRIBUTES _DirectoryObjectAttributes;

        TEST_METHOD_INITIALIZE(TestMethodSetUp)
        {
            // Create directory for testing
            wchar_t* pProfileDirectory;
            Assert::AreEqual(S_OK, SHGetKnownFolderPath(FOLDERID_Profile, 0, nullptr, &pProfileDirectory));
            _directoryName = L"\\??\\" + std::wstring(pProfileDirectory) + L"\\NativeApiLibTests";
            CoTaskMemFree(pProfileDirectory);

            _nt.RtlInitUnicodeString(&_DirectoryName, _directoryName.c_str());
            InitializeObjectAttributes(&_DirectoryObjectAttributes, &_DirectoryName, OBJ_CASE_INSENSITIVE, nullptr, nullptr);

            Nt::unique_nt_handle dirHandle;
            IO_STATUS_BLOCK iosb;
            Assert::AreEqual(STATUS_SUCCESS, _nt.NtCreateFile(dirHandle.get_address_of(), FILE_GENERIC_WRITE, &_DirectoryObjectAttributes, &iosb, 0, FILE_ATTRIBUTE_DIRECTORY, 0, FILE_CREATE, FILE_DIRECTORY_FILE, nullptr, 0));
        }

        TEST_METHOD_CLEANUP(TestMethodCleanUp)
        {
            Assert::AreEqual(STATUS_SUCCESS, _nt.NtDeleteFile(&_DirectoryObjectAttributes));
        }

        TEST_METHOD(FileOperations)
        {
            auto filename = _directoryName + L"\\file.txt";
            UNICODE_STRING FileName;
            OBJECT_ATTRIBUTES FileObjectAttributes;

            _nt.RtlInitUnicodeString(&FileName, filename.c_str());
            InitializeObjectAttributes(&FileObjectAttributes, &FileName, OBJ_CASE_INSENSITIVE, nullptr, nullptr);

            Nt::unique_nt_handle fileHandle;
            IO_STATUS_BLOCK iosb;
            Assert::AreEqual(STATUS_SUCCESS, _nt.NtCreateFile(fileHandle.get_address_of(), FILE_ALL_ACCESS, &FileObjectAttributes, &iosb, 0, 0, 0, FILE_CREATE, FILE_DELETE_ON_CLOSE, nullptr, 0));

            Nt::unique_nt_handle dirHandle;
            Assert::AreEqual(STATUS_SUCCESS, _nt.NtCreateFile(dirHandle.get_address_of(), FILE_LIST_DIRECTORY | SYNCHRONIZE, &_DirectoryObjectAttributes, &iosb, 0, FILE_ATTRIBUTE_DIRECTORY, 0, FILE_OPEN, FILE_SYNCHRONOUS_IO_NONALERT | FILE_DIRECTORY_FILE, nullptr, 0));

            unsigned long bufferSize = 256;
            std::vector<BYTE> fileInformationBuffer(bufferSize);
            auto pValueFullInformation = reinterpret_cast<Nt::FILE_NAMES_INFORMATION*>(&fileInformationBuffer[0]);
            Assert::AreEqual(STATUS_SUCCESS, _nt.NtQueryDirectoryFile(dirHandle.get(), nullptr, nullptr, nullptr, &iosb, pValueFullInformation, bufferSize, Nt::FileNamesInformation, TRUE, nullptr, TRUE));
            std::wstring queriedFilename(pValueFullInformation->FileName, pValueFullInformation->FileNameLength / sizeof(wchar_t));
            Assert::AreEqual(L".", queriedFilename.c_str());
        }
    };

    Nt::NtApi FileTests::_nt;
}
