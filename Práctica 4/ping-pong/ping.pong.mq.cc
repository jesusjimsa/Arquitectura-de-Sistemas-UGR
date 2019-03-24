//---------------------------------------------------------
// ping.pong.mq.cc
//---------------------------------------------------------

#include <iostream>
#include <mqueue.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */

#define QUEUE_NAME  "/ping_pong_queue"
#define MAX_SIZE    1024

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

//---------------------------------------------------------

int main(){
	mqd_t mq;
	struct mq_attr attr;
	char c;

	switch(fork()){
		case -1:
			cerr << "Fallo en fork()" << endl;
			break;
		case 0:	// Hijo
			signal(SIGALRM, show_pong);
			alarm(1);

			/* initialize the queue attributes */
			attr.mq_flags = 0;
			attr.mq_maxmsg = 10;
			attr.mq_msgsize = sizeof(char);
			attr.mq_curmsgs = 0;

			/* create the message queue */
    		mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR | O_NONBLOCK, 0644, &attr);

			while(true){
				mq_send(mq, &PONG, sizeof(char), 0);

				do{
					mq_receive(mq, &c, sizeof(char), NULL);
				}while(c == PONG);

				pong++;
			}

			break;
		default:	// Padre
			signal(SIGALRM, show_ping);
			alarm(1);

			/* initialize the queue attributes */
			attr.mq_flags = 0;
			attr.mq_maxmsg = 10;
			attr.mq_msgsize = sizeof(char);
			attr.mq_curmsgs = 0;

			/* create the message queue */
    		mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR | O_NONBLOCK, 0644, &attr);

			while(true){
				mq_send(mq, &PING, sizeof(char), 0);

				do{
					mq_receive(mq, &c, sizeof(char), NULL);
				}while(c == PING);

				ping++;
			}

			break;
	}

	/* cleanup */
    mq_close(mq);
    mq_unlink(QUEUE_NAME);
}

//---------------------------------------------------------

