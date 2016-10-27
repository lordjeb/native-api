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

    typedef enum _OBJECT_INFORMATION_CLASS {
        ObjectBasicInformation,
        ObjectNameInformation,
        ObjectTypeInformation,
        ObjectAllInformation,
        ObjectDataInformation
    } OBJECT_INFORMATION_CLASS, *POBJECT_INFORMATION_CLASS;
}
