
#include "ntoskrln.h"

// My little own replica of the C RTL
size_t __cdecl my_wcslen(const wchar_t* s) {
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

// This "utility" is in NtDll.dll AND in NtOsKrln. But we do not want a dependency on the first, 
// and we are not in kernel mode (so we cannot call the second). 
// Let's just rewrite it like we did with the C RTL
VOID NTAPI RtlInitUnicodeString(IN OUT PUNICODE_STRING DestinationString, IN PCWSTR SourceString) {
	SIZE_T size;
	CONST SIZE_T maxSize = (MAXUSHORT & ~1) - sizeof(UNICODE_NULL); // an even number
	if (SourceString) {
		size = my_wcslen(SourceString) * sizeof(WCHAR);
		if (size > maxSize)
			size = maxSize;

		DestinationString->Length = (USHORT)size;
		DestinationString->MaximumLength = (USHORT)size + sizeof(UNICODE_NULL);
	}
	else {
		DestinationString->Length = 0;
		DestinationString->MaximumLength = 0;
	}
	DestinationString->Buffer = (PWCHAR)SourceString;
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
	status = my_NtCreateFile(&hFile, GENERIC_WRITE | SYNCHRONIZE, &object, &ioStatus, NULL,
		FILE_ATTRIBUTE_NORMAL, 0, FILE_OVERWRITE_IF, FILE_SYNCHRONOUS_IO_NONALERT, NULL,
		0);
	if (!NT_SUCCESS(status)) {
		my_NtTerminateProcess(NULL, -1);
		return;
	}

	const wchar_t* text = L"Hello world from the Kernel\n";

	RtlZeroMemory(&ioStatus, sizeof(IO_STATUS_BLOCK));
	status = my_NtWriteFile(hFile,
		NULL, NULL, NULL,
		&ioStatus,
		(PVOID)text, sizeof(wchar_t) * my_wcslen(text),
		NULL, NULL);

	if (!NT_SUCCESS(status)) {
		my_NtClose(hFile);
		my_NtTerminateProcess(NULL, -2);
		return;
	}

	my_NtClose(hFile);
	my_NtTerminateProcess(NULL, 0);
}
