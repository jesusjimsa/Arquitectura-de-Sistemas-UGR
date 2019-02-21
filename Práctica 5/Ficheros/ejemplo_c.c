#include <pthread.h>
#include <stdio.h>

void* hebra(void* p)
{
	printf("[2] hola: %lu\n", pthread_self());
	pthread_exit(NULL);  // return NULL;
}

int main()
{
	pthread_t id;
	
	printf("[1] hola: %lu\n", pthread_self());
	pthread_create(&id, NULL, hebra, NULL);
	pthread_join(id, NULL);
	
	return 0;  // exit(0); // estilo pre C99
}

