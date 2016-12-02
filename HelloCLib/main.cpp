#include <stdio.h>
#include <string.h>

int main() {

	FILE* file = fopen("C:\\testfile.txt", "w");
	if (!file)
		return -1;
	
	const wchar_t* text = L"Hello world\n";
	fwrite(text, sizeof(wchar_t), wcslen(text), file);
	fclose(file);
	
	return 0;
}