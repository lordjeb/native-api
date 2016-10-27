#pragma once
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <Windows.h>
#include <winternl.h>
#pragma warning( push )
#pragma warning( disable : 4005 )
#include <ntstatus.h>
#pragma warning( pop )
#include "undocumented.h"
#include "function_pointer_types.h"


#ifndef RTL_CONSTANT_STRING
#define RTL_CONSTANT_STRING(x) { (USHORT)wcslen(x) * sizeof(wchar_t), (USHORT)wcslen(x) * sizeof(wchar_t), x }
#endif

#ifndef RTL_CONSTANT_OBJECT_ATTRIBUTES
#define RTL_CONSTANT_OBJECT_ATTRIBUTES(r, o, a) { sizeof(OBJECT_ATTRIBUTES), r, o, a, NULL, NULL }
#endif


namespace Nt
{

    class NtApi
    {
    public:
        NtApi();
        virtual ~NtApi();

        NTSTATUS NTAPI NtClose(
            _In_ HANDLE Handle
        ) const;

        NTSTATUS NTAPI NtCreateFile(
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
        ) const;

        NTSTATUS NTAPI NtCreateKey(
            _Out_ PHANDLE KeyHandle,
            _In_ ACCESS_MASK DesiredAccess,
            _In_ POBJECT_ATTRIBUTES ObjectAttributes,
            _In_ ULONG TitleIndex,
            _In_opt_ PUNICODE_STRING Class,
            _In_ ULONG CreateOptions,
            _Out_opt_ PULONG Disposition
        ) const;

        NTSTATUS NTAPI NtCreateKeyTransacted(
            _Out_ PHANDLE KeyHandle,
            _In_ ACCESS_MASK DesiredAccess,
            _In_ POBJECT_ATTRIBUTES ObjectAttributes,
            _In_ ULONG TitleIndex,
            _In_opt_ PUNICODE_STRING Class,
            _In_ ULONG CreateOptions,
            _In_ HANDLE TransactionHandle,
            _Out_opt_ PULONG Disposition
        ) const;

        NTSTATUS NTAPI NtDeleteKey(
            _In_ HANDLE KeyHandle
        ) const;

        NTSTATUS NTAPI NtDeleteFile(
            _In_ POBJECT_ATTRIBUTES ObjectAttributes
        ) const;

        NTSTATUS NTAPI NtDeleteValueKey(
            _In_ HANDLE KeyHandle,
            _In_ PUNICODE_STRING ValueName
        ) const;

        NTSTATUS NTAPI NtEnumerateKey(
            _In_ HANDLE KeyHandle,
            _In_ ULONG Index,
            _In_ KEY_INFORMATION_CLASS KeyInformationClass,
            _Out_opt_ PVOID KeyInformation,
            _In_ ULONG Length,
            _Out_ PULONG ResultLength
        ) const;

        NTSTATUS NTAPI NtEnumerateValueKey(
            _In_ HANDLE KeyHandle,
            _In_ ULONG Index,
            _In_ KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
            _Out_opt_ PVOID KeyValueInformation,
            _In_ ULONG Length,
            _Out_ PULONG ResultLength
        ) const;

        NTSTATUS NTAPI NtFlushKey(
            _In_ HANDLE KeyHandle
        ) const;

        NTSTATUS NTAPI NtNotifyChangeKey(
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
        ) const;

        NTSTATUS NTAPI NtOpenFile(
            _Out_ PHANDLE FileHandle,
            _In_ ACCESS_MASK DesiredAccess,
            _In_ POBJECT_ATTRIBUTES ObjectAttributes,
            _Out_ PIO_STATUS_BLOCK IoStatusBlock,
            _In_ ULONG ShareAccess,
            _In_ ULONG OpenOptions
        ) const;

        NTSTATUS NTAPI NtOpenKey(
            _Out_ PHANDLE KeyHandle,
            _In_ ACCESS_MASK DesiredAccess,
            _In_ POBJECT_ATTRIBUTES ObjectAttributes
        ) const;

