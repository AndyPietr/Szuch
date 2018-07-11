#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<unistd.h>
#include "mylib.h"

#define SEC_IN_HOUR 3600
#define SEC_IN_MIN 60

void * threadFunction (void* arg){
	
	MyData* pmydata = (MyData*) arg;

typedef enum
{
	N,
	O,
	T
} OrderKind;

OrderKind orderKind; 


	if ((pmydata->kind_of_order) == 'N'){
		orderKind=N;
	}
	else if((pmydata->kind_of_order) == 'O'){
		orderKind=O;
	}
	else if((pmydata->kind_of_order) == 'T'){
		orderKind=T;
	}
	// dopiero tu jest cos waznego
	switch(orderKind)
	{
	case N: 
		N_task(pmydata); 
		break;

	case O: 
		O_task(pmydata);
		break;

	case T: 
		T_task(pmydata);
		break;

	defualt: 
		puts("function threadFunction problem with switch: orderKind doesn't match any kind");
	
	}
}
