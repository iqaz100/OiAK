SYSEXIT = 1;
SYSCALL32 = 0x80
EXIT_SUCCES = 0

.data
result: 
        .long 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

menu_option_msg: .string "Wybierz opcje: 1. Dodawanie 2.Odejmowanie 3.Mnozenie 4. Dzielenie "
firstNumberMsg: .string "Podaj pierwsza liczbe "
secondNumberMsg: .string "Podaj druga liczbe "
testPrint: .string "test\n"
menuOption: .ascii ""
formatScan: .string "%d"
number_1: .float 0
number_2: .float 0
inputFormat: .ascii "%f"
optionFormat: .string "%c"
outputFormat: .ascii "%f\n"





.text
.global _start

_start:
pushl $firstNumberMsg   # Wczytanie pierwszej liczby
call printf
pushl $number_1
pushl $inputFormat
call scanf

pushl $secondNumberMsg  # Wczytanie drugiej liczby
call printf
pushl $number_2
pushl $inputFormat
call scanf

pushl $menu_option_msg   # Wybor dzialania(dodawanie/odejmowanie/mnozenie/dzielenie)
call printf
pushl $menuOption
pushl $optionFormat
call scanf

fld number_1
fst %st(1)
fld number_2

movb menuOption, %al
cmpb $'1', %al
je add

cmpb $'2', %al
je sub

cmpb $'3', %al
je mult

cmpb $'3', %al
je div

add:
fadd %st(1), %st(0)
jmp print

sub:
fsub %st(1), %st(0)
jmp print

mult:
fmul %st(1), %st(0)
jmp print

div:
fdiv %st(1), %st(0)
jmp print

print:
fstl (%esp)     # Wrzucenie wyniku na stos
pushl $outputFormat
call printf


movl $SYSEXIT, %eax
movl $EXIT_SUCCES, %ebx
int $SYSCALL32






