#include "ntdll.h"


namespace Nt
{

    NtApi::NtApi()
        : m_hLib{ nullptr },
        m_pfnNtClose{ nullptr },
        m_pfnNtCreateFile{ nullptr },
        m_pfnNtCreateKey{ nullptr },
        m_pfnNtCreateKeyTransacted{ nullptr },
        m_pfnNtDeleteKey{ nullptr },
        m_pfnNtDeleteValueKey{ nullptr },
        m_pfnNtEnumerateKey{ nullptr },
        m_pfnNtEnumerateValueKey{ nullptr },
        m_pfnNtFlushKey{ nullptr },
        m_pfnNtNotifyChangeKey{ nullptr },
        m_pfnNtOpenFile{ nullptr },
        m_pfnNtOpenKey{ nullptr },
        m_pfnNtOpenKeyEx{ nullptr },
        m_pfnNtOpenKeyTransacted{ nullptr },
        m_pfnNtOpenKeyTransactedEx{ nullptr },
        m_pfnNtQueryKey{ nullptr },
        m_pfnNtQueryObject{ nullptr },
        m_pfnNtQueryValueKey{ nullptr },
        m_pfnNtSetValueKey{ nullptr }
    {
        m_hLib = LoadLibraryW(L"ntdll.dll");

        m_pfnNtClose = (PFN_NtClose)GetProcAddress(m_hLib, "NtClose");
        m_pfnNtCreateFile = (PFN_NtCreateFile)GetProcAddress(m_hLib, "NtCreateFile");
        m_pfnNtCreateKey = (PFN_NtCreateKey)GetProcAddress(m_hLib, "NtCreateKey");
        m_pfnNtCreateKeyTransacted = (PFN_NtCreateKeyTransacted)GetProcAddress(m_hLib, "NtCreateKeyTransacted");
        m_pfnNtDeleteKey = (PFN_NtDeleteKey)GetProcAddress(m_hLib, "NtDeleteKey");
        m_pfnNtDeleteValueKey = (PFN_NtDeleteValueKey)GetProcAddress(m_hLib, "NtDeleteValueKey");
        m_pfnNtEnumerateKey = (PFN_NtEnumerateKey)GetProcAddress(m_hLib, "NtEnumerateKey");
        m_pfnNtEnumerateValueKey = (PFN_NtEnumerateValueKey)GetProcAddress(m_hLib, "NtEnumerateValueKey");
        m_pfnNtFlushKey = (PFN_NtFlushKey)GetProcAddress(m_hLib, "NtFlushKey");
        m_pfnNtNotifyChangeKey = (PFN_NtNotifyChangeKey)GetProcAddress(m_hLib, "NtNotifyChangeKey");
        m_pfnNtOpenFile = (PFN_NtOpenFile)GetProcAddress(m_hLib, "NtOpenFile");
        m_pfnNtOpenKey = (PFN_NtOpenKey)GetProcAddress(m_hLib, "NtOpenKey");
        m_pfnNtOpenKeyEx = (PFN_NtOpenKeyEx)GetProcAddress(m_hLib, "NtOpenKeyEx");
        m_pfnNtOpenKeyTransacted = (PFN_NtOpenKeyTransacted)GetProcAddress(m_hLib, "NtOpenKeyTransacted");
        m_pfnNtOpenKeyTransactedEx = (PFN_NtOpenKeyTransactedEx)GetProcAddress(m_hLib, "NtOpenKeyTransactedEx");
        m_pfnNtQueryKey = (PFN_NtQueryKey)GetProcAddress(m_hLib, "NtQueryKey");
        m_pfnNtQueryObject = (PFN_NtQueryObject)GetProcAddress(m_hLib, "NtQueryObject");
        m_pfnNtQueryValueKey = (PFN_NtQueryValueKey)GetProcAddress(m_hLib, "NtQueryValueKey");
        m_pfnNtSetValueKey = (PFN_NtSetValueKey)GetProcAddress(m_hLib, "NtSetValueKey");
        m_pfnRtlInitUnicodeString = reinterpret_cast<PFN_RtlInitUnicodeString>(GetProcAddress(m_hLib, "RtlInitUnicodeString"));
    }

    NtApi::~NtApi()
    {
        FreeLibrary(m_hLib);
    }

    NTSTATUS NtApi::NtClose(
        _In_ HANDLE Handle
    ) const
    {
        NTSTATUS status;
        __try
        {
            status = m_pfnNtClose(Handle);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            status = GetExceptionCode();
        }
        return status;
    }

