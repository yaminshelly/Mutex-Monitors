#include "monitor.h"
#include "consumer.h"
#include "supplier.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h> 


struct consume_info{
	char *Name; 
	int Consumption_Interval; 
	int Repetitions; 
	int Consume_Size; 
}; 

struct consume_info consumer ; 

extern int stock;
extern pthread_mutex_t Mutex; 
extern pthread_cond_t condition_variable ; 
void* runConsumer (void* param)
{
	//time 
	struct tm *ptr;
	
	time_t t;
	char str[100]; 
	
	//day 
	struct tm *local; 
	char *name_of_file= (char*)param; 
	
	//costumer varible :
	char Name[20] ; 
	int Consumption_Interval=0 ; 
	int Repetitions=0 ; 
	int Consume_Size=0 ; 
	
	//time
	t=time(NULL);
	local  = localtime(&t);  // day now 
	ptr = localtime(&t); // time now
	
	
	
	 FILE *fp ; 
	// open the configuration file
	fp = fopen (name_of_file , "r"); // read and write file 
	
	// read the configuration material from the file
	
	
		fscanf(fp , "%s %d %d %d", Name , &Consumption_Interval , &Repetitions , &Consume_Size);
		//printf(" name = %s \ninterval = %d \nrepitation = %d \nsize = %d\n", Name, Consumption_Interval, Repetitions, Consume_Size);
	
	int count =0;
	
	//pthread_mutex_lock(&Mutex); // critical section 
	
	for(int i =0 ; i< Repetitions ; i++)
	{
		// critical section 
		pthread_mutex_lock(&Mutex);
		if(stock-Consume_Size < 0) //There are no bottle in the machine 
		{ 
			while(stock-Consume_Size < 0 )
			{
				//time before the massage 
				printf("%s  %s  %d  " , change_num_to_day (local->tm_wday) , change_num_to_mounth(local->tm_mon) ,  local->tm_mday); 
				strftime(str , 100 , "%X   " , ptr );
				printf("%s",  str);
				printf("%d " ,  local -> tm_year +1900);
				printf("%s going to wait\n\n" , Name  );
				
				pthread_cond_wait(&condition_variable ,&Mutex);  // wait for signal . 
				count =0 ; 
			}
			
		}
		// consume when we should, sleep when we need to consume but can't
		//have botles in the machine 
			stock = stock - Consume_Size;
			count++;
			
			//time
			printf("%s  %s  %d  " , change_num_to_day (local->tm_wday) , change_num_to_mounth(local->tm_mon) ,  local->tm_mday); 
			strftime(str , 100 , "%X   " , ptr );
			printf("%s",  str);
			printf("%d " ,  local -> tm_year +1900);
			printf("%s removed %d units. Stock after = %d\n" , Name , count*Consume_Size , stock );
			count =0 ; 
			
			// end of critical section 
			pthread_mutex_unlock(&Mutex);
			pthread_cond_signal(&condition_variable); 
			sleep(Consumption_Interval); 
	
	}
	
	fclose(fp) ; 
	
	
	return 0 ; 
}
