#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<unistd.h>
#include "mylib.h"

#define SEC_IN_HOUR 3600
#define SEC_IN_MIN 60


int creatingThreads(void* arg, int num_of_structures){

	MyData* pmydata = (MyData*) arg;

	pthread_t tid[num_of_structures];
	//creating threads
	int i=0;
	for(i=0; i<num_of_structures; i++){

		pthread_create(&tid[i], NULL, threadFunction, (pmydata+i) );
	}
	
	for(i=0; i<num_of_structures ; i++){

		pthread_join(tid[i], NULL);

	}
	
}
