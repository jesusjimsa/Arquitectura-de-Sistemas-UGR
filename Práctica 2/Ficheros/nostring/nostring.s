###############################################################################
# nostring.s
###############################################################################

.code16                # código de 16 bits

.text                  # sección de código
	.globl _start      # punto de entrada al código

_start:
	xor %ax, %ax       # 0 --> ax   |
	mov %ax, %ds       # ax --> ds  | msg --> ds:si
	mov $msg, %si      # msg --> si |

	mov $0xb800, %ax   # 0xb800 --> ax |
	mov %ax, %es       # ax --> es     | video --> es:di
	xor %di, %di       # 0 --> di      |

	mov $0x0c, %ah     # color rojo
	mov len, %cx       # nº de caracteres

sig:
	mov %ds:(%si), %al # ds(si) --> al
	inc %si
	mov %ax, %es:(%di) # ax --> es(di)
	add $2, %di
	loop sig           # decrementa cx y salta si no 0

	cli
	hlt

msg: .ascii "cognito, ergo sum!"
len: .int . - msg

	.org 510           # saltar 510 bytes
	.word 0xAA55       # firma del sector de arranque
