#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<unistd.h>
#include "mylib.h"

#define SEC_IN_HOUR 3600
#define SEC_IN_MIN 60

void * T_task(void* arg){
	
	MyData* pmydata = (MyData*) arg;

	//oblicza czas do włączenia
	long int tOn=calculate_sec_to(pmydata->task_hour_ON, pmydata->task_min_ON, pmydata->task_sec_ON);
	//sprawdza czy zdarzenia juz nie było
	if(tOn <0)
	{
		puts("function N_task tOn<0");
		return NULL;
	}

	//czeka tON sekund
	my_delay(tOn);
	puts("rozpoczynam zadanie");
	
	//czeka do konca zadania
	my_delay(pmydata->task_lasting_in_sec);
	puts("koncze zadanie");
	
}

