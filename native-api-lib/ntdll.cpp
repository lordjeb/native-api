#include "ntdll.h"


NtApi::NtApi()
	: m_hLib(NULL), m_pfnNtClose(NULL), m_pfnNtCreateFile(NULL), m_pfnNtCreateKey(NULL), m_pfnNtDeleteKey(NULL), m_pfnNtDeleteValueKey(NULL),
	m_pfnNtEnumerateKey(NULL), m_pfnNtEnumerateValueKey(NULL), m_pfnNtOpenFile(NULL), m_pfnNtOpenKey(NULL), m_pfnNtOpenKeyEx(NULL), m_pfnNtQueryKey(NULL),
	m_pfnNtQueryObject(NULL), m_pfnNtQueryValueKey(NULL), m_pfnNtSetValueKey(NULL)
{
	m_hLib = LoadLibraryW( L"ntdll.dll" );

	m_pfnNtClose = (PFN_NtClose) GetProcAddress( m_hLib, "NtClose" );
	m_pfnNtCreateFile = (PFN_NtCreateFile) GetProcAddress( m_hLib, "NtCreateFile" );
	m_pfnNtCreateKey = (PFN_NtCreateKey) GetProcAddress( m_hLib, "NtCreateKey" );
	m_pfnNtDeleteKey = (PFN_NtDeleteKey) GetProcAddress( m_hLib, "NtDeleteKey" );
	m_pfnNtDeleteValueKey = (PFN_NtDeleteValueKey) GetProcAddress( m_hLib, "NtDeleteValueKey" );
	m_pfnNtEnumerateKey = (PFN_NtEnumerateKey) GetProcAddress( m_hLib, "NtEnumerateKey" );
	m_pfnNtEnumerateValueKey = (PFN_NtEnumerateValueKey) GetProcAddress( m_hLib, "NtEnumerateValueKey" );
	m_pfnNtOpenFile = (PFN_NtOpenFile) GetProcAddress( m_hLib, "NtOpenFile" );
	m_pfnNtOpenKey = (PFN_NtOpenKey) GetProcAddress( m_hLib, "NtOpenKey" );
	m_pfnNtOpenKeyEx = (PFN_NtOpenKeyEx) GetProcAddress( m_hLib, "NtOpenKeyEx" );
	m_pfnNtQueryKey = (PFN_NtQueryKey) GetProcAddress( m_hLib, "NtQueryKey" );
	m_pfnNtQueryObject = (PFN_NtQueryObject) GetProcAddress( m_hLib, "NtQueryObject" );
	m_pfnNtQueryValueKey = (PFN_NtQueryValueKey) GetProcAddress( m_hLib, "NtQueryValueKey" );
	m_pfnNtSetValueKey = (PFN_NtSetValueKey) GetProcAddress( m_hLib, "NtSetValueKey" );
}

NtApi::~NtApi()
{
	FreeLibrary( m_hLib );
}

NTSTATUS NtApi::NtClose( __in HANDLE Handle )
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

NTSTATUS NtApi::NtCreateFile( __out PHANDLE FileHandle, __in ACCESS_MASK DesiredAccess, __in POBJECT_ATTRIBUTES ObjectAttributes, __out PIO_STATUS_BLOCK IoStatusBlock,
							  __in_opt PLARGE_INTEGER AllocationSize, __in ULONG FileAttributes, __in ULONG ShareAccess, __in ULONG CreateDisposition, __in ULONG CreateOptions,
							  __in PVOID EaBuffer, __in ULONG EaLength )
{
	return m_pfnNtCreateFile( FileHandle, DesiredAccess, ObjectAttributes, IoStatusBlock, AllocationSize, FileAttributes, ShareAccess, CreateDisposition, CreateOptions, EaBuffer, EaLength );
}

NTSTATUS NtApi::NtCreateKey( __out PHANDLE KeyHandle, __in ACCESS_MASK DesiredAccess, __in POBJECT_ATTRIBUTES ObjectAttributes, __in ULONG TitleIndex, __in_opt PUNICODE_STRING Class,
							 __in ULONG CreateOptions, __out_opt PULONG Disposition )
{
	return m_pfnNtCreateKey( KeyHandle, DesiredAccess, ObjectAttributes, TitleIndex, Class, CreateOptions, Disposition );
}

