all: p1 #p2

p1: p1.o
		ld -m elf_i386 -dynamic-linker /lib/ld-linux.so.2 -lc -o p1 p1.o

p1.o: p1.s
		as --32 --gstabs -o p1.o p1.s

#p2: p2.o
		#ld -m elf_i386 -dynamic-linker /lib/ld-linux.so.2 -lc -o p2 p2.o

#p2.o: p2.s
		#as --32 --gstabs -o p2.o p2.s
