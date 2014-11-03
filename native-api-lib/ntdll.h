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


class NtApi
{
public:
	NtApi();
	virtual ~NtApi();

	NTSTATUS NTAPI NtClose(
		__in HANDLE Handle
		);

	NTSTATUS NTAPI NtCreateFile(
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
		);

	NTSTATUS NTAPI NtCreateKey(
		__out PHANDLE KeyHandle,
		__in ACCESS_MASK DesiredAccess,
		__in POBJECT_ATTRIBUTES ObjectAttributes,
		__in ULONG TitleIndex,
		__in_opt PUNICODE_STRING Class,
		__in ULONG CreateOptions,
		__out_opt PULONG Disposition
		);

	NTSTATUS NTAPI NtCreateKeyTransacted(
		__out PHANDLE KeyHandle,
		__in ACCESS_MASK DesiredAccess,
		__in POBJECT_ATTRIBUTES ObjectAttributes,
		__in ULONG TitleIndex,
		__in_opt PUNICODE_STRING Class,
		__in ULONG CreateOptions,
		__in HANDLE TransactionHandle,
		__out_opt PULONG Disposition
		);

	NTSTATUS NTAPI NtDeleteKey(
		__in HANDLE KeyHandle
		);

	NTSTATUS NTAPI NtDeleteValueKey(
		__in HANDLE KeyHandle,
		__in PUNICODE_STRING ValueName
		);

	NTSTATUS NTAPI NtEnumerateKey(
		__in HANDLE KeyHandle,
		__in ULONG Index,
		__in KEY_INFORMATION_CLASS KeyInformationClass,
		__out_opt PVOID KeyInformation,
		__in ULONG Length,
		__out PULONG ResultLength
		);

	NTSTATUS NTAPI NtEnumerateValueKey(
		__in HANDLE KeyHandle,
		__in ULONG Index,
		__in KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
		__out_opt PVOID KeyValueInformation,
		__in ULONG Length,
		__out PULONG ResultLength
		);

	NTSTATUS NTAPI NtFlushKey(
		__in HANDLE KeyHandle
		);

	NTSTATUS NTAPI NtNotifyChangeKey(
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
		);

	NTSTATUS NTAPI NtOpenFile(
		__out PHANDLE FileHandle,
		__in ACCESS_MASK DesiredAccess,
		__in POBJECT_ATTRIBUTES ObjectAttributes,
		__out PIO_STATUS_BLOCK IoStatusBlock,
		__in ULONG ShareAccess,
		__in ULONG OpenOptions
		);

	NTSTATUS NTAPI NtOpenKey(
		__out PHANDLE KeyHandle,
		__in ACCESS_MASK DesiredAccess,
		__in POBJECT_ATTRIBUTES ObjectAttributes
		);

	NTSTATUS NTAPI NtOpenKeyEx(
		__out PHANDLE KeyHandle,
		__in ACCESS_MASK DesiredAccess,
		__in POBJECT_ATTRIBUTES ObjectAttributes,
		__in ULONG OpenOptions
		);

	NTSTATUS NTAPI NtOpenKeyTransacted(
		__out PHANDLE KeyHandle,
		__in ACCESS_MASK DesiredAccess,
		__in POBJECT_ATTRIBUTES ObjectAttributes,
		__in HANDLE TransactionHandle
		);

	NTSTATUS NTAPI NtOpenKeyTransactedEx(
		__out PHANDLE KeyHandle,
		__in ACCESS_MASK DesiredAccess,
		__in POBJECT_ATTRIBUTES ObjectAttributes,
		__in ULONG OpenOptions,
		__in HANDLE TransactionHandle
		);

	NTSTATUS NTAPI NtQueryKey(
		__in HANDLE KeyHandle,
		__in KEY_INFORMATION_CLASS KeyInformationClass,
		__out_opt PVOID KeyInformation,
		__in ULONG Length,
		__out PULONG ResultLength
		);

	NTSTATUS NTAPI NtQueryObject(
		__in_opt HANDLE Handle,
		__in OBJECT_INFORMATION_CLASS ObjectInformationClass,
		__out_opt PVOID ObjectInformation,
		__in ULONG ObjectInformationLength,
		__out_opt PULONG ReturnLength
		);

	NTSTATUS NTAPI NtQueryValueKey(
		__in HANDLE KeyHandle,
		__in PUNICODE_STRING ValueName,
		__in KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
		__out_opt PVOID KeyValueInformation,
		__in ULONG Length,
		__out PULONG ResultLength
		);

	NTSTATUS NTAPI NtSetValueKey(
		__in HANDLE KeyHandle,
		__in PUNICODE_STRING ValueName,
		__in_opt ULONG TitleIndex,
		__in ULONG Type,
		__in_opt PVOID Data,
		__in ULONG DataSize
		);

private:
	HMODULE m_hLib;
	PFN_NtClose m_pfnNtClose;
	PFN_NtCreateFile m_pfnNtCreateFile;
	PFN_NtCreateKey m_pfnNtCreateKey;
	PFN_NtCreateKeyTransacted m_pfnNtCreateKeyTransacted;
	PFN_NtDeleteKey m_pfnNtDeleteKey;
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
	PFN_NtQueryKey m_pfnNtQueryKey;
	PFN_NtQueryObject m_pfnNtQueryObject;
	PFN_NtQueryValueKey m_pfnNtQueryValueKey;
	PFN_NtSetValueKey m_pfnNtSetValueKey;
};
