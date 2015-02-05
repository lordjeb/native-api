#include "stdafx.h"
#include "CppUnitTest.h"
#include <stdio.h>
#include "ntdll.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace nativeapitests
{		
	VOID NTAPI ApcRoutine(
		__in PVOID ApcContext,
		__in PIO_STATUS_BLOCK IoStatusBlock,
		__in ULONG Reserved
		)
	{
		SetEvent( *(PHANDLE) ApcContext );
	}

	TEST_CLASS( RegistryTests )
	{
	public:
		NtApi nt;
		const wchar_t* userSid = L"S-1-5-21-1153546953-3807600753-4089874444-1001";

		TEST_METHOD( ClosingInvalidHandleReturnsError1 )
		{
			HANDLE hTest = INVALID_HANDLE_VALUE;
			Assert::AreEqual( STATUS_INVALID_HANDLE, nt.NtClose( hTest ) );
		}

		TEST_METHOD( ClosingInvalidHandleReturnsError2 )
		{
			HANDLE hTest = 0L;
			Assert::AreEqual( STATUS_INVALID_HANDLE, nt.NtClose( hTest ) );
		}

		TEST_METHOD( OpenKeySucceeds )
		{
			UNICODE_STRING keyName = RTL_CONSTANT_STRING( L"\\REGISTRY\\MACHINE\\SOFTWARE\\Microsoft" );
			OBJECT_ATTRIBUTES oa = RTL_CONSTANT_OBJECT_ATTRIBUTES( 0L, &keyName, OBJ_CASE_INSENSITIVE );
			HANDLE hKey;
			Assert::AreEqual( STATUS_SUCCESS, nt.NtOpenKey( &hKey, KEY_READ, &oa ) );
			Assert::AreEqual( STATUS_SUCCESS, nt.NtClose( hKey ) );
		}

		TEST_METHOD( OpenKeyExFailsWhenBackupPrivilegeNotEnabled )
		{
			UNICODE_STRING keyName = RTL_CONSTANT_STRING( L"\\REGISTRY\\MACHINE\\SOFTWARE\\Microsoft" );
			OBJECT_ATTRIBUTES oa = RTL_CONSTANT_OBJECT_ATTRIBUTES( 0L, &keyName, OBJ_CASE_INSENSITIVE );
			HANDLE hKey;
			Assert::AreEqual( STATUS_ACCESS_DENIED, nt.NtOpenKeyEx( &hKey, KEY_READ, &oa, REG_OPTION_BACKUP_RESTORE ) );
		}

		TEST_METHOD( NotifyTester )
		{
			wchar_t keyName[ MAX_PATH ];
			swprintf_s( keyName, L"\\REGISTRY\\USER\\%s\\Software\\NativeApiLibTests", userSid );
			UNICODE_STRING KeyName = RTL_CONSTANT_STRING( keyName );
			OBJECT_ATTRIBUTES oa = RTL_CONSTANT_OBJECT_ATTRIBUTES( 0L, &KeyName, OBJ_CASE_INSENSITIVE );
			HANDLE hKey;
			ULONG ulDisposition;
			Assert::AreEqual( STATUS_SUCCESS, nt.NtCreateKey( &hKey, KEY_ALL_ACCESS, &oa, 0, nullptr, REG_OPTION_VOLATILE, &ulDisposition ) );
			Assert::AreEqual( (ULONG) REG_CREATED_NEW_KEY, ulDisposition );

			__try
			{
				HANDLE hEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
				IO_STATUS_BLOCK iosb;
				Assert::AreEqual( STATUS_PENDING, nt.NtNotifyChangeKey( hKey, NULL, (PIO_APC_ROUTINE)ApcRoutine, &hEvent, &iosb, REG_NOTIFY_CHANGE_NAME | REG_NOTIFY_CHANGE_LAST_SET, TRUE, NULL, 0, TRUE ) );

				UNICODE_STRING ValueName = RTL_CONSTANT_STRING( L"TestValue" );
				Assert::AreEqual( STATUS_SUCCESS, nt.NtSetValueKey( hKey, &ValueName, 0, REG_SZ, ValueName.Buffer, ValueName.Length + sizeof( wchar_t ) ) );

				//	Cause the thread to enter an alterable state so that it can call the APC routine(s)
				Assert::AreEqual( (DWORD) WAIT_IO_COMPLETION, SleepEx( 0, TRUE ) );
				Assert::AreEqual( (DWORD) WAIT_OBJECT_0, WaitForSingleObject( hEvent, INFINITE ) );
				Assert::AreEqual( STATUS_NOTIFY_ENUM_DIR, iosb.Status );
			}
			__finally
			{
				Assert::AreEqual( STATUS_SUCCESS, nt.NtDeleteKey( hKey ) );
				Assert::AreEqual( STATUS_SUCCESS, nt.NtClose( hKey ) );
			}
		}
	};
}