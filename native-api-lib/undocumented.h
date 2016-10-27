#pragma once

//	Note that the following definitions are undocumented altogether, or are documented only in WDK files that do not co-exist with usermode SDK files
namespace Nt
{
    typedef struct _KEY_BASIC_INFORMATION {
        LARGE_INTEGER LastWriteTime;
        ULONG   TitleIndex;
        ULONG   NameLength;
        WCHAR   Name[1];            // Variable length string
    } KEY_BASIC_INFORMATION, *PKEY_BASIC_INFORMATION;

    typedef struct _KEY_NODE_INFORMATION {
        LARGE_INTEGER LastWriteTime;
        ULONG   TitleIndex;
        ULONG   ClassOffset;
        ULONG   ClassLength;
        ULONG   NameLength;
        WCHAR   Name[1];            // Variable length string
    //          Class[1];           // Variable length string not declared
    } KEY_NODE_INFORMATION, *PKEY_NODE_INFORMATION;

    typedef struct _KEY_FULL_INFORMATION {
        LARGE_INTEGER LastWriteTime;
        ULONG   TitleIndex;
        ULONG   ClassOffset;
        ULONG   ClassLength;
        ULONG   SubKeys;
        ULONG   MaxNameLen;
        ULONG   MaxClassLen;
        ULONG   Values;
        ULONG   MaxValueNameLen;
        ULONG   MaxValueDataLen;
        WCHAR   Class[1];           // Variable length
    } KEY_FULL_INFORMATION, *PKEY_FULL_INFORMATION;

    typedef enum _KEY_INFORMATION_CLASS {
        KeyBasicInformation,
        KeyNodeInformation,
        KeyFullInformation,
        KeyNameInformation,
        KeyCachedInformation,
        KeyFlagsInformation,
        KeyVirtualizationInformation,
        KeyHandleTagsInformation,
        KeyTrustInformation,
        MaxKeyInfoClass  // MaxKeyInfoClass should always be the last enum
    } KEY_INFORMATION_CLASS;

    typedef struct _KEY_VALUE_BASIC_INFORMATION {
        ULONG   TitleIndex;
        ULONG   Type;
        ULONG   NameLength;
        WCHAR   Name[1];            // Variable size
    } KEY_VALUE_BASIC_INFORMATION, *PKEY_VALUE_BASIC_INFORMATION;

    typedef struct _KEY_VALUE_FULL_INFORMATION {
        ULONG   TitleIndex;
        ULONG   Type;
        ULONG   DataOffset;
        ULONG   DataLength;
        ULONG   NameLength;
        WCHAR   Name[1];            // Variable size
    //          Data[1];            // Variable size data not declared
    } KEY_VALUE_FULL_INFORMATION, *PKEY_VALUE_FULL_INFORMATION;

    typedef struct _KEY_VALUE_PARTIAL_INFORMATION {
        ULONG   TitleIndex;
        ULONG   Type;
        ULONG   DataLength;
        _Field_size_bytes_(DataLength) UCHAR Data[1]; // Variable size
    } KEY_VALUE_PARTIAL_INFORMATION, *PKEY_VALUE_PARTIAL_INFORMATION;

    typedef struct _KEY_VALUE_PARTIAL_INFORMATION_ALIGN64 {
        ULONG   Type;
        ULONG   DataLength;
        _Field_size_bytes_(DataLength) UCHAR   Data[1];            // Variable size
    } KEY_VALUE_PARTIAL_INFORMATION_ALIGN64, *PKEY_VALUE_PARTIAL_INFORMATION_ALIGN64;

    typedef enum _KEY_VALUE_INFORMATION_CLASS {
        KeyValueBasicInformation,
        KeyValueFullInformation,
        KeyValuePartialInformation,
        KeyValueFullInformationAlign64,
        KeyValuePartialInformationAlign64,
        MaxKeyValueInfoClass  // MaxKeyValueInfoClass should always be the last enum
    } KEY_VALUE_INFORMATION_CLASS;

