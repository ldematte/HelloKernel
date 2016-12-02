.code
 
my_NtCreateFile  PROC 
		mov         r10, rcx
		mov         eax, 55h
		syscall
		ret 
my_NtCreateFile  ENDP

my_NtClose  PROC
		mov         r10, rcx
		mov         eax, 0Fh
		syscall
		ret
my_NtClose  ENDP

my_NtWriteFile  PROC
		mov         r10, rcx
		mov         eax, 8
		syscall
		ret 
my_NtWriteFile  ENDP

my_NtTerminateProcess  PROC
		mov         r10, rcx
		mov         eax,2Ch
		syscall
		ret 
my_NtTerminateProcess  ENDP
 
END