        NTSTATUS NTAPI NtOpenKeyEx(
            _Out_ PHANDLE KeyHandle,
            _In_ ACCESS_MASK DesiredAccess,
            _In_ POBJECT_ATTRIBUTES ObjectAttributes,
            _In_ ULONG OpenOptions
        ) const;

        NTSTATUS NTAPI NtOpenKeyTransacted(
            _Out_ PHANDLE KeyHandle,
            _In_ ACCESS_MASK DesiredAccess,
            _In_ POBJECT_ATTRIBUTES ObjectAttributes,
            _In_ HANDLE TransactionHandle
        ) const;

        NTSTATUS NTAPI NtOpenKeyTransactedEx(
            _Out_ PHANDLE KeyHandle,
            _In_ ACCESS_MASK DesiredAccess,
            _In_ POBJECT_ATTRIBUTES ObjectAttributes,
            _In_ ULONG OpenOptions,
            _In_ HANDLE TransactionHandle
        ) const;

        NTSTATUS NTAPI NtQueryDirectoryFile(
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
        ) const;

        NTSTATUS NTAPI NtQueryKey(
            _In_ HANDLE KeyHandle,
            _In_ KEY_INFORMATION_CLASS KeyInformationClass,
            _Out_opt_ PVOID KeyInformation,
            _In_ ULONG Length,
            _Out_ PULONG ResultLength
        ) const;

        NTSTATUS NTAPI NtQueryObject(
            _In_opt_ HANDLE Handle,
            _In_ OBJECT_INFORMATION_CLASS ObjectInformationClass,
            _Out_opt_ PVOID ObjectInformation,
            _In_ ULONG ObjectInformationLength,
            _Out_opt_ PULONG ReturnLength
        ) const;

        NTSTATUS NTAPI NtQueryValueKey(
            _In_ HANDLE KeyHandle,
            _In_ PUNICODE_STRING ValueName,
            _In_ KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
            _Out_opt_ PVOID KeyValueInformation,
            _In_ ULONG Length,
            _Out_ PULONG ResultLength
        ) const;

        NTSTATUS NTAPI NtSetValueKey(
            _In_ HANDLE KeyHandle,
            _In_ PUNICODE_STRING ValueName,
            _In_opt_ ULONG TitleIndex,
            _In_ ULONG Type,
            _In_opt_ PVOID Data,
            _In_ ULONG DataSize
        ) const;

        VOID NTAPI RtlInitUnicodeString(
            _In_ PUNICODE_STRING DestinationString,
            _In_ PCWSTR SourceString
        ) const;

    private:
        HMODULE m_hLib;
        PFN_NtClose m_pfnNtClose;
        PFN_NtCreateFile m_pfnNtCreateFile;
        PFN_NtCreateKey m_pfnNtCreateKey;
        PFN_NtCreateKeyTransacted m_pfnNtCreateKeyTransacted;
        PFN_NtDeleteKey m_pfnNtDeleteKey;
        PFN_NtDeleteFile m_pfnNtDeleteFile;
        PFN_NtDeleteValueKey m_pfnNtDeleteValueKey;
        PFN_NtEnumerateKey m_pfnNtEnumerateKey;
        PFN_NtEnumerateValueKey m_pfnNtEnumerateValueKey;
        PFN_NtFlushKey m_pfnNtFlushKey;
        PFN_NtNotifyChangeKey m_pfnNtNotifyChangeKey;
        PFN_NtOpenFile m_pfnNtOpenFile;
        PFN_NtOpenKey m_pfnNtOpenKey;
        PFN_NtOpenKeyEx m_pfnNtOpenKeyEx;
        PFN_NtOpenKeyTransacted m_pfnNtOpenKeyTransacted;
        PFN_NtOpenKeyTransactedEx m_pfnNtOpenKeyTransactedEx;
        PFN_NtQueryDirectoryFile m_pfnNtQueryDirectoryFile;
        PFN_NtQueryKey m_pfnNtQueryKey;
        PFN_NtQueryObject m_pfnNtQueryObject;
        PFN_NtQueryValueKey m_pfnNtQueryValueKey;
        PFN_NtSetValueKey m_pfnNtSetValueKey;
        PFN_RtlInitUnicodeString m_pfnRtlInitUnicodeString;
    };
}