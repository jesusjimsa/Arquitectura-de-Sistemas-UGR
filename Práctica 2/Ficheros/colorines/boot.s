################################################################################
# long mode initialization from amd manual
################################################################################

.code16					# código de 16 bits, modo real

.text					# sección de código
.globl _start			# punto de entrada

_start:

	movw $0xb800, %ax	# 0xb800 --> ax |
	movw %ax, %es		# ax --> es     | memoria de video --> es:di
	xorw %di, %di		# 0 --> di      |

	movw $1999, %cx		# número de almacenamientos, 2000 --> cx

	xor %ax, %ax		# 0 --> ax
p:	stosb				# al --> es:di++ ... color
	stosb				# al --> es:di++ ... caracter
	inc %ax
	loop p

	cli			# deshabilitar interrupciones
	hlt			# párate

################################################################################
# firma del sector de arranque
################################################################################

sign: .org 510      # posición de memoria 510
      .word 0xAA55  # marca del sector de arranque

