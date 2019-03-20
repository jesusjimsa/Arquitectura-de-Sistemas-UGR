/*
	Programa creado con la ayuda del tutorial de
	https://users.cs.cf.ac.uk/Dave.Marshall/C/node25.html
*/

#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cassert>
#include <string>
#include <iostream>

#define MSGSZ     128

/*
 * Declare the message structure.
 */

typedef struct msgbuf{
	long mtype;
	char mtext[MSGSZ];
} message_buf;

using namespace std;

int main(){
	key_t key; /* key to be passed to msgget() */
	int msgflg; /* msgflg to be passed to msgget() */
	int msqid; /* return value from msgget() */
	message_buf sbuf, rbuf;
	size_t buf_length;

	key = 1234;
	msgflg = IPC_CREAT | 0666;

	if ((msqid = msgget(key, msgflg)) == 1){
		cerr << "msgget: msgget failed" << endl;
		exit(1);
	}
	else{
		cout << "msgget succeeded" << endl;
	}

	switch(fork()){
		case -1:
			cout << "Fallo en fork()" << endl;
			break;
		case 0:		// Hijo
			sbuf.mtype = 1;

			strcpy(sbuf.mtext, "Did you get this?");
			
			buf_length = strlen(sbuf.mtext) + 1 ;

			/*
			* Send a message.
			*/
			if(msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0){
				cout << msqid << sbuf.mtype << sbuf.mtext << buf_length << endl;
				cerr << "msgsnd" << endl;
				exit(1);
			}
			else{
				cout << "Message sent: \"" << sbuf.mtext << "\"" << endl;
			}

			break;
		default:	// Padre
			wait(nullptr);

			/*
			* Receive an answer of message type 1.
			*/
			if (msgrcv(msqid, &rbuf, MSGSZ, 1, 0) < 0){
				cerr << "msgrcv" << endl;
				exit(1);
			}

			cout << "Message received: \"" << rbuf.mtext << "\"" << endl;

			break;
	}
}