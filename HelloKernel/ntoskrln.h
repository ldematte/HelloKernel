#pragma once

#define _WIN32_WINNT 0x0602
#define _AMD64_

#include <winternl.h>

const size_t MAXUSHORT = (USHORT)-1;

//extern "C" NTSTATUS my_NtCreateFile_imp(void);
//extern "C" NTSTATUS my_NtClose_imp(void);
//extern "C" NTSTATUS my_NtWriteFile_imp(void);
//extern "C" NTSTATUS my_NtTerminateProcess_imp(void);

extern "C" {
	NTSTATUS
		NTAPI
		my_NtCreateFile(
			OUT PHANDLE FileHandle,
			IN ACCESS_MASK DesiredAccess,
			IN POBJECT_ATTRIBUTES ObjectAttributes,
			OUT PIO_STATUS_BLOCK IoStatusBlock,
			IN PLARGE_INTEGER AllocationSize OPTIONAL,
			IN ULONG FileAttributes,
			IN ULONG ShareAccess,
			IN ULONG CreateDisposition,
			IN ULONG CreateOptions,
			IN PVOID EaBuffer OPTIONAL,
			IN ULONG EaLength
		);

	NTSTATUS
		NTAPI
		my_NtClose(
			IN HANDLE Handle
		);

	NTSTATUS
		NTAPI
		my_NtTerminateProcess(
			_In_opt_ HANDLE ProcessHandle,
			_In_ NTSTATUS ExitStatus
		);

	NTSTATUS
		NTAPI
		my_NtWriteFile(
			_In_ HANDLE FileHandle,
			_In_opt_ HANDLE Event,
			_In_opt_ PIO_APC_ROUTINE ApcRoutine,
			_In_opt_ PVOID ApcContext,
			_Out_ PIO_STATUS_BLOCK IoStatusBlock,
			_In_reads_bytes_(Length) PVOID Buffer,
			_In_ ULONG Length,
			_In_opt_ PLARGE_INTEGER ByteOffset,
			_In_opt_ PULONG Key
		);
}

