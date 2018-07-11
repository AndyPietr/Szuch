#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<unistd.h>
#include "mylib.h"

#define SEC_IN_HOUR 3600
#define SEC_IN_MIN 60

//funkcja zwracajaca ilość sekund do okreslonych danych czasowych, jeśli zwróci wartość ujemną to zdarzenie już było
long int calculate_sec_to(int target_h, int target_m, int target_s)
{   
	//tworzy obiekt z aktualnym czasem
	struct tm *at; //actual time
	time_t t=time(NULL);
	at = localtime(&t);
	//oblicza ilosc sekund od poczatku doby do czasu target h:m:s
	long int target_seconds= (long int)target_h*3600 + (long int)target_m*60 + (long int)target_s;
	long int actual_seconds= (long int)at->tm_hour*3600 + (long int)at->tm_min*60 + (long int)at->tm_sec;
	
	//zwraca ich różnicę
	long int diff_in_sec= target_seconds-actual_seconds;
//	printf("\ntarget_seconds: %li  actual_seconds: %li  diff_in_sec: %li\n", target_seconds, actual_seconds, diff_in_sec);

return diff_in_sec;
} 