NTSTATUS NtApi::NtDeleteKey( __in HANDLE KeyHandle )
{
	return m_pfnNtDeleteKey( KeyHandle );
}

NTSTATUS NtApi::NtDeleteValueKey( __in HANDLE KeyHandle, __in PUNICODE_STRING ValueName )
{
	return m_pfnNtDeleteValueKey( KeyHandle, ValueName );
}

NTSTATUS NtApi::NtEnumerateKey( __in HANDLE KeyHandle, __in ULONG Index, __in KEY_INFORMATION_CLASS KeyInformationClass, __out_opt PVOID KeyInformation, __in ULONG Length,
								__out PULONG ResultLength )
{
	return m_pfnNtEnumerateKey( KeyHandle, Index, KeyInformationClass, KeyInformation, Length, ResultLength );
}

NTSTATUS NtApi::NtEnumerateValueKey( __in HANDLE KeyHandle, __in ULONG Index, __in KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass, __out_opt PVOID KeyValueInformation, 
									 __in ULONG Length, __out PULONG ResultLength )
{
	return m_pfnNtEnumerateValueKey( KeyHandle, Index, KeyValueInformationClass, KeyValueInformation, Length, ResultLength );
}

NTSTATUS NtApi::NtOpenFile( __out PHANDLE FileHandle, __in ACCESS_MASK DesiredAccess, __in POBJECT_ATTRIBUTES ObjectAttributes, __out PIO_STATUS_BLOCK IoStatusBlock,
							__in ULONG ShareAccess, __in ULONG OpenOptions )
{
	return m_pfnNtOpenFile( FileHandle, DesiredAccess, ObjectAttributes, IoStatusBlock, ShareAccess, OpenOptions );
}

NTSTATUS NtApi::NtOpenKey( __out PHANDLE KeyHandle, __in ACCESS_MASK DesiredAccess, __in POBJECT_ATTRIBUTES ObjectAttributes )
{
	return m_pfnNtOpenKey( KeyHandle, DesiredAccess, ObjectAttributes );
}

NTSTATUS NtApi::NtOpenKeyEx( __out PHANDLE KeyHandle, __in ACCESS_MASK DesiredAccess, __in POBJECT_ATTRIBUTES ObjectAttributes, __in ULONG OpenOptions )
{
	//	API is only implemented on Windows 7 and later
	return m_pfnNtOpenKeyEx ? m_pfnNtOpenKeyEx( KeyHandle, DesiredAccess, ObjectAttributes, OpenOptions ) : STATUS_PROCEDURE_NOT_FOUND;
}

NTSTATUS NtApi::NtQueryKey( __in HANDLE KeyHandle, __in KEY_INFORMATION_CLASS KeyInformationClass, __out_opt PVOID KeyInformation, __in ULONG Length, __out PULONG ResultLength )
{
	return m_pfnNtQueryKey( KeyHandle, KeyInformationClass, KeyInformation, Length, ResultLength );
}

NTSTATUS NtApi::NtQueryObject( __in_opt HANDLE Handle, __in OBJECT_INFORMATION_CLASS ObjectInformationClass, __out_opt PVOID ObjectInformation, __in ULONG ObjectInformationLength,
							   __out_opt PULONG ReturnLength )
{
	return m_pfnNtQueryObject( Handle, ObjectInformationClass, ObjectInformation, ObjectInformationLength, ReturnLength );
}

NTSTATUS NtApi::NtQueryValueKey( __in HANDLE KeyHandle, __in PUNICODE_STRING ValueName, __in KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass, __out_opt PVOID KeyValueInformation,
								 __in ULONG Length, __out PULONG ResultLength )
{
	return m_pfnNtQueryValueKey( KeyHandle, ValueName, KeyValueInformationClass, KeyValueInformation, Length, ResultLength );
}

NTSTATUS NtApi::NtSetValueKey( __in HANDLE KeyHandle, __in PUNICODE_STRING ValueName, __in_opt ULONG TitleIndex, __in ULONG Type, __in_opt PVOID Data, __in ULONG DataSize )
{
	return m_pfnNtSetValueKey( KeyHandle, ValueName, TitleIndex, Type, Data, DataSize );
}
