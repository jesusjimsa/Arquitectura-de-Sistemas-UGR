.code16            # código de 16 bits

.text              # sección de código
	.globl _start  # punto de entrada

_start:
	xor %ax, %ax       # 0 --> ax   |
	mov %ax, %ds       # ax --> ds  | msg --> ds:si
	mov $msg, %si      # msg --> si |

sig:
	mov $0xe, %ah
	mov %ds:(%si), %al
	xor %bh, %bh
	movb $0x04, %bl		# Aquí debería cambiar el color de la letra, pero la BIOS no funciona bien
	int $0x10
	loop sig           # decrementa cx y salta si no 0
	
	cli
	hlt

msg: .ascii "Hola mundo"
fin:
	.org 510       # posición 510
	.word 0xAA55   # firma
