SYSEXIT = 1;
SYSCALL32 = 0x00
EXIT_SUCCES = 0

.data
number_1:
    	.long 0xF0304008, 0x101100F0, 0x45100020, 0x08570030
		#.long 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
number_2:
    	.long 0xF040500C, 0xD2205020, 0x321000CB, 0x04520031
		#.long 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
result: 
        .long 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

menu_option_msg: .string "Wybierz opcje: 1. Dodawanie 2.Odejmowanie"
menu_option: .int 0



.text
.global _start

_start:



movl $4, %ecx

add_loop:
decl %ecx
movl number_1(,%ecx,4),%eax
movl number_2(,%ecx,4),%ebx

subl %ebx,%eax #odjecie drugiej liczby od pierwszej, wynik w eax

jnc noclflag
decl result(,%ecx,4) #jesli jest przeniesienie to odejmij 1 od wyniku
clc #a następnie wyzeruj przeniesienie

noclflag:
incl %ecx
addl %eax, result(, %ecx, 4)

loop add_loop  #zamist lopp sprawdzic czy ecx=0 jesli nie to jump to _add_loop 

movl $SYSEXIT, %eax
movl $EXIT_SUCCES, %ebx
int $SYSCALL32
