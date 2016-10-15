#include "ntdll.h"


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
    m_hLib = LoadLibraryW( L"ntdll.dll" );

    m_pfnNtClose = (PFN_NtClose) GetProcAddress( m_hLib, "NtClose" );
    m_pfnNtCreateFile = (PFN_NtCreateFile) GetProcAddress( m_hLib, "NtCreateFile" );
    m_pfnNtCreateKey = (PFN_NtCreateKey) GetProcAddress( m_hLib, "NtCreateKey" );
    m_pfnNtCreateKeyTransacted = (PFN_NtCreateKeyTransacted) GetProcAddress( m_hLib, "NtCreateKeyTransacted" );
    m_pfnNtDeleteKey = (PFN_NtDeleteKey) GetProcAddress( m_hLib, "NtDeleteKey" );
    m_pfnNtDeleteValueKey = (PFN_NtDeleteValueKey) GetProcAddress( m_hLib, "NtDeleteValueKey" );
    m_pfnNtEnumerateKey = (PFN_NtEnumerateKey) GetProcAddress( m_hLib, "NtEnumerateKey" );
    m_pfnNtEnumerateValueKey = (PFN_NtEnumerateValueKey) GetProcAddress( m_hLib, "NtEnumerateValueKey" );
    m_pfnNtFlushKey = (PFN_NtFlushKey) GetProcAddress( m_hLib, "NtFlushKey" );
    m_pfnNtNotifyChangeKey = (PFN_NtNotifyChangeKey) GetProcAddress( m_hLib, "NtNotifyChangeKey" );
    m_pfnNtOpenFile = (PFN_NtOpenFile) GetProcAddress( m_hLib, "NtOpenFile" );
    m_pfnNtOpenKey = (PFN_NtOpenKey) GetProcAddress( m_hLib, "NtOpenKey" );
    m_pfnNtOpenKeyEx = (PFN_NtOpenKeyEx) GetProcAddress( m_hLib, "NtOpenKeyEx" );
    m_pfnNtOpenKeyTransacted = (PFN_NtOpenKeyTransacted) GetProcAddress( m_hLib, "NtOpenKeyTransacted" );
    m_pfnNtOpenKeyTransactedEx = (PFN_NtOpenKeyTransactedEx) GetProcAddress( m_hLib, "NtOpenKeyTransactedEx" );
    m_pfnNtQueryKey = (PFN_NtQueryKey) GetProcAddress( m_hLib, "NtQueryKey" );
    m_pfnNtQueryObject = (PFN_NtQueryObject) GetProcAddress( m_hLib, "NtQueryObject" );
    m_pfnNtQueryValueKey = (PFN_NtQueryValueKey) GetProcAddress( m_hLib, "NtQueryValueKey" );
    m_pfnNtSetValueKey = (PFN_NtSetValueKey) GetProcAddress( m_hLib, "NtSetValueKey" );
}

NtApi::~NtApi()
{
    FreeLibrary( m_hLib );
}

NTSTATUS NtApi::NtClose(
    __in HANDLE Handle
    ) const
{
    NTSTATUS status;
    __try
    {
        status = m_pfnNtClose( Handle );
    }
    __except ( EXCEPTION_EXECUTE_HANDLER )
    {
        status = GetExceptionCode();
    }
    return status;
}

NTSTATUS NTAPI NtApi::NtCreateFile(
    __out PHANDLE FileHandle,
    __in ACCESS_MASK DesiredAccess,
    __in POBJECT_ATTRIBUTES ObjectAttributes,
    __out PIO_STATUS_BLOCK IoStatusBlock,
    __in_opt PLARGE_INTEGER AllocationSize,
    __in ULONG FileAttributes,
    __in ULONG ShareAccess,
    __in ULONG CreateDisposition,
    __in ULONG CreateOptions,
    __in PVOID EaBuffer,
    __in ULONG EaLength
    ) const
{
    return m_pfnNtCreateFile( FileHandle, DesiredAccess, ObjectAttributes, IoStatusBlock, AllocationSize, FileAttributes, ShareAccess, CreateDisposition, CreateOptions, EaBuffer, EaLength );
}

