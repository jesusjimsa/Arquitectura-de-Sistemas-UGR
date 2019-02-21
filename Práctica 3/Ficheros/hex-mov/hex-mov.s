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
	in $0x60, %al         # leer código de tecla pulsada
	xor %ch, %ch
	mov %al, %cl          # almacenar código en variable carácter

	mov $0x0f, %ah        # color: blanco sobre negro

	mov %cx, %si          # digito hexadecimal
	shr $4, %si           # primera parte
	movb hex(%si), %al    # al = hex[al]
	stosw                 # imprimir caracter

	mov %cx, %si          # digito hexadecimal
	and $0xf, %si         # segunda parte
	movb hex(%si), %al    # al = hex[al]
	stosw                 # imprimir caracter

	mov $0x20, %al        # código EOI
	out %al, $0x20        # enviar EOI

	iret                  # volver de la interrupción

###############################################################################

hex:    .ascii "0123456789ABCDEF"  # dígitos hexadecimales

###############################################################################

	.org 510          # posición de memoria 510
	.word 0xAA55      # marca del sector de arranque

###############################################################################