    typedef enum _FILE_INFORMATION_CLASS {
        FileDirectoryInformation = 1,
        FileFullDirectoryInformation,   // 2
        FileBothDirectoryInformation,   // 3
        FileBasicInformation,           // 4
        FileStandardInformation,        // 5
        FileInternalInformation,        // 6
        FileEaInformation,              // 7
        FileAccessInformation,          // 8
        FileNameInformation,            // 9
        FileRenameInformation,          // 10
        FileLinkInformation,            // 11
        FileNamesInformation,           // 12
        FileDispositionInformation,     // 13
        FilePositionInformation,        // 14
        FileFullEaInformation,          // 15
        FileModeInformation,            // 16
        FileAlignmentInformation,       // 17
        FileAllInformation,             // 18
        FileAllocationInformation,      // 19
        FileEndOfFileInformation,       // 20
        FileAlternateNameInformation,   // 21
        FileStreamInformation,          // 22
        FilePipeInformation,            // 23
        FilePipeLocalInformation,       // 24
        FilePipeRemoteInformation,      // 25
        FileMailslotQueryInformation,   // 26
        FileMailslotSetInformation,     // 27
        FileCompressionInformation,     // 28
        FileObjectIdInformation,        // 29
        FileCompletionInformation,      // 30
        FileMoveClusterInformation,     // 31
        FileQuotaInformation,           // 32
        FileReparsePointInformation,    // 33
        FileNetworkOpenInformation,     // 34
        FileAttributeTagInformation,    // 35
        FileTrackingInformation,        // 36
        FileIdBothDirectoryInformation, // 37
        FileIdFullDirectoryInformation, // 38
        FileValidDataLengthInformation, // 39
        FileShortNameInformation,       // 40
        FileIoCompletionNotificationInformation, // 41
        FileIoStatusBlockRangeInformation,       // 42
        FileIoPriorityHintInformation,           // 43
        FileSfioReserveInformation,              // 44
        FileSfioVolumeInformation,               // 45
        FileHardLinkInformation,                 // 46
        FileProcessIdsUsingFileInformation,      // 47
        FileNormalizedNameInformation,           // 48
        FileNetworkPhysicalNameInformation,      // 49
        FileIdGlobalTxDirectoryInformation,      // 50
        FileIsRemoteDeviceInformation,           // 51
        FileUnusedInformation,                   // 52
        FileNumaNodeInformation,                 // 53
        FileStandardLinkInformation,             // 54
        FileRemoteProtocolInformation,           // 55
        FileRenameInformationBypassAccessCheck,  // 56
        FileLinkInformationBypassAccessCheck,    // 57
        FileVolumeNameInformation,               // 58
        FileIdInformation,                       // 59
        FileIdExtdDirectoryInformation,          // 60
        FileReplaceCompletionInformation,        // 61
        FileHardLinkFullIdInformation,           // 62
        FileIdExtdBothDirectoryInformation,      // 63
        FileDispositionInformationEx,            // 64
        FileRenameInformationEx,                 // 65
        FileRenameInformationExBypassAccessCheck, // 66
        FileMaximumInformation
    } FILE_INFORMATION_CLASS, *PFILE_INFORMATION_CLASS;

    typedef struct _FILE_DIRECTORY_INFORMATION {
        ULONG NextEntryOffset;
        ULONG FileIndex;
        LARGE_INTEGER CreationTime;
        LARGE_INTEGER LastAccessTime;
        LARGE_INTEGER LastWriteTime;
        LARGE_INTEGER ChangeTime;
        LARGE_INTEGER EndOfFile;
        LARGE_INTEGER AllocationSize;
        ULONG FileAttributes;
        ULONG FileNameLength;
        WCHAR FileName[1];
    } FILE_DIRECTORY_INFORMATION, *PFILE_DIRECTORY_INFORMATION;

    typedef struct _FILE_FULL_DIR_INFORMATION {
        ULONG NextEntryOffset;
        ULONG FileIndex;
        LARGE_INTEGER CreationTime;
        LARGE_INTEGER LastAccessTime;
        LARGE_INTEGER LastWriteTime;
        LARGE_INTEGER ChangeTime;
        LARGE_INTEGER EndOfFile;
        LARGE_INTEGER AllocationSize;
        ULONG FileAttributes;
        ULONG FileNameLength;
        ULONG EaSize;
        WCHAR FileName[1];
    } FILE_FULL_DIR_INFORMATION, *PFILE_FULL_DIR_INFORMATION;

    typedef struct _FILE_ID_FULL_DIR_INFORMATION {
        ULONG NextEntryOffset;
        ULONG FileIndex;
        LARGE_INTEGER CreationTime;
        LARGE_INTEGER LastAccessTime;
        LARGE_INTEGER LastWriteTime;
        LARGE_INTEGER ChangeTime;
        LARGE_INTEGER EndOfFile;
        LARGE_INTEGER AllocationSize;
        ULONG FileAttributes;
        ULONG FileNameLength;
        ULONG EaSize;
        LARGE_INTEGER FileId;
        WCHAR FileName[1];
    } FILE_ID_FULL_DIR_INFORMATION, *PFILE_ID_FULL_DIR_INFORMATION;

    typedef struct _FILE_BOTH_DIR_INFORMATION {
        ULONG NextEntryOffset;
        ULONG FileIndex;
        LARGE_INTEGER CreationTime;
        LARGE_INTEGER LastAccessTime;
        LARGE_INTEGER LastWriteTime;
        LARGE_INTEGER ChangeTime;
        LARGE_INTEGER EndOfFile;
        LARGE_INTEGER AllocationSize;
        ULONG FileAttributes;
        ULONG FileNameLength;
        ULONG EaSize;
        CCHAR ShortNameLength;
        WCHAR ShortName[12];
        WCHAR FileName[1];
    } FILE_BOTH_DIR_INFORMATION, *PFILE_BOTH_DIR_INFORMATION;