NTSTATUS NTAPI NtApi::NtCreateKey(
    __out PHANDLE KeyHandle,
    __in ACCESS_MASK DesiredAccess,
    __in POBJECT_ATTRIBUTES ObjectAttributes,
    __in ULONG TitleIndex,
    __in_opt PUNICODE_STRING Class,
    __in ULONG CreateOptions,
    __out_opt PULONG Disposition
    ) const
{
    return m_pfnNtCreateKey( KeyHandle, DesiredAccess, ObjectAttributes, TitleIndex, Class, CreateOptions, Disposition );
}

NTSTATUS NTAPI NtApi::NtCreateKeyTransacted(
    __out PHANDLE KeyHandle,
    __in ACCESS_MASK DesiredAccess,
    __in POBJECT_ATTRIBUTES ObjectAttributes,
    __in ULONG TitleIndex,
    __in_opt PUNICODE_STRING Class,
    __in ULONG CreateOptions,
    __in HANDLE TransactionHandle,
    __out_opt PULONG Disposition
    ) const
{
    return m_pfnNtCreateKeyTransacted ? m_pfnNtCreateKeyTransacted( KeyHandle, DesiredAccess, ObjectAttributes, TitleIndex, Class, CreateOptions, TransactionHandle, Disposition ) : STATUS_PROCEDURE_NOT_FOUND;
}

NTSTATUS NTAPI NtApi::NtDeleteKey(
    __in HANDLE KeyHandle
    ) const
{
    return m_pfnNtDeleteKey( KeyHandle );
}

NTSTATUS NTAPI NtApi::NtDeleteValueKey(
    __in HANDLE KeyHandle,
    __in PUNICODE_STRING ValueName
    ) const
{
    return m_pfnNtDeleteValueKey( KeyHandle, ValueName );
}

NTSTATUS NTAPI NtApi::NtEnumerateKey(
    __in HANDLE KeyHandle,
    __in ULONG Index,
    __in KEY_INFORMATION_CLASS KeyInformationClass,
    __out_opt PVOID KeyInformation,
    __in ULONG Length,
    __out PULONG ResultLength
    ) const
{
    return m_pfnNtEnumerateKey( KeyHandle, Index, KeyInformationClass, KeyInformation, Length, ResultLength );
}

NTSTATUS NTAPI NtApi::NtEnumerateValueKey(
    __in HANDLE KeyHandle,
    __in ULONG Index,
    __in KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
    __out_opt PVOID KeyValueInformation,
    __in ULONG Length,
    __out PULONG ResultLength
    ) const
{
    return m_pfnNtEnumerateValueKey( KeyHandle, Index, KeyValueInformationClass, KeyValueInformation, Length, ResultLength );
}

NTSTATUS NTAPI NtApi::NtFlushKey(
    __in HANDLE KeyHandle
    ) const
{
    return m_pfnNtFlushKey( KeyHandle );
}

NTSTATUS NTAPI NtApi::NtNotifyChangeKey(
    __in HANDLE KeyHandle,
    __in_opt HANDLE Event,
    __in_opt PIO_APC_ROUTINE ApcRoutine,
    __in_opt PVOID ApcContext,
    __out PIO_STATUS_BLOCK IoStatusBlock,
    __in ULONG CompletionFilter,
    __in BOOLEAN WatchTree,
    __out_opt PVOID Buffer,
    __in ULONG BufferSize,
    __in BOOLEAN Asynchronous
    ) const
{
    return m_pfnNtNotifyChangeKey( KeyHandle, Event, ApcRoutine, ApcContext, IoStatusBlock, CompletionFilter, WatchTree, Buffer, BufferSize, Asynchronous );
}

NTSTATUS NTAPI NtApi::NtOpenFile(
    __out PHANDLE FileHandle,
    __in ACCESS_MASK DesiredAccess,
    __in POBJECT_ATTRIBUTES ObjectAttributes,
    __out PIO_STATUS_BLOCK IoStatusBlock,
    __in ULONG ShareAccess,
    __in ULONG OpenOptions
    ) const
{
    return m_pfnNtOpenFile( FileHandle, DesiredAccess, ObjectAttributes, IoStatusBlock, ShareAccess, OpenOptions );
}