    NTSTATUS NTAPI NtApi::NtCreateFile(
        _Out_ PHANDLE FileHandle,
        _In_ ACCESS_MASK DesiredAccess,
        _In_ POBJECT_ATTRIBUTES ObjectAttributes,
        _Out_ PIO_STATUS_BLOCK IoStatusBlock,
        _In_opt_ PLARGE_INTEGER AllocationSize,
        _In_ ULONG FileAttributes,
        _In_ ULONG ShareAccess,
        _In_ ULONG CreateDisposition,
        _In_ ULONG CreateOptions,
        _In_ PVOID EaBuffer,
        _In_ ULONG EaLength
    ) const
    {
        return m_pfnNtCreateFile(FileHandle, DesiredAccess, ObjectAttributes, IoStatusBlock, AllocationSize, FileAttributes, ShareAccess, CreateDisposition, CreateOptions, EaBuffer, EaLength);
    }

    NTSTATUS NTAPI NtApi::NtCreateKey(
        _Out_ PHANDLE KeyHandle,
        _In_ ACCESS_MASK DesiredAccess,
        _In_ POBJECT_ATTRIBUTES ObjectAttributes,
        _In_ ULONG TitleIndex,
        _In_opt_ PUNICODE_STRING Class,
        _In_ ULONG CreateOptions,
        _Out_opt_ PULONG Disposition
    ) const
    {
        return m_pfnNtCreateKey(KeyHandle, DesiredAccess, ObjectAttributes, TitleIndex, Class, CreateOptions, Disposition);
    }

    NTSTATUS NTAPI NtApi::NtCreateKeyTransacted(
        _Out_ PHANDLE KeyHandle,
        _In_ ACCESS_MASK DesiredAccess,
        _In_ POBJECT_ATTRIBUTES ObjectAttributes,
        _In_ ULONG TitleIndex,
        _In_opt_ PUNICODE_STRING Class,
        _In_ ULONG CreateOptions,
        _In_ HANDLE TransactionHandle,
        _Out_opt_ PULONG Disposition
    ) const
    {
        return m_pfnNtCreateKeyTransacted ? m_pfnNtCreateKeyTransacted(KeyHandle, DesiredAccess, ObjectAttributes, TitleIndex, Class, CreateOptions, TransactionHandle, Disposition) : STATUS_PROCEDURE_NOT_FOUND;
    }

    NTSTATUS NTAPI NtApi::NtDeleteKey(
        _In_ HANDLE KeyHandle
    ) const
    {
        return m_pfnNtDeleteKey(KeyHandle);
    }

    NTSTATUS NTAPI NtApi::NtDeleteValueKey(
        _In_ HANDLE KeyHandle,
        _In_ PUNICODE_STRING ValueName
    ) const
    {
        return m_pfnNtDeleteValueKey(KeyHandle, ValueName);
    }

    NTSTATUS NTAPI NtApi::NtEnumerateKey(
        _In_ HANDLE KeyHandle,
        _In_ ULONG Index,
        _In_ KEY_INFORMATION_CLASS KeyInformationClass,
        _Out_opt_ PVOID KeyInformation,
        _In_ ULONG Length,
        _Out_ PULONG ResultLength
    ) const
    {
        return m_pfnNtEnumerateKey(KeyHandle, Index, KeyInformationClass, KeyInformation, Length, ResultLength);
    }

    NTSTATUS NTAPI NtApi::NtEnumerateValueKey(
        _In_ HANDLE KeyHandle,
        _In_ ULONG Index,
        _In_ KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
        _Out_opt_ PVOID KeyValueInformation,
        _In_ ULONG Length,
        _Out_ PULONG ResultLength
    ) const
    {
        return m_pfnNtEnumerateValueKey(KeyHandle, Index, KeyValueInformationClass, KeyValueInformation, Length, ResultLength);
    }

    NTSTATUS NTAPI NtApi::NtFlushKey(
        _In_ HANDLE KeyHandle
    ) const
    {
        return m_pfnNtFlushKey(KeyHandle);
    }

    NTSTATUS NTAPI NtApi::NtNotifyChangeKey(
        _In_ HANDLE KeyHandle,
        _In_opt_ HANDLE Event,
        _In_opt_ PIO_APC_ROUTINE ApcRoutine,
        _In_opt_ PVOID ApcContext,
        _Out_ PIO_STATUS_BLOCK IoStatusBlock,
        _In_ ULONG CompletionFilter,
        _In_ BOOLEAN WatchTree,
        _Out_opt_ PVOID Buffer,
        _In_ ULONG BufferSize,
        _In_ BOOLEAN Asynchronous
    ) const
    {
        return m_pfnNtNotifyChangeKey(KeyHandle, Event, ApcRoutine, ApcContext, IoStatusBlock, CompletionFilter, WatchTree, Buffer, BufferSize, Asynchronous);
    }

