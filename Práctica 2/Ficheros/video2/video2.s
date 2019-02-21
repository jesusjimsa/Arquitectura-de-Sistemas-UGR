################################################################################
# video2.s
################################################################################

.code16                # código de 16 bits

.text                  # sección de código
	.globl _start      # punto de entrada al código

_start:
	xorw %ax, %ax      # 0 --> ax   |
	movw %ax, %ds      # ax --> ds  | ds:si
	movw $msg, %si     # msg --> si |

	movw $0xb800, %ax  # 0xb800 --> ax |
	movw %ax, %es      # ax --> es     | es:di
	xorw %di, %di      # 0 --> di      |

	movb $0x01, %ah    # color azul

char:
	lodsb              # ds:[si++] --> al
	stosw              # ax --> es:[di++]
	incb %ah           # siguiente color
	andb $0x0f, %ah    # limita color
	orb %al, %al       # ¿es al == 0?
	jnz char           # si al != 0 imprimir el siguiente carácter

	movw $(2000-(fin-msg)), %cx  # repetir 2000-msg veces    |
	movw $0x0f20, %ax            # escribe espacio en blanco | limpiar pantalla
	rep stosw                    # ax --> es:[di++]          |

	cli                  # deshabilitar las interrupciones
	hlt                  # detener el procesador

msg: .asciz "cognito, ergo sum"  # datos en la sección de código
fin:

	.org 510      # saltar 510 bytes
	.word 0xAA55  # marca del sector de arranque
