.code16				# código de 16 bits

.text				# sección de código
	.globl _start	# punto de entrada

_start:
	xor %ax, %ax		# 0 --> ax   |
	mov %ax, %ds		# ax --> ds  | msg --> ds:si
	mov $msg, %si		# msg --> si |
	
	movw $0xb800, %ax  # 0xb800 --> ax |
	movw %ax, %es      # ax --> es     | video --> es:di
	xorw %di, %di      # 0 --> di      |


	mov tam, %cx
sig:
	mov $0xe, %ah
	mov %ds:(%si), %al	# Caracter que se desea imprimir
	xor %bh, %bh
	movb $0x04, %bl		# Aquí debería cambiar el color de la letra, pero la BIOS no funciona bien
	int $0x10			# Interrupción para imprimir por pantalla
	inc %si
	loop sig			# decrementa cx y salta si no 0

fin:	
	cli
	hlt

msg: .string "Hola mundo"
tam: .short . - msg

	.org 510		# posición 510
	.word 0xAA55	# firma
