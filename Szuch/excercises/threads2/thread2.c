//running multiple threads

#include <stdio.h>
#include<stdlib.h>
#include<pthread.h>

struct sum_runner_struct{
	long long limit;
	long long answer;
};


//thread function to generate sum of 0 to N
void *sum_runner(void* arg){
	struct sum_runner_struct *arg_struct = (struct sum_runner_struct*) arg; 
	long long i;
	long long sum = 0;

	for(i=0; i <= arg_struct->limit ; i++){
		sum +=i;
	}
	arg_struct->answer= sum;
	pthread_exit(0);
}

int main(int argc, char **argv){
	
	puts("");
	if(argc<2) {
		printf("usage %s <num> \n", argv[0]);
		exit(-1);
	}

	int num_args = argc - 1;
	struct sum_runner_struct args[num_args];

	//launch threads:
	pthread_t tid[num_args];
	int i;
	for(i=0 ; i < num_args ; i++){
		args[i].limit = atoll(argv[1+i]);
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tid[i], &attr, sum_runner, &args[i]);
	}
	//wait for ALL off the  threads 'tids' to done their work 
	for(i=0; i<num_args ; i++){
		pthread_join(tid[i], NULL);
		printf("sum %d is %lld \n", i, args[i].answer); 
	}
	
	
}
