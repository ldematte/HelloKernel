# HelloKernel
Can you write a no-deps, kernel-only, windows program?

Start with a simple "Hello world" (written in a file), C console application, `HelloCLib`.

Step 1: remove all dependencies on the CRT (C Runtime library/DLL), use only Win32 functions: `HelloWin32`

Step 2: remove dependencies on `kernel32` etc., and use only the _Native API_ (ntdll.dll) `HelloNative`

Step 3: remove dependency on `ntdll`, _trap_ directly into the kernel (ntoskrln): `HelloKernel`
