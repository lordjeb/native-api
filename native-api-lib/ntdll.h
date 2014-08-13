#pragma once
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <Windows.h>
#include <winternl.h>
#pragma warning( push )
#pragma warning( disable : 4005 )
#include <ntstatus.h>
#pragma warning( pop )
#include "undocumented.h"

typedef NTSTATUS (NTAPI *PFN_NtClose)( __in HANDLE Handle );
typedef NTSTATUS (NTAPI *PFN_NtCreateFile)( __out PHANDLE FileHandle, __in ACCESS_MASK DesiredAccess, __in POBJECT_ATTRIBUTES ObjectAttributes, __out PIO_STATUS_BLOCK IoStatusBlock,
											__in_opt PLARGE_INTEGER AllocationSize, __in ULONG FileAttributes, __in ULONG ShareAccess, __in ULONG CreateDisposition, __in ULONG CreateOptions,
											__in PVOID EaBuffer, __in ULONG EaLength );
typedef NTSTATUS (NTAPI *PFN_NtCreateKey)( __out PHANDLE KeyHandle, __in ACCESS_MASK DesiredAccess, __in POBJECT_ATTRIBUTES ObjectAttributes, __in ULONG TitleIndex, __in_opt PUNICODE_STRING Class,
										   __in ULONG CreateOptions, __out_opt PULONG Disposition );
typedef NTSTATUS (NTAPI *PFN_NtDeleteKey)( __in HANDLE KeyHandle );
typedef NTSTATUS (NTAPI *PFN_NtDeleteValueKey)( __in HANDLE KeyHandle, __in PUNICODE_STRING ValueName );
typedef NTSTATUS (NTAPI *PFN_NtEnumerateKey)( __in HANDLE KeyHandle, __in ULONG Index, __in KEY_INFORMATION_CLASS KeyInformationClass, __out_opt PVOID KeyInformation, __in ULONG Length,
											  __out PULONG ResultLength );
typedef NTSTATUS (NTAPI *PFN_NtEnumerateValueKey)( __in HANDLE KeyHandle, __in ULONG Index, __in KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass, __out_opt PVOID KeyValueInformation, 
												   __in ULONG Length, __out PULONG ResultLength );
typedef NTSTATUS (NTAPI *PFN_NtOpenFile)( __out PHANDLE FileHandle, __in ACCESS_MASK DesiredAccess, __in POBJECT_ATTRIBUTES ObjectAttributes, __out PIO_STATUS_BLOCK IoStatusBlock,
										  __in ULONG ShareAccess, __in ULONG OpenOptions );
typedef NTSTATUS (NTAPI *PFN_NtOpenKey)( __out PHANDLE KeyHandle, __in ACCESS_MASK DesiredAccess, __in POBJECT_ATTRIBUTES ObjectAttributes );
typedef NTSTATUS (NTAPI *PFN_NtOpenKeyEx)( __out PHANDLE KeyHandle, __in ACCESS_MASK DesiredAccess, __in POBJECT_ATTRIBUTES ObjectAttributes, __in ULONG OpenOptions );
typedef NTSTATUS (NTAPI *PFN_NtQueryKey)( __in HANDLE KeyHandle, __in KEY_INFORMATION_CLASS KeyInformationClass, __out_opt PVOID KeyInformation, __in ULONG Length, __out PULONG ResultLength );
typedef NTSTATUS (NTAPI *PFN_NtQueryObject)( __in_opt HANDLE Handle, __in OBJECT_INFORMATION_CLASS ObjectInformationClass, __out_opt PVOID ObjectInformation, __in ULONG ObjectInformationLength,
											 __out_opt PULONG ReturnLength );
typedef NTSTATUS (NTAPI *PFN_NtQueryValueKey)( __in HANDLE KeyHandle, __in PUNICODE_STRING ValueName, __in KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass, __out_opt PVOID KeyValueInformation,
											   __in ULONG Length, __out PULONG ResultLength );
