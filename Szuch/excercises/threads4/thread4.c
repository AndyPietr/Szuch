#include <stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define NUM_LOOPS 100 
long long sum = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void* counting_thread(void* arg){
	int offset = *(int*) arg;
	
	for(int i =0; i<NUM_LOOPS; i++){
		//start critical setcion
		//pthread_mutex_lock(&mutex);
		
		sum += offset;

		//end critical secion
		//pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}


int main(void){

	int l1 =1;
	
	pthread_t tid1;
	pthread_create(&tid1, NULL, counting_thread, &l1);

	int l2 =-1;
	pthread_t tid2;
	pthread_create(&tid2, NULL, counting_thread, &l2);


	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	printf("\n answer is %lld\n", sum);
	return EXIT_SUCCESS;
}
