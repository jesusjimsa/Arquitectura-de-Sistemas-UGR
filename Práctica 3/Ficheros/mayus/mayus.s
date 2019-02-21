.code16            # código de 16 bits

.text              # sección de código
	.globl _start  # punto de entrada

_start:
	xor %ax, %ax      # ax = 0                         |
	mov %ax, %ss      # ss = 0                         | pila en
	mov $0x9c00, %sp  # sp = 0x09c00 = 0x7c00 + 0x2000 |  ss:sp

	mov $0xb800, %ax  # 0xb800 --> ax |
	mov %ax, %es      # ax --> es     | video --> es:di = 0xb8000
	xor %di, %di      # 0 --> di      |

	cli                      # deshabilitar interrupciones
	mov $0x09, %bx           # interrupción hardware del teclado
	shl $2, %bx              # bx = bx * 4, dirección del vector int.
	movw $controlador, (%bx) # cambiar el desplazamiento la int. teclado
	movw %ds, 2(%bx)         # cambiar el segmento de la int. teclado
	sti                      # habilitar interrupciones

stop:
	hlt                    # ¿hace falta?
	jmp stop               # bucle vacío

###############################################################################

controlador:
	in $0x60, %al       # leer código de tecla pulsada
	mov %al, %cl        # guardar código

	mov $0x20, %al      # código EOI
	out %al, $0x20      # enviar EOI

	mov $0x0f, %ah      # color: blanco sobre negro
	mov %cl, %al        # recuperar código

	cmp $0x2a, %al      # shift izquierdo encendido
	je shift_on

	cmp $0x36, %al      # shift derecho encendido
	je shift_on

	cmp $0xaa, %al      # shift izquierdo apagado
	je shift_off

	cmp $0xb6, %al      # shift derecho apagado
	je shift_off

	cmp $0x02, %al      # 1
	jl fin
	cmp $0x40, %al      # ' '
	jg fin

imprimir:
	sub $2, %al         # indexar desde 0
	mov $minus, %bx     # tabla de traducción
	mov (shift), %cl    # shift activo?
	or %cl, %cl
	jz char
	mov $mayus, %bx
char:
	xlat                # traducir, al = (bx + al)
	stosw               # imprimir caracter
	jmp fin

shift_on:
	movb $1, (shift)
	jmp fin

shift_off:
	movb $0, (shift)
	jmp fin

fin:
	iret                # volver de la interrupción

###############################################################################

shift: .byte 0 # shift desactivado por defecto

minus: .ascii "1234567890....qwertyuiop....asdfghjkl.....zxcvbnm.... "
mayus: .ascii "..............QWERTYUIOP....ASDFGHJKL.....ZXCVBNM.... "

###############################################################################

	.org 510          # posición de memoria 510
	.word 0xAA55      # marca del sector de arranque

###############################################################################

