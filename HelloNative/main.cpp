#define _WIN32_WINNT 0x0602
#define _AMD64_

#include <ntddk.h>

size_t __cdecl wcslen(const wchar_t* s) {
	size_t len = 0;
	while (s && *(s + len))
		++len;
	return len;
}

void* memset(void * ptr, int value, size_t num) {
	for (int i = 0; i < num; ++i) {
		((unsigned char*)ptr)[i] = (unsigned char)value;
	}
	return ptr;
}

void entry() {

	UNICODE_STRING fn;
	OBJECT_ATTRIBUTES object{ 0 };
	IO_STATUS_BLOCK ioStatus{ 0 };
	HANDLE hFile;
	NTSTATUS status;

	object.Length = sizeof(object);
	object.Attributes = OBJ_CASE_INSENSITIVE;
	RtlInitUnicodeString(&fn, L"\\??\\C:\\testfile.txt");
	object.ObjectName = &fn;
	status = ZwCreateFile(&hFile, GENERIC_WRITE | SYNCHRONIZE, &object, &ioStatus, NULL,
		FILE_ATTRIBUTE_NORMAL, 0, FILE_OVERWRITE_IF, FILE_SYNCHRONOUS_IO_NONALERT, NULL,
		0);
	if (!NT_SUCCESS(status)) {
		ZwTerminateProcess(NULL, -1);
		return;
	}

	const wchar_t* text = L"Hello world from NtDll\n";

	RtlZeroMemory(&ioStatus, sizeof(IO_STATUS_BLOCK));
	status = ZwWriteFile(hFile, 
		NULL, NULL, NULL, 
		&ioStatus,
		(PVOID)text, sizeof(wchar_t) * wcslen(text),
		NULL, NULL);

	if (!NT_SUCCESS(status)) {
		ZwClose(hFile);
		ZwTerminateProcess(NULL, -2); 
		return;
	}

	ZwClose(hFile);
	ZwTerminateProcess(NULL, 0);
}
