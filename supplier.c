#include "monitor.h"
#include "supplier.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h> 

//%X standart time now 
//%I hour 
//%p -- am or pm 
// %M minutes 
//%S second 
// %Z time zone name 


typedef struct supplier_info{
	char *Name; 
	int Supply_interval;
	int Repetitions; 
	int Supply_Size; 
} SUPPLIER;

SUPPLIER supplier ; 

//change number to the word of the day
char *change_num_to_day(int x)
{
	switch (x)
	{
		case 0 : return "SUN"; break ; 
		case 1 : return "MON" ; break; 
		case 2 : return "TUR" ; break ; 
		case 3 : return "WED" ; break ; 
		case 4 : return "THUR" ; break ; 
		case 5: return "FRI" ; break ; 
		case 6 : return "SAT" ; break ; 
		default : return "nothing" ;
	}
}

//change number to the word of the mounth 
char *change_num_to_mounth(int x)
{
	switch(x)
	{
		case 0 : return "JAN"; break ; 
		case 1 : return "FEB" ; break; 
		case 2 : return "MERCH" ; break ; 
		case 3 : return "APRIL" ; break ; 
		case 4 : return "MAY" ; break ; 
		case 5: return "JUNE" ; break ; 
		case 6 : return "JUNY" ; break ; 
		case 7 : return "JULY" ; break ; 
		case 8 : return "AUGUST" ; break ; 
		case 9 : return "SEP" ; break ; 
		case 10 : return "OCT" ; break ; 
		case 11: return "NOV" ; break ;
		case 12: return "DEC" ; break ;  
		default : return "nothing " ;
	}
}



extern int stock;
extern pthread_mutex_t Mutex ; 
extern pthread_cond_t condition_variable ; 
void *runSupplier (void* param)
{
	//time 
	FILE *fp; 
	struct tm *ptr;
	time_t t;
	char str[100]; 
	
	//day 
	struct tm *local; 
	
	//name of file 
	char *name_of_file= (char*)param; 
	
	//supplier varible : 
	char Name[20];
	int Supply_interval = 0 ; 
	int Repetitions= 0 ; 
	int Supply_Size = 0; 
	
	//time varible
	t=time(NULL);
	local  = localtime(&t);  // day now 
	ptr = localtime(&t); // time now
	
	
	
	
	// open the configuration file
	fp = fopen (name_of_file, "r"); // read only 
	// read the configuration material from the file
	fscanf(fp , "%s %d %d %d", Name , &Supply_interval , &Repetitions , &Supply_Size);  
	
	
	int count =0; 
	
	for(int i =0 ; i< Repetitions ; i++)
	
	{
		pthread_mutex_lock(&Mutex); // critical section 
		if(Supply_Size + stock  > VENDING_MAX ) //There are no place in the machine 
		{ 
			while(Supply_Size + stock > VENDING_MAX)
			{	
					//time
					printf("%s  %s  %d " , change_num_to_day (local->tm_wday) , change_num_to_mounth(local->tm_mon) ,  local->tm_mday ); 
					strftime(str , 100 , "%X  " , ptr );
					printf("%s",  str);
					printf("%d " ,  local -> tm_year +1900);
					printf(" %s going to wait\n\n" , Name  );
					
					// wait for signal .
					pthread_cond_wait(&condition_variable ,&Mutex);  
					count=0 ; 
			}
		}
		// supply when we should, sleep when we need to supply but can't
		else//<200 
		{
				stock = stock + Supply_Size;
				count++;    
				printf("%s  %s  %d " , change_num_to_day (local->tm_wday) , change_num_to_mounth(local->tm_mon) ,  local->tm_mday ); 
				strftime(str , 100 , "%X  " , ptr );
				printf("%s",  str);
				printf("%d " ,  local -> tm_year +1900);
	
				printf("%s supply %d units. Stock after = %d\n\n" , Name , count*Supply_Size , stock );
				count=0 ; 
				
				// end of critical section   
				pthread_mutex_unlock(&Mutex);
				pthread_cond_signal(&condition_variable); 
				sleep(Supply_interval);  
		}
			
	}
	
	
	fclose(fp) ; 
	return 0; 
}


