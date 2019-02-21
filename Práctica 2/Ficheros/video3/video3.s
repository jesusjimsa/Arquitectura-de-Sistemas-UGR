###############################################################################
# video3.s
###############################################################################

.code16                # código de 16 bits

.text                  # sección de código
	.globl _start      # punto de entrada al código

_start:
	xorw %ax, %ax      # 0 --> ax   }
	movw %ax, %ds      # ax --> ds  } msg --> ds:si 
	movw $msg, %si     # msg --> si }

	movw $0xb800, %ax  # 0xb800 --> ax }
	movw %ax, %es      # ax --> es     } video --> es:	di
	xorw %di, %di      # 0 --> di      }

	movw $((fin-msg)/2), %cx  # longitud de la cadena --> cx

	rep movsw          # repite ds:[si++] --> es:[di++]

	movw $(2000-(fin-msg)/2), %cx  # repetir 2000 veces |
	movw $0x0f20, %ax              # escribe ' '        | limpiar pantalla
	rep stosw                      # ax --> es:[di++]   |

	cli         # deshabilitar las interrupciones
	hlt         # detener el procesador

msg: .byte 'c', 0x0f, 'o', 0x0f, 'g', 0x0f, 'n', 0x0f, 'i', 0x0f, 't', 0x0f, 'o', 0x0f, ',', 0x0f, ' ', 0x0f, 'e', 0x0f, 'r', 0x0f, 'g', 0x0f, 'o', 0x0f, ' ', 0x0f, 's', 0x0f, 'u', 0x0f, 'm', 0x0f, ' ', 0x0f
fin:

	.org 510      # saltar 510 bytes
	.word 0xAA55  # marca del sector de arranque

###############################################################################
