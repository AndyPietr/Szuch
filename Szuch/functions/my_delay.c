#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<unistd.h>
#include "mylib.h"

#define SEC_IN_HOUR 3600
#define SEC_IN_MIN 60

int my_delay(long int sec_to_wait)
{
	if(sec_to_wait < 60000 ) //limit zmiennej int
	{ 
		sleep(sec_to_wait);
		return 0;		
	}
	else if(sec_to_wait >= 60000)
	{
		sleep(60000);
		sleep( sec_to_wait - 60000 );
	}

}
