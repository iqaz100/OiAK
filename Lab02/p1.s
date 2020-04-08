SYSEXIT = 1;
SYSCALL32 = 0x00
EXIT_SUCCES = 0

.data
number_1:
    	.long 0x10304008, 0x701100FF, 0x45100020, 0x08570030
		#.long 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
number_2:
    	.long 0xF040500C, 0x00220026, 0x321000CB, 0x04520031
		#.long 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
result: 
        .long 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

menu_option_msg: .string "Wybierz opcje: 1. Dodawanie 2.Odejmowanie"
formatScan: .string "%d"



.text
.global _start

_start:


movl $4, %ecx

add_loop:
decl %ecx
movl number_1(,%ecx,4),%eax
movl number_2(,%ecx,4),%ebx

adcl %eax,%ebx #dodanie dwoch liczb, wynik w ebx

jnc noclflag
incl result(,%ecx,4) #jesli jest przeniesienie to dodaj 1 do wyniku
clc #a następnie wyzeruj przeniesienie

noclflag:
incl %ecx
addl %ebx, result(, %ecx, 4)

loop add_loop  #zamist lopp sprawdzic czy ecx=0 jesli nie to jump to _add_loop 

movl $SYSEXIT, %eax
movl $EXIT_SUCCES, %ebx
int $SYSCALL32






