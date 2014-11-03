#pragma once


typedef NTSTATUS( NTAPI *PFN_NtClose )(
	__in HANDLE Handle
	);

typedef NTSTATUS( NTAPI *PFN_NtCreateFile )(
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

typedef NTSTATUS( NTAPI *PFN_NtCreateKey )( 
	__out PHANDLE KeyHandle, 
	__in ACCESS_MASK DesiredAccess, 
	__in POBJECT_ATTRIBUTES ObjectAttributes, 
	__in ULONG TitleIndex, 
	__in_opt PUNICODE_STRING Class,
	__in ULONG CreateOptions, 
	__out_opt PULONG Disposition 
	);

typedef NTSTATUS( NTAPI *PFN_NtCreateKeyTransacted )( 
	__out PHANDLE KeyHandle, 
	__in ACCESS_MASK DesiredAccess, 
	__in POBJECT_ATTRIBUTES ObjectAttributes, 
	__in ULONG TitleIndex, 
	__in_opt PUNICODE_STRING Class,
	__in ULONG CreateOptions, 
	__in HANDLE TransactionHandle, 
	__out_opt PULONG Disposition 
	);

typedef NTSTATUS( NTAPI *PFN_NtDeleteKey )( 
	__in HANDLE KeyHandle 
	);

typedef NTSTATUS( NTAPI *PFN_NtDeleteValueKey )( 
	__in HANDLE KeyHandle, 
	__in PUNICODE_STRING ValueName 
	);

typedef NTSTATUS( NTAPI *PFN_NtEnumerateKey )( 
	__in HANDLE KeyHandle, 
	__in ULONG Index, 
	__in KEY_INFORMATION_CLASS KeyInformationClass, 
	__out_opt PVOID KeyInformation, 
	__in ULONG Length,
	__out PULONG ResultLength 
	);

typedef NTSTATUS( NTAPI *PFN_NtEnumerateValueKey )( 
	__in HANDLE KeyHandle, 
	__in ULONG Index, 
	__in KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass, 
	__out_opt PVOID KeyValueInformation,
	__in ULONG Length, 
	__out PULONG ResultLength 
	);

typedef NTSTATUS( NTAPI *PFN_NtFlushKey )(
	__in HANDLE KeyHandle
	);

typedef NTSTATUS( NTAPI *PFN_NtNotifyChangeKey )(
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

typedef NTSTATUS( NTAPI *PFN_NtOpenFile )( 
	__out PHANDLE FileHandle, 
	__in ACCESS_MASK DesiredAccess, 
	__in POBJECT_ATTRIBUTES ObjectAttributes, 
	__out PIO_STATUS_BLOCK IoStatusBlock,
	__in ULONG ShareAccess, 
	__in ULONG OpenOptions 
	);

typedef NTSTATUS( NTAPI *PFN_NtOpenKey )( 
	__out PHANDLE KeyHandle, 
	__in ACCESS_MASK DesiredAccess, 
	__in POBJECT_ATTRIBUTES ObjectAttributes 
	);

typedef NTSTATUS( NTAPI *PFN_NtOpenKeyEx )( 
	__out PHANDLE KeyHandle, 
	__in ACCESS_MASK DesiredAccess, 
	__in POBJECT_ATTRIBUTES ObjectAttributes, 
	__in ULONG OpenOptions 
	);

typedef NTSTATUS( NTAPI *PFN_NtOpenKeyTransacted )(
	__out PHANDLE KeyHandle,
	__in ACCESS_MASK DesiredAccess,
	__in POBJECT_ATTRIBUTES ObjectAttributes,
	__in HANDLE TransactionHandle
	);

typedef NTSTATUS( NTAPI *PFN_NtOpenKeyTransactedEx )(
	__out PHANDLE KeyHandle,
	__in ACCESS_MASK DesiredAccess,
	__in POBJECT_ATTRIBUTES ObjectAttributes,
	__in ULONG OpenOptions,
	__in HANDLE TransactionHandle
	);

typedef NTSTATUS( NTAPI *PFN_NtQueryKey )(
	__in HANDLE KeyHandle, 
	__in KEY_INFORMATION_CLASS KeyInformationClass, 
	__out_opt PVOID KeyInformation, 
	__in ULONG Length, 
	__out PULONG ResultLength 
	);

typedef NTSTATUS( NTAPI *PFN_NtQueryObject )( 
	__in_opt HANDLE Handle, 
	__in OBJECT_INFORMATION_CLASS ObjectInformationClass, 
	__out_opt PVOID ObjectInformation, 
	__in ULONG ObjectInformationLength,
	__out_opt PULONG ReturnLength 
	);

typedef NTSTATUS( NTAPI *PFN_NtQueryValueKey )( 
	__in HANDLE KeyHandle, 
	__in PUNICODE_STRING ValueName, 
	__in KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass, 
	__out_opt PVOID KeyValueInformation,
	__in ULONG Length, 
	__out PULONG ResultLength 
	);

typedef NTSTATUS( NTAPI *PFN_NtSetValueKey )( 
	__in HANDLE KeyHandle, 
	__in PUNICODE_STRING ValueName, 
	__in_opt ULONG TitleIndex, 
	__in ULONG Type, 
	__in_opt PVOID Data, 
	__in ULONG DataSize 
	);
