#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "wrapper.h"
#include <pthread.h>
#include <unistd.h>
int loops;					//number of producers
int volatile *buffer;		//buffer for requests
int fillptr = 0; 			//is where to put the item in the queue
int numfull = 0; 			//keeps track of the num items so see if we reach capacity
int max;					//max number of requests that can be put into queue (command line)
int useptr = 0;				//putting the ptr back in the right spot after a get call
pthread_cond_t *empty;		//if the queue is empty (CV)
pthread_cond_t *fill;		//CV to fill queue
pthread_mutex_t *m;			//lock
int consumers; 				//# of consumers (spec. by the command line)
#define CMAX 1000 			//max consumers (worker threads) ***not sure
int cid [CMAX];				//consumer IDs

/*queue get/put*/
void do_fill(int value){
	buffer[fillptr] = value;
	fillptr = (fillptr + 1) % max;
	numfull++;
}

int do_get(){
	int tmp = buffer[useptr];
	useptr = (useptr + 1) % max;
	numfull--;
	return tmp;
}
/*queue get/put*/

/*working producer/consumer code*/
//master
void *producer(void *arg){
	for (int i = 0; i < loops; i++){	//loops is the num of requests
										//i is the request
										//loops through the shared queue (buffer)
		Pthread_mutex_lock(m);
		while(numfull == max){				//start of CS
			Pthread_cond_wait(empty, m);//goes to sleep and releases lock
		}
		do_fill(i);	//pushing to buffer
		Pthread_cond_signal(fill);			//end of CS
		Pthread_mutex_unlock(m);
	}
	return NULL;
}
//worker threads
void *consumer(void *arg){
	while(1){
		Pthread_mutex_lock(m);
		while(numfull == 0){				//start of CS
			Pthread_cond_wait(fill, m);//goes to sleep and releases lock
		}
		int tmp = do_get();//pulling from buffer
		Pthread_cond_signal(empty);			//end of CS
		Pthread_mutex_unlock(m);
		printf("%d\n", tmp);
	}
	return NULL;
}
/*working producer/consumer code*/

/*main routine
 * argv[1] = port number
 * argv[2] = # of threads
 * argv[3] = # of elements in buffer
 * argv[4] = scheduling algorithm
 */

int main(int argc, char *argv[]){
	max = atoi(argv[1]);
	loops = atoi(argv[2]);//not sure if i need this
	consumers = atoi(argv[3]);
	buffer = (int*) Malloc(max * sizeof(int));
	/*initialization*/
	Pthread_mutex_init(m, NULL);
	Pthread_cond_init(empty, NULL);
	Pthread_cond_init(fill, NULL);
	/*initialization*/
	pthread_t pid;
	pthread_t cid[CMAX];//array of threads
	Pthread_create(&pid, NULL, producer, NULL);
	int i;
	for(i = 0; i < consumers; i++){//filling the array with threads
		Pthread_create(&cid[i], NULL, consumer, NULL);
	}
	Pthread_join(pid, NULL);//waiting for all the threads in the array to finish
	for(i = 0; i < consumers; i++){
		Pthread_join(cid[i], NULL);
	}
}
/*main routine*/
