.code16            # código de 16 bits

.text              # sección de código
    .globl _start  # punto de entrada

_start:
    jmp .          # bucle infinito

    .org 510       # posición 510
    .word 0xAA55   # firma