NTSTATUS NTAPI NtApi::NtOpenKey(
    __out PHANDLE KeyHandle,
    __in ACCESS_MASK DesiredAccess,
    __in POBJECT_ATTRIBUTES ObjectAttributes
    ) const
{
    return m_pfnNtOpenKey( KeyHandle, DesiredAccess, ObjectAttributes );
}

NTSTATUS NTAPI NtApi::NtOpenKeyEx(
    __out PHANDLE KeyHandle,
    __in ACCESS_MASK DesiredAccess,
    __in POBJECT_ATTRIBUTES ObjectAttributes,
    __in ULONG OpenOptions
    ) const
{
    //	API is only implemented on Windows 7 and later
    return m_pfnNtOpenKeyEx ? m_pfnNtOpenKeyEx( KeyHandle, DesiredAccess, ObjectAttributes, OpenOptions ) : STATUS_PROCEDURE_NOT_FOUND;
}

NTSTATUS NTAPI NtApi::NtOpenKeyTransacted(
    __out PHANDLE KeyHandle,
    __in ACCESS_MASK DesiredAccess,
    __in POBJECT_ATTRIBUTES ObjectAttributes,
    __in HANDLE TransactionHandle
    ) const
{
    return m_pfnNtOpenKeyTransacted ? m_pfnNtOpenKeyTransacted( KeyHandle, DesiredAccess, ObjectAttributes, TransactionHandle ) : STATUS_PROCEDURE_NOT_FOUND;
}

NTSTATUS NTAPI NtApi::NtOpenKeyTransactedEx(
    __out PHANDLE KeyHandle,
    __in ACCESS_MASK DesiredAccess,
    __in POBJECT_ATTRIBUTES ObjectAttributes,
    __in ULONG OpenOptions,
    __in HANDLE TransactionHandle
    ) const
{
    return m_pfnNtOpenKeyTransactedEx ? m_pfnNtOpenKeyTransactedEx( KeyHandle, DesiredAccess, ObjectAttributes, OpenOptions, TransactionHandle ) : STATUS_PROCEDURE_NOT_FOUND;
}

NTSTATUS NTAPI NtApi::NtQueryKey(
    __in HANDLE KeyHandle,
    __in KEY_INFORMATION_CLASS KeyInformationClass,
    __out_opt PVOID KeyInformation,
    __in ULONG Length,
    __out PULONG ResultLength
    ) const
{
    return m_pfnNtQueryKey( KeyHandle, KeyInformationClass, KeyInformation, Length, ResultLength );
}

NTSTATUS NTAPI NtApi::NtQueryObject(
    __in_opt HANDLE Handle,
    __in OBJECT_INFORMATION_CLASS ObjectInformationClass,
    __out_opt PVOID ObjectInformation,
    __in ULONG ObjectInformationLength,
    __out_opt PULONG ReturnLength
    ) const
{
    return m_pfnNtQueryObject( Handle, ObjectInformationClass, ObjectInformation, ObjectInformationLength, ReturnLength );
}

NTSTATUS NTAPI NtApi::NtQueryValueKey(
    __in HANDLE KeyHandle,
    __in PUNICODE_STRING ValueName,
    __in KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
    __out_opt PVOID KeyValueInformation,
    __in ULONG Length,
    __out PULONG ResultLength
    ) const
{
    return m_pfnNtQueryValueKey( KeyHandle, ValueName, KeyValueInformationClass, KeyValueInformation, Length, ResultLength );
}

NTSTATUS NTAPI NtApi::NtSetValueKey(
    __in HANDLE KeyHandle,
    __in PUNICODE_STRING ValueName,
    __in_opt ULONG TitleIndex,
    __in ULONG Type,
    __in_opt PVOID Data,
    __in ULONG DataSize
    ) const
{
    return m_pfnNtSetValueKey( KeyHandle, ValueName, TitleIndex, Type, Data, DataSize );
}
