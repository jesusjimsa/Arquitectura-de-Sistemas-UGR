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

const char PING = '1', PONG = '0';
int ping = 0, pong = 0;

//---------------------------------------------------------

void show_ping(int){
	cout << "ping = " << ping << endl;

	exit(EXIT_SUCCESS);
}

//---------------------------------------------------------

void show_pong(int){
	cout << "pong = " << pong << endl;

	exit(EXIT_SUCCESS);
}

//---------------------------------------------------------

int main(){
	int sd;			// descriptor de socket
	struct sockaddr_in server;	// la estructura utilizada para conectar
	struct sockaddr_in from;
	int client_id;
	socklen_t length = sizeof(from);
	char c;

	switch (fork()){
		case -1:
			cerr << "Error en fork()" << endl;
			exit(-1);

			break;
		case 0:	// Hijo
			if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
				cerr << "Error in socket()." << endl;
				return errno;
			}

			/* llenamos la estructura utilizada para conectar al servidor */
			/* la familia de socket */
			server.sin_family = AF_INET;
			
			/* dirección IP del servidor */
			server.sin_addr.s_addr = inet_addr("127.0.0.1");
			
			/* el puerto de conexión */
			server.sin_port = htons(PORT);

			if(connect(sd, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1){
				cerr << "[client]Error in connect()." << endl;
				return errno;
			}

			while(true){
				send(sd, &PING, sizeof(char), 0);

				do{
					recv(sd, &c, sizeof(char), 0);
				}while(c == PING);

				ping++;
			}

			close(sd);

			break;
		default:	// Padre
			/* creando un socket */
			if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
				cerr << "[server]Error in socket()." << endl;
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
				cerr << "[server]Error in bind()." << endl;
				return errno;
			}

			/* le pedimos al servidor que escuche si los clientes vienen a conectarse */
			if (listen(sd, 5) == -1){
				cerr << "[server]Error in listen()." << endl;
				return errno;
			}

			client_id = accept(sd, (struct sockaddr *) &from, &length);

			while(true){
				send(client_id, &PONG, sizeof(char), 0);

				do{
					recv(client_id, &c, sizeof(char), 0);
				}while(c == PONG);

				pong++;
			}
			
			close(client_id);
			close(sd);
			
			break;
	}
}

//---------------------------------------------------------
