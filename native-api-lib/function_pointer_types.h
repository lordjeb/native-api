#pragma once

namespace Nt
{
    typedef NTSTATUS(NTAPI *PFN_NtClose)(
        _In_ HANDLE Handle
        );

    typedef NTSTATUS(NTAPI *PFN_NtCreateFile)(
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
        );

    typedef NTSTATUS(NTAPI *PFN_NtCreateKey)(
        _Out_ PHANDLE KeyHandle,
        _In_ ACCESS_MASK DesiredAccess,
        _In_ POBJECT_ATTRIBUTES ObjectAttributes,
        _In_ ULONG TitleIndex,
        _In_opt_ PUNICODE_STRING Class,
        _In_ ULONG CreateOptions,
        _Out_opt_ PULONG Disposition
        );

    typedef NTSTATUS(NTAPI *PFN_NtCreateKeyTransacted)(
        _Out_ PHANDLE KeyHandle,
        _In_ ACCESS_MASK DesiredAccess,
        _In_ POBJECT_ATTRIBUTES ObjectAttributes,
        _In_ ULONG TitleIndex,
        _In_opt_ PUNICODE_STRING Class,
        _In_ ULONG CreateOptions,
        _In_ HANDLE TransactionHandle,
        _Out_opt_ PULONG Disposition
        );

    typedef NTSTATUS(NTAPI *PFN_NtCreateWnfStateName)(
        _Out_ PWNF_STATE_NAME StateName,
        _In_ WNF_STATE_NAME_LIFETIME NameLifetime,
        _In_ WNF_DATA_SCOPE DataScope,
        _In_ BOOLEAN PersistData,
        _In_opt_ PCWNF_TYPE_ID TypeId,
        _In_ ULONG MaximumStateSize,
        _In_ PSECURITY_DESCRIPTOR SecurityDescriptor
        );

    typedef NTSTATUS(NTAPI *PFN_NtDeleteKey)(
        _In_ HANDLE KeyHandle
        );

    typedef NTSTATUS(NTAPI *PFN_NtDeleteFile)(
        _In_ POBJECT_ATTRIBUTES ObjectAttributes
        );
    
    typedef NTSTATUS(NTAPI *PFN_NtDeleteValueKey)(
        _In_ HANDLE KeyHandle,
        _In_ PUNICODE_STRING ValueName
        );

    typedef NTSTATUS(NTAPI* PFN_NtDeleteWnfStateName)(
        _In_ PCWNF_STATE_NAME StateName
        );

    typedef NTSTATUS(NTAPI *PFN_NtEnumerateKey)(
        _In_ HANDLE KeyHandle,
        _In_ ULONG Index,
        _In_ KEY_INFORMATION_CLASS KeyInformationClass,
        _Out_opt_ PVOID KeyInformation,
        _In_ ULONG Length,
        _Out_ PULONG ResultLength
        );

    typedef NTSTATUS(NTAPI *PFN_NtEnumerateValueKey)(
        _In_ HANDLE KeyHandle,
        _In_ ULONG Index,
        _In_ KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
        _Out_opt_ PVOID KeyValueInformation,
        _In_ ULONG Length,
        _Out_ PULONG ResultLength
        );

    typedef NTSTATUS(NTAPI *PFN_NtFlushKey)(
        _In_ HANDLE KeyHandle
        );

    typedef NTSTATUS(NTAPI *PFN_NtNotifyChangeKey)(
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
        );

    typedef NTSTATUS(NTAPI *PFN_NtOpenFile)(
        _Out_ PHANDLE FileHandle,
        _In_ ACCESS_MASK DesiredAccess,
        _In_ POBJECT_ATTRIBUTES ObjectAttributes,
        _Out_ PIO_STATUS_BLOCK IoStatusBlock,
        _In_ ULONG ShareAccess,
        _In_ ULONG OpenOptions
        );

    typedef NTSTATUS(NTAPI *PFN_NtOpenKey)(
        _Out_ PHANDLE KeyHandle,
        _In_ ACCESS_MASK DesiredAccess,
        _In_ POBJECT_ATTRIBUTES ObjectAttributes
        );

    typedef NTSTATUS(NTAPI *PFN_NtOpenKeyEx)(
        _Out_ PHANDLE KeyHandle,
        _In_ ACCESS_MASK DesiredAccess,
        _In_ POBJECT_ATTRIBUTES ObjectAttributes,
        _In_ ULONG OpenOptions
        );

    typedef NTSTATUS(NTAPI *PFN_NtOpenKeyTransacted)(
        _Out_ PHANDLE KeyHandle,
        _In_ ACCESS_MASK DesiredAccess,
        _In_ POBJECT_ATTRIBUTES ObjectAttributes,
        _In_ HANDLE TransactionHandle
        );

    typedef NTSTATUS(NTAPI *PFN_NtOpenKeyTransactedEx)(
        _Out_ PHANDLE KeyHandle,
        _In_ ACCESS_MASK DesiredAccess,
        _In_ POBJECT_ATTRIBUTES ObjectAttributes,
        _In_ ULONG OpenOptions,
        _In_ HANDLE TransactionHandle
        );

    typedef NTSTATUS(NTAPI *PFN_NtQueryDirectoryFile)(
        _In_ HANDLE FileHandle,
        _In_opt_ HANDLE Event,
        _In_opt_ PIO_APC_ROUTINE ApcRoutine,
        _In_opt_ PVOID ApcContext,
        _Out_ PIO_STATUS_BLOCK IoStatusBlock,
        _Out_ PVOID FileInformation,
        _In_ ULONG Length,
        _In_ FILE_INFORMATION_CLASS FileInformationClass,
        _In_ BOOLEAN ReturnSingleEntry,
        _In_opt_ PUNICODE_STRING FileName,
        _In_ BOOLEAN RestartScan
        );
    
    typedef NTSTATUS(NTAPI *PFN_NtQueryKey)(
        _In_ HANDLE KeyHandle,
        _In_ KEY_INFORMATION_CLASS KeyInformationClass,
        _Out_opt_ PVOID KeyInformation,
        _In_ ULONG Length,
        _Out_ PULONG ResultLength
        );

    typedef NTSTATUS(NTAPI *PFN_NtQueryObject)(
        _In_opt_ HANDLE Handle,
        _In_ OBJECT_INFORMATION_CLASS ObjectInformationClass,
        _Out_opt_ PVOID ObjectInformation,
        _In_ ULONG ObjectInformationLength,
        _Out_opt_ PULONG ReturnLength
        );

    typedef NTSTATUS(NTAPI *PFN_NtQueryValueKey)(
        _In_ HANDLE KeyHandle,
        _In_ PUNICODE_STRING ValueName,
        _In_ KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
        _Out_opt_ PVOID KeyValueInformation,
        _In_ ULONG Length,
        _Out_ PULONG ResultLength
        );

    typedef NTSTATUS(NTAPI *PFN_NtSetValueKey)(
        _In_ HANDLE KeyHandle,
        _In_ PUNICODE_STRING ValueName,
        _In_opt_ ULONG TitleIndex,
        _In_ ULONG Type,
        _In_opt_ PVOID Data,
        _In_ ULONG DataSize
        );

    typedef VOID(NTAPI *PFN_RtlInitUnicodeString)(
        _In_ PUNICODE_STRING DestinationString,
        _In_ PCWSTR SourceString
        );
}
