#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<unistd.h>
#include "mylib.h"

#define SEC_IN_HOUR 3600
#define SEC_IN_MIN 60


void* O_task(void* arg){
	
	MyData* pmydata = (MyData*) arg;

	//oblicza czas do wylaczenie tOFF w sekundach
	long int tOff=calculate_sec_to(pmydata->task_hour_OFF, pmydata->task_min_OFF, pmydata->task_sec_OFF);
	//sprawdza czy zdarzenia juz nie było
	if(tOff <0)
	{
		puts("function N_task tOff<0");
		return NULL;
	}

	//oblicza czas do pierwszego włączenia
	long int tOn=calculate_sec_to(pmydata->task_hour_ON, pmydata->task_min_ON, pmydata->task_sec_ON);
	//sprawdza czy zdarzenia juz nie było
	if(tOn <0)
	{
		puts("function N_task tOn<0");
		return NULL;
	}
	//sprawdza sensownosc rozkazu
	if(!(tOff > tOn))
	{
		puts("function N_task czas 'off' jest przed czasem 'on'");
		return NULL;
	}
	
	//czeka tON sekund
	my_delay(tOn);
	puts("rozpoczynam zadanie");
	
	//czeka do konca zadania
	my_delay(pmydata->task_lasting_in_sec);
	puts("koncze zadanie");

	//cykliczność zadania
	char canIgoON = 1;
	do
	{
		//ustala kolejny czas do wlaczenia
		tOn = ((long int)pmydata->task_period_in_min)*60 - pmydata->task_lasting_in_sec  ;  
		//oblicza czas do wyłączenia
		long int tOff=calculate_sec_to(pmydata->task_hour_OFF, pmydata->task_min_OFF, pmydata->task_sec_OFF);
	
		//porównuje te czasy
		if(tOn > tOff)
		{
			canIgoON=0;
		
		}
		else
		{
			canIgoON= 1;
			//czeka tON sekund
			my_delay(tOn);
			puts("rozpoczynam zadanie");
	
			//czeka do konca zadania
			my_delay(pmydata->task_lasting_in_sec);
			puts("koncze zadanie");
		}
	}while(canIgoON == 1);
	
}