typedef NTSTATUS (NTAPI *PFN_NtSetValueKey)( __in HANDLE KeyHandle, __in PUNICODE_STRING ValueName, __in_opt ULONG TitleIndex, __in ULONG Type, __in_opt PVOID Data, __in ULONG DataSize );


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

	NTSTATUS NtClose( __in HANDLE Handle );
	NTSTATUS NtCreateFile( __out PHANDLE FileHandle, __in ACCESS_MASK DesiredAccess, __in POBJECT_ATTRIBUTES ObjectAttributes, __out PIO_STATUS_BLOCK IoStatusBlock,
						   __in_opt PLARGE_INTEGER AllocationSize, __in ULONG FileAttributes, __in ULONG ShareAccess, __in ULONG CreateDisposition, __in ULONG CreateOptions,
						   __in PVOID EaBuffer, __in ULONG EaLength );
	NTSTATUS NtCreateKey( __out PHANDLE KeyHandle, __in ACCESS_MASK DesiredAccess, __in POBJECT_ATTRIBUTES ObjectAttributes, __in ULONG TitleIndex, __in_opt PUNICODE_STRING Class,
						  __in ULONG CreateOptions, __out_opt PULONG Disposition );
	NTSTATUS NtDeleteKey( __in HANDLE KeyHandle );
	NTSTATUS NtDeleteValueKey( __in HANDLE KeyHandle, __in PUNICODE_STRING ValueName );
	NTSTATUS NtEnumerateKey( __in HANDLE KeyHandle, __in ULONG Index, __in KEY_INFORMATION_CLASS KeyInformationClass, __out_opt PVOID KeyInformation, __in ULONG Length,
							 __out PULONG ResultLength );
	NTSTATUS NtEnumerateValueKey( __in HANDLE KeyHandle, __in ULONG Index, __in KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass, __out_opt PVOID KeyValueInformation, 
								  __in ULONG Length, __out PULONG ResultLength );
	NTSTATUS NtOpenFile( __out PHANDLE FileHandle, __in ACCESS_MASK DesiredAccess, __in POBJECT_ATTRIBUTES ObjectAttributes, __out PIO_STATUS_BLOCK IoStatusBlock,
						 __in ULONG ShareAccess, __in ULONG OpenOptions );
	NTSTATUS NtOpenKey( __out PHANDLE KeyHandle, __in ACCESS_MASK DesiredAccess, __in POBJECT_ATTRIBUTES ObjectAttributes );
	NTSTATUS NtOpenKeyEx( __out PHANDLE KeyHandle, __in ACCESS_MASK DesiredAccess, __in POBJECT_ATTRIBUTES ObjectAttributes, __in ULONG OpenOptions );
	NTSTATUS NtQueryKey( __in HANDLE KeyHandle, __in KEY_INFORMATION_CLASS KeyInformationClass, __out_opt PVOID KeyInformation, __in ULONG Length, __out PULONG ResultLength );
	NTSTATUS NtQueryObject( __in_opt HANDLE Handle, __in OBJECT_INFORMATION_CLASS ObjectInformationClass, __out_opt PVOID ObjectInformation, __in ULONG ObjectInformationLength,
							__out_opt PULONG ReturnLength );
	NTSTATUS NtQueryValueKey( __in HANDLE KeyHandle, __in PUNICODE_STRING ValueName, __in KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass, __out_opt PVOID KeyValueInformation,
								  __in ULONG Length, __out PULONG ResultLength );
	NTSTATUS NtSetValueKey( __in HANDLE KeyHandle, __in PUNICODE_STRING ValueName, __in_opt ULONG TitleIndex, __in ULONG Type, __in_opt PVOID Data, __in ULONG DataSize );

private:
	HMODULE m_hLib;
	PFN_NtClose m_pfnNtClose;
	PFN_NtCreateFile m_pfnNtCreateFile;
	PFN_NtCreateKey m_pfnNtCreateKey;
	PFN_NtDeleteKey m_pfnNtDeleteKey;
	PFN_NtDeleteValueKey m_pfnNtDeleteValueKey;
	PFN_NtEnumerateKey m_pfnNtEnumerateKey;
	PFN_NtEnumerateValueKey m_pfnNtEnumerateValueKey;
	PFN_NtOpenFile m_pfnNtOpenFile;
	PFN_NtOpenKey m_pfnNtOpenKey;
	PFN_NtOpenKeyEx m_pfnNtOpenKeyEx;
	PFN_NtQueryKey m_pfnNtQueryKey;
	PFN_NtQueryObject m_pfnNtQueryObject;
	PFN_NtQueryValueKey m_pfnNtQueryValueKey;
	PFN_NtSetValueKey m_pfnNtSetValueKey;
};
