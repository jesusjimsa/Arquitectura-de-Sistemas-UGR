//---------------------------------------------------------
// ping.pong.socket.cc
//---------------------------------------------------------

#include <iostream>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* el puerto usado */
#define PORT 2024

using namespace std;

//---------------------------------------------------------

int main(){
	int ping = 0, pong = 0;

	switch (fork()){
		case -1:
			cerr << "Error en fork()" << endl;
			exit(-1);

			break;
		case 0:	// Hijo

			break;
		default:
			struct sockaddr_in server; // la estructura utilizada por el servidor
			struct sockaddr_in from;
			int sd; //descriptor de socket
			socklen_t length = sizeof(from);
			/* creando un socket */
			if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
				perror("[server]Error in socket().\n");
				return errno;
			}

			/* preparación de estructuras de datos */
			bzero(&server, sizeof(server));
			bzero(&from, sizeof(from));

			/* llene la estructura utilizada por el servidor */
			/* estableciendo la familia de sockets */
			server.sin_family = AF_INET;

			/* aceptamos cualquier dirección */
			server.sin_addr.s_addr = htonl(INADDR_ANY);

			/* usamos un puerto de usuario */
			server.sin_port = htons(PORT);

			/* adjuntamos el socket */
			if (bind(sd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1){
				perror("[server]Error in bind().\n");
				return errno;
			}

			/* le pedimos al servidor que escuche si los clientes vienen a conectarse */
			if (listen(sd, 5) == -1){
				perror("[server]Error in listen().\n");
				return errno;
			}
			
			
			close(sd);
			
			break;
	}

	cout << "ping = " << ping << endl
		 << "pong = " << pong << endl;
	
	
}

//---------------------------------------------------------
