/*
 * wrapper.h
 *
 *  Created on: Nov 12, 2013
 *      Author: Van
 */

#ifndef WRAPPER_H_
#define WRAPPER_H_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *Pthread_create (pthread_t * thread, const pthread_attr_t * attr,
		void *(*start_routine)(void *), void * arg);
void *Pthread_mutex_init  (pthread_mutex_t *lock,
		const pthread_mutexattr_t *attr);
void *Pthread_mutex_lock (pthread_mutex_t *lock);
void *Pthread_mutex_unlock (pthread_mutex_t *lock);
void *Pthread_cond_init (pthread_cond_t *cond,
		const pthread_condattr_t *attr);
void *Pthread_cond_wait (pthread_cond_t *cond,
		pthread_mutex_t *lock);
void *Pthread_cond_signal (pthread_cond_t *cond);
void *Pthread_join (pthread_t thread, void **value_ptr);
void *Malloc(size_t size);

#endif /* WRAPPER_H_ */
