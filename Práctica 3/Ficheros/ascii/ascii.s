.code16            # código de 16 bits

.text              # sección de código
	.globl _start  # punto de entrada

_start:
	xor %ax, %ax      #                                |
	mov %ax, %ss      # ss = 0                         | pila en
	mov $0x9c00, %sp  # sp = 0x09c00 = 0x7c00 + 0x2000 |  ss:sp

	mov $0xb800, %ax  # 0xb800 --> ax |
	mov %ax, %es      # ax --> es     | video --> es:di = 0xb8000
	xor %di, %di      # 0 --> di      |

	cli                      # deshabilitar interrupciones
	mov $0x09, %bx           # interrupción hardware del teclado
	shl $2, %bx              # bx = bx * 4, dirección del vector int.
	movw $controlador, (%bx) # cambiar el desplazamiento la int. teclado
	movw %cs, 2(%bx)         # cambiar el segmento de la int. teclado
	sti                      # habilitar interrupciones

stop:
	hlt                    # ¿hace falta?
	jmp stop               # bucle vacío

###############################################################################

controlador:
	in $0x60, %al       # leer código de tecla pulsada
	mov %al, (buffer)   # almacenar código en variable carácter

	mov $0x20, %al      # código EOI
	out %al, $0x20      # enviar EOI

	mov $0x0f, %ah      # color: blanco sobre negro
	mov (buffer), %al   # digito hexadecimal

	cmp $0x02, %al      # 1
	jl fin
	cmp $0x0b, %al      # 0
	jg q
	sub $0x02, %al      # indexar desde 0
	mov $numero, %bx    # tabla de traducción
	jmp imprimir

q:	cmp $0x10, %al      # q
	jl fin
	cmp $0x19, %al      # p
	jg a
	sub $0x10, %al      # indexar desde 0
	mov $qwerty, %bx    # tabla de traducción
	jmp imprimir

a:	cmp $0x1e, %al      # a
	jl fin
	cmp $0x26, %al      # l
	jg z
	sub $0x1e, %al      # indexar desde 0
	mov $asdfgh, %bx    # tabla de traducción
	jmp imprimir

z:	cmp $0x2c, %al      # z
	jl fin
	cmp $0x32, %al      # m
	jg b
	sub $0x2c, %al      # indexar desde 0
	mov $zxcvbn, %bx    # tabla de traducción
	jmp imprimir

b:	cmp $0x39, %al      # ' '
	jne fin
	sub $0x39, %al      # indexar desde 0
	mov $blanco, %bx    # tabla de traducción

imprimir:
	xlat                # traducir, al = (bx + al)
	stosw               # imprimir caracter

fin:
	iret                # volver de la interrupción

###############################################################################

buffer: .byte 0  # datos del puerto 0x60

numero: .ascii "1234567890"
qwerty: .ascii "qwertyuiop"
asdfgh: .ascii "asdfghjkl"
zxcvbn: .ascii "zxcvbnm"
blanco: .ascii " "

###############################################################################

	.org 510          # posición de memoria 510
	.word 0xAA55      # marca del sector de arranque

###############################################################################

