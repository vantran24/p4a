/*
 * wrapper.c
 *
 *  Created on: Nov 12, 2013
 *      Author: Van
 */
#include "wrapper.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int Pthread_create (pthread_t * thread, const pthread_attr_t * attr,
		void *(*start_routine)(void *), void * arg){
	int rc;
	if (pthread_create(thread, start_routine, arg) != 0)
		perror("pthread_create");
	return rc;
}
int Pthread_join (pthread_t thread, void **value_ptr){
	int rc;
	if (pthread_join(thread, value_ptr) != 0)
			perror("pthread_join");
	return rc;
}
int Pthread_mutex_init  (pthread_mutex_t *lock,
		const pthread_mutexattr_t *attr){
	int rc;
	if ((rc = pthread_mutex_init(lock, attr)) != 0)
		perror("pthread_mutex_init");
	return rc;
}
int Pthread_mutex_lock (pthread_mutex_t *lock){
	int rc;
	if ((rc = pthread_mutex_lock(lock)) != 0)
		perror("pthread_mutex_lock");
	return rc;
}
int Pthread_mutex_unlock (pthread_mutex_t *lock){
	int rc;
	if ((rc = pthread_mutex_unlock(lock)) != 0)
		perror("pthread_mutex_unlock");
	return rc;
}
int Pthread_cond_init (pthread_cond_t *cond,
		const pthread_condattr_t *attr){
	int rc;
	if ((rc = pthread_cond_init(cond, attr)) != 0)
		perror("pthread_cond_init");
	return rc;
}
int Pthread_cond_wait (pthread_cond_t *cond,
		pthread_mutex_t *lock){
	int rc;
	if ((rc = pthread_cond_wait(cond, lock)) != 0)
		perror("pthread_cond_wait");
	return rc;
}
int Pthread_cond_signal (pthread_cond_t *cond){
	int rc;
	if ((rc = pthread_cond_signal(cond)) != 0)
		perror("pthread_cond_signal");
	return rc;
}
void *Malloc(size_t size){
	void *rc;
	if ((rc = malloc(size)) == NULL){
		perror("malloc");
	}
	return rc;
}








