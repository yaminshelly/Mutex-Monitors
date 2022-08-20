#ifndef MONITOR_H
#define MONITOR_H

#include <pthread.h>

typedef struct {
	// define the parts of the monitor here
	int stock ; 
	pthread_mutex_t Mutex ; 
	pthread_cond_t condition_variable ; 
} monitor_t;

monitor_t *theMonitor;
#define VENDING_MAX 200
#endif
