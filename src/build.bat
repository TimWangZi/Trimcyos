del a.bin
nasm asm\bootcode.inc -o asm\boot.inf
nasm asm\kernel_init.asm -o asm\ki.bin
tool\t_copy f a.bin asm\boot.inf asm\ki.bin
del asm\ki.bin
del asm\boot.inf