    NTSTATUS NTAPI NtApi::NtOpenFile(
        _Out_ PHANDLE FileHandle,
        _In_ ACCESS_MASK DesiredAccess,
        _In_ POBJECT_ATTRIBUTES ObjectAttributes,
        _Out_ PIO_STATUS_BLOCK IoStatusBlock,
        _In_ ULONG ShareAccess,
        _In_ ULONG OpenOptions
    ) const
    {
        return m_pfnNtOpenFile(FileHandle, DesiredAccess, ObjectAttributes, IoStatusBlock, ShareAccess, OpenOptions);
    }

    NTSTATUS NTAPI NtApi::NtOpenKey(
        _Out_ PHANDLE KeyHandle,
        _In_ ACCESS_MASK DesiredAccess,
        _In_ POBJECT_ATTRIBUTES ObjectAttributes
    ) const
    {
        return m_pfnNtOpenKey(KeyHandle, DesiredAccess, ObjectAttributes);
    }

    NTSTATUS NTAPI NtApi::NtOpenKeyEx(
        _Out_ PHANDLE KeyHandle,
        _In_ ACCESS_MASK DesiredAccess,
        _In_ POBJECT_ATTRIBUTES ObjectAttributes,
        _In_ ULONG OpenOptions
    ) const
    {
        //	API is only implemented on Windows 7 and later
        return m_pfnNtOpenKeyEx ? m_pfnNtOpenKeyEx(KeyHandle, DesiredAccess, ObjectAttributes, OpenOptions) : STATUS_PROCEDURE_NOT_FOUND;
    }

    NTSTATUS NTAPI NtApi::NtOpenKeyTransacted(
        _Out_ PHANDLE KeyHandle,
        _In_ ACCESS_MASK DesiredAccess,
        _In_ POBJECT_ATTRIBUTES ObjectAttributes,
        _In_ HANDLE TransactionHandle
    ) const
    {
        return m_pfnNtOpenKeyTransacted ? m_pfnNtOpenKeyTransacted(KeyHandle, DesiredAccess, ObjectAttributes, TransactionHandle) : STATUS_PROCEDURE_NOT_FOUND;
    }

    NTSTATUS NTAPI NtApi::NtOpenKeyTransactedEx(
        _Out_ PHANDLE KeyHandle,
        _In_ ACCESS_MASK DesiredAccess,
        _In_ POBJECT_ATTRIBUTES ObjectAttributes,
        _In_ ULONG OpenOptions,
        _In_ HANDLE TransactionHandle
    ) const
    {
        return m_pfnNtOpenKeyTransactedEx ? m_pfnNtOpenKeyTransactedEx(KeyHandle, DesiredAccess, ObjectAttributes, OpenOptions, TransactionHandle) : STATUS_PROCEDURE_NOT_FOUND;
    }

    NTSTATUS NTAPI NtApi::NtQueryKey(
        _In_ HANDLE KeyHandle,
        _In_ KEY_INFORMATION_CLASS KeyInformationClass,
        _Out_opt_ PVOID KeyInformation,
        _In_ ULONG Length,
        _Out_ PULONG ResultLength
    ) const
    {
        return m_pfnNtQueryKey(KeyHandle, KeyInformationClass, KeyInformation, Length, ResultLength);
    }

    NTSTATUS NTAPI NtApi::NtQueryObject(
        _In_opt_ HANDLE Handle,
        _In_ OBJECT_INFORMATION_CLASS ObjectInformationClass,
        _Out_opt_ PVOID ObjectInformation,
        _In_ ULONG ObjectInformationLength,
        _Out_opt_ PULONG ReturnLength
    ) const
    {
        return m_pfnNtQueryObject(Handle, ObjectInformationClass, ObjectInformation, ObjectInformationLength, ReturnLength);
    }

    NTSTATUS NTAPI NtApi::NtQueryValueKey(
        _In_ HANDLE KeyHandle,
        _In_ PUNICODE_STRING ValueName,
        _In_ KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
        _Out_opt_ PVOID KeyValueInformation,
        _In_ ULONG Length,
        _Out_ PULONG ResultLength
    ) const
    {
        return m_pfnNtQueryValueKey(KeyHandle, ValueName, KeyValueInformationClass, KeyValueInformation, Length, ResultLength);
    }

    NTSTATUS NTAPI NtApi::NtSetValueKey(
        _In_ HANDLE KeyHandle,
        _In_ PUNICODE_STRING ValueName,
        _In_opt_ ULONG TitleIndex,
        _In_ ULONG Type,
        _In_opt_ PVOID Data,
        _In_ ULONG DataSize
    ) const
    {
        return m_pfnNtSetValueKey(KeyHandle, ValueName, TitleIndex, Type, Data, DataSize);
    }

    VOID NTAPI NtApi::RtlInitUnicodeString(
        _In_ PUNICODE_STRING DestinationString,
        _In_ PCWSTR SourceString
    ) const
    {
        m_pfnRtlInitUnicodeString(DestinationString, SourceString);
    }
}
