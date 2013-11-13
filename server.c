#include "cs537.h"
#include "request.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "wrapper.h"
#include <pthread.h>
#include <unistd.h>
#define FIFO    (0)//first-in-first-out
#define SFNF    (1)//shortest=file-name-first
#define SFF     (2)//shortest-file-first

int volatile *buffer;		//buffer for requests
int fillptr = 0; 			//is where to put the item in the queue
int numfull = 0; 			//keeps track of the num items so see if we reach capacity
int threadnum;				//num of threads
int buf_ele; 				//numb of buffer elements	(max)
int schaglo;				//scheduling algo
int useptr = 0;				//putting the ptr back in the right spot after a get call
pthread_cond_t *empty;		//if the queue is empty (CV)
pthread_cond_t *fill;		//CV to fill queue
pthread_mutex_t *m;			//lock
// 
// server.c: A very, very simple web server
//
// To run:
//  server <portnum (above 2000)>
//
// Repeatedly handles HTTP requests sent to this port number.
// Most of the work is done within routines written in request.c
//

// CS537: Parse the new arguments too
void getargs(int *port, int threadnum, int buf_ele, int schaglo, int argc,
		char *argv[])
{
    if (argc != 5) {
	fprintf(stderr, "Usage: %s Invalid Number of Args\n", argv[0]);
	exit(1);
    }
    *port = atoi(argv[1]);//port number
    /* argv[1] = port number
     * argv[2] = # of threads
     * argv[3] = # of elements in buffer
     * argv[4] = scheduling algorithm
     */
    threadnum = atoi(argv[2]);
    buf_ele = atoi(argv[3]);
    //error checking here
    schaglo = atoi(argv[4]);

    //haven't gotten the other arguments yet
}

int main(int argc, char *argv[])
{
	//probably what the producer (master) will be doing
    int listenfd, connfd, port, clientlen;
    struct sockaddr_in clientaddr;

    getargs(&port, threadnum, buf_ele, schaglo, argc, argv);
    buffer = (int*) Malloc(buf_ele * sizeof(int));
    /*initialization*/
    Pthread_mutex_init(m, NULL);
    Pthread_cond_init(empty, NULL);
    Pthread_cond_init(fill, NULL);
    // 
    // CS537: Create some threads...
    //
    // create the pool of worker thread here **** i'm assuming
    pthread_t master;
    pthread_t workers[threadnum];//array of worker threads
    //socket programming, don't have to do much with this but multi it***
    listenfd = Open_listenfd(port);
    while (1) {
	clientlen = sizeof(clientaddr);
	connfd = Accept(listenfd, (SA *)&clientaddr, (socklen_t *) &clientlen);
	//put this fd into the shared queue
	//then take more requests

	// 
	// CS537: In general, don't handle the request in the main thread.
	// Save the relevant info in a buffer and have one of the worker threads 
	// do the work. However, for SFF, you may have to do a little work
	// here (e.g., a stat() on the filename) ...
	// 

	requestHandle(connfd);//read and write
	//most of the work is done from here****
	/*this is called from request.c*******/

	Close(connfd);
    }
}


    


 
