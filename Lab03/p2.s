
SYSEXIT = 1;
SYSCALL32 = 0x80
EXIT_SUCCES = 0

.data

menu_option_msg: .string "Wybierz opcje: 1. Dodawanie 2.Odejmowanie 3.Mnozenie 4. Dzielenie "
firstNumberMsg: .string "Podaj pierwsza liczbe "
secondNumberMsg: .string "Podaj druga liczbe "
menuOption: .ascii ""
formatScan: .string "%d"
number_1: .double 0
number_2: .double 0
inputFormat: .ascii "%lf"
optionFormat: .string "%c"
outputFormat: .string "%.15lf\n"
result: .double 0

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

fldl number_2
fst %st(1)
fldl number_1

xor %eax, %eax

movb menuOption, %al
cmpb $'1', %al
je add

cmpb $'2', %al
je sub

cmpb $'3', %al
je mult

cmpb $'4', %al
je div

print:
fstl (result)     # Wrzucenie wyniku na do result
pushl result+4
pushl result
pushl $outputFormat
call printf

movl $SYSEXIT, %eax
movl $EXIT_SUCCES, %ebx
int $SYSCALL32

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
