del a.bin
nasm bootcode.inc -o boot.inf
nasm kernel_init.asm -o ki.bin
t_copy f a.bin boot.inf ki.bin
del ki.bin
del boot.inf