//--------------------------------------------------------------------
// alarma.c
//--------------------------------------------------------------------

#include <unistd.h>  // alarm
#include <signal.h>  // signal SIGALRM
#include <stdio.h>   // printf

//--------------------------------------------------------------------

int FRECUENCIA_ALARMA = 1; // segundos
void atrapar_alarma(int);  // declaración anticipada

//--------------------------------------------------------------------

void instalar_alarma() // instalador del manejador de señal y alarma
{
	signal(SIGALRM, atrapar_alarma); // establecer manejador de la señal
	alarm(FRECUENCIA_ALARMA);        // establecer alarma
}

//--------------------------------------------------------------------

void atrapar_alarma(int i) // manejador de señal
{
	instalar_alarma(); // reinstalar tras cada alarma
	printf("¡¡¡ALARMA!!!\n");
}

//--------------------------------------------------------------------

int main()
{
	instalar_alarma(); // instalar alarma por primera vez
	for(;;);           // bucle infinito
}

//--------------------------------------------------------------------
