.code16             # código de 16 bits

.text               # sección de código
	.globl _start   # punto de entrada al código

_start:
	movb $0x0e, %ah  # imprimir carácter
	movb $0x00, %bh  # página 0
	movb $0x0f, %bl  # color del texto blanco
	movw $msg, %si   # msg --> si
char:
	lodsb            # ds:[si++] --> al
	or %al, %al      # ¿es al 0?
	jz fin           # si al == 0 acabar
	int $0x10        # llamada a la BIOS
	jmp char         # imprimir siguiente carácter
fin:
	cli              # deshabilitar las interrupciones
	hlt              # detener el procesador

msg: .asciz "cognito, ergo sum"  # datos en la sección de código

	.org 510         # saltar 510 bytes
	.word 0xAA55     # marca del sector de arranque