    typedef struct _FILE_ID_BOTH_DIR_INFORMATION {
        ULONG NextEntryOffset;
        ULONG FileIndex;
        LARGE_INTEGER CreationTime;
        LARGE_INTEGER LastAccessTime;
        LARGE_INTEGER LastWriteTime;
        LARGE_INTEGER ChangeTime;
        LARGE_INTEGER EndOfFile;
        LARGE_INTEGER AllocationSize;
        ULONG FileAttributes;
        ULONG FileNameLength;
        ULONG EaSize;
        CCHAR ShortNameLength;
        WCHAR ShortName[12];
        LARGE_INTEGER FileId;
        WCHAR FileName[1];
    } FILE_ID_BOTH_DIR_INFORMATION, *PFILE_ID_BOTH_DIR_INFORMATION;

    typedef struct _FILE_NAMES_INFORMATION {
        ULONG NextEntryOffset;
        ULONG FileIndex;
        ULONG FileNameLength;
        WCHAR FileName[1];
    } FILE_NAMES_INFORMATION, *PFILE_NAMES_INFORMATION;

    typedef struct _FILE_ID_GLOBAL_TX_DIR_INFORMATION {
        ULONG NextEntryOffset;
        ULONG FileIndex;
        LARGE_INTEGER CreationTime;
        LARGE_INTEGER LastAccessTime;
        LARGE_INTEGER LastWriteTime;
        LARGE_INTEGER ChangeTime;
        LARGE_INTEGER EndOfFile;
        LARGE_INTEGER AllocationSize;
        ULONG FileAttributes;
        ULONG FileNameLength;
        LARGE_INTEGER FileId;
        GUID LockingTransactionId;
        ULONG TxInfoFlags;
        WCHAR FileName[1];
    } FILE_ID_GLOBAL_TX_DIR_INFORMATION, *PFILE_ID_GLOBAL_TX_DIR_INFORMATION;

#define FILE_ID_GLOBAL_TX_DIR_INFO_FLAG_WRITELOCKED         0x00000001
#define FILE_ID_GLOBAL_TX_DIR_INFO_FLAG_VISIBLE_TO_TX       0x00000002
#define FILE_ID_GLOBAL_TX_DIR_INFO_FLAG_VISIBLE_OUTSIDE_TX  0x00000004

    typedef struct _FILE_ID_EXTD_DIR_INFORMATION {
        ULONG NextEntryOffset;
        ULONG FileIndex;
        LARGE_INTEGER CreationTime;
        LARGE_INTEGER LastAccessTime;
        LARGE_INTEGER LastWriteTime;
        LARGE_INTEGER ChangeTime;
        LARGE_INTEGER EndOfFile;
        LARGE_INTEGER AllocationSize;
        ULONG FileAttributes;
        ULONG FileNameLength;
        ULONG EaSize;
        ULONG ReparsePointTag;
        FILE_ID_128 FileId;
        WCHAR FileName[1];
    } FILE_ID_EXTD_DIR_INFORMATION, *PFILE_ID_EXTD_DIR_INFORMATION;

    typedef struct _FILE_ID_EXTD_BOTH_DIR_INFORMATION {
        ULONG NextEntryOffset;
        ULONG FileIndex;
        LARGE_INTEGER CreationTime;
        LARGE_INTEGER LastAccessTime;
        LARGE_INTEGER LastWriteTime;
        LARGE_INTEGER ChangeTime;
        LARGE_INTEGER EndOfFile;
        LARGE_INTEGER AllocationSize;
        ULONG FileAttributes;
        ULONG FileNameLength;
        ULONG EaSize;
        ULONG ReparsePointTag;
        FILE_ID_128 FileId;
        CCHAR ShortNameLength;
        WCHAR ShortName[12];
        WCHAR FileName[1];
    } FILE_ID_EXTD_BOTH_DIR_INFORMATION, *PFILE_ID_EXTD_BOTH_DIR_INFORMATION;

    typedef struct _FILE_OBJECTID_INFORMATION {
        LONGLONG FileReference;
        UCHAR ObjectId[16];
        union {
            struct {
                UCHAR BirthVolumeId[16];
                UCHAR BirthObjectId[16];
                UCHAR DomainId[16];
            } DUMMYSTRUCTNAME;
            UCHAR ExtendedInfo[48];
        } DUMMYUNIONNAME;
    } FILE_OBJECTID_INFORMATION, *PFILE_OBJECTID_INFORMATION;

    typedef enum _OBJECT_INFORMATION_CLASS {
        ObjectBasicInformation,
        ObjectNameInformation,
        ObjectTypeInformation,
        ObjectAllInformation,
        ObjectDataInformation
    } OBJECT_INFORMATION_CLASS, *POBJECT_INFORMATION_CLASS;
}
