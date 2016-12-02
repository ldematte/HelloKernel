#include <windows.h>

size_t __cdecl my_wcslen(const wchar_t* s) {
	size_t len = 0;
	while (s && *(s + len))
		++len;
	return len;
}

void entry() {
	HANDLE hFile = CreateFile(L"C:\\testfile.txt", GENERIC_WRITE, 0, NULL,  
							  CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
		ExitProcess(-1);

	const wchar_t* text = L"Hello world from Win32\n";
	DWORD bytesWritten;

	BOOL errorFlag = WriteFile(hFile, text, sizeof(wchar_t) * my_wcslen(text),
		                       &bytesWritten, NULL);

	if (!errorFlag)
		ExitProcess(-2);

	CloseHandle(hFile);
	ExitProcess(0);
}
