//---------------------------------------------------------
// ping.pong.socket.cc
//---------------------------------------------------------

#include <iostream>
#include <socket.h>
#include <sys/types.h>

/* el puerto usado */
#define PORT 2024

using namespace std;

//---------------------------------------------------------

int main(){
	struct sockaddr_in server;	// La estructura utilizada por el servidor
	struct sockaddr_in from;
	int sockd;	// Socket descriptor
	socklen_t length = sizeof(from);
	int client_id;
	int ping = 0, pong = 0;

	switch(fork()){
		case -1:
			cerr << "Error en fork()" << endl;
			break;
		case 0:
			
		default:
			if((sockd = socket (AF_INET, SOCK_STREAM, 0)) == -1){
				perror("[server]Error in socket().\n");
				return errno;
			}

			/* Preparación de estructuras de datos */
			bzero(&server, sizeof(server));
			bzero(&from, sizeof(from));

			/* Llene la estructura utilizada por el servidor */
			/* estableciendo la familia de sockets */
			server.sin_family = AF_INET;

			/* Aceptamos cualquier dirección */
			server.sin_addr.s_addr = htonl(INADDR_ANY);

			/* Usamos un puerto de usuario */
			server.sin_port = htons(PORT);

			/* Adjuntamos el socket */
			if(bind(sockd, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1){
				perror("[server]Error in bind().\n");
				return errno;
			}

			/* Le pedimos al servidor que escuche si los clientes vienen a conectarse */
			if(listen(sockd, 5) == -1){
				perror ("[server]Error in listen().\n");
				return errno;
			}

			client_id = accept(sockd, (struct sockaddr *) &from, &length);

			if(client_id < 0){
				cerr << "[server]Error in accept()." << endl;
			}

			/////////////////////////////////////////////////// Aquí

			break;
	}

	cout << "ping = " << ping << endl
		 << "pong = " << pong << endl;

	close(sockd);
}

//---------------------------------------------------------

