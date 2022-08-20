#include <stdio.h>
#include <stdlib.h>
 #include <pthread.h>
#include <errno.h>
#include <ctype.h>
#include "monitor.h"
#include "supplier.h"
#include "consumer.h"
#include <time.h> 


pthread_mutex_t Mutex ; 
pthread_cond_t condition_variable ; 

//the name of the files 
char *suppliers[3]= {"Supplier1-Configuration.txt" , "Supplier2-Configuration.txt", "Supplier3-Configuration.txt"};
char* consumers[3] = {"Consumer1-Configuration.txt" , "Consumer2-Configuration.txt" , "Consumer3-Configuration.txt"};

int stock =0 ;  //initial the machine with 0 unit.

//We didnt use this struct at the end 
struct thread_info {
	pthread_t thread_id;
	int thread_num;
	char *argv_string;
};

// initialize the monitor with the standard parametenrs
int monitor_init (monitor_t *monitor)
{
  monitor->Mutex=Mutex;
  monitor->condition_variable = condition_variable ;
  monitor->stock = stock ; 
  return 0;
}

int main( int argv, char* args[])
{	// initiate the monitor with malloc
	// create one thread for each of the six elements - 3 suppliers, 3 consumers
	// run them
	
	pthread_t supplierthreads[3]; //3 thread for supplier 
	pthread_t consumerthreads[3]; //3 thread for consumer 
	int suppliernum[3];//Id of theard 
	int consumersnum[3];//Id of theard
	pthread_mutex_init(&Mutex , NULL ); //mutex initial
	pthread_cond_init(&condition_variable , NULL); //condition verible initial 

//creat 3 thraed of supplier 
	for(int i=0 ; i < 3 ; i++)
	{
			suppliernum[i]= pthread_create(&supplierthreads[i] , NULL , &runSupplier ,suppliers[i] );
	}
//creat 3 thraed of consumer 
	for(int i=0 ; i < 3 ; i++)
	{
			consumersnum[i]= pthread_create(&consumerthreads[i] , NULL , &runConsumer ,consumers[i] );	
	}
	
//join suppliers
	for(int i=0 ; i < 3 ; i++)
	{
		pthread_join(supplierthreads[i] , NULL);
		
	}
//join consumers	
	for(int i=0 ; i < 3 ; i++)
	{
		pthread_join(consumerthreads[i],NULL);
		
	}
	
		printf(" All threads completed. Final stock = 0 ");


	pthread_mutex_destroy(&Mutex); 
	pthread_cond_destroy(&condition_variable); 
	
	exit(0);
	return 0; 
}
