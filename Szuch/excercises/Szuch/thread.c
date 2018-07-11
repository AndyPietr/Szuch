//first szuch project

#include <stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<unistd.h>
#include<wiringPi.h>

#define SEC_IN_HOUR 3600
#define SEC_IN_MIN 60

struct dane{
	//task time
	int task_hour;
	int task_min;
	int task_sec;
	int section_number ;
};

long long calculate_second_to_task(struct dane * section){

	unsigned time_to_task = 0;
	// gets actual local time
	struct tm *local;
	time_t t = time(NULL);
	local = localtime(&t);
	
	//prints both time current and task time
	//printf("\n loccal time is %d %d %d ", local->tm_hour, local->tm_min, local->tm_sec);
	//printf("\n task  time  is %d %d %d ", section->task_hour, section->task_min,  section->task_sec);

	// calculate time to task in second
	// time_to_task = (task_time) - (current_time)
	time_to_task = ( section->task_hour - local->tm_hour) * SEC_IN_HOUR + 
				   ( section->task_min  - local->tm_min ) * SEC_IN_MIN  +  
                   ( section->task_sec  - local->tm_sec ) ;
	
	//printf("\ntime to task in sec: %lld", time_to_task);
	
	// TODO WHAT IF time is negative value ?? do some if construction adding 24h or whatever

	return time_to_task;   
}

void * section_thread(void* arg){
	puts("hello form thread");
	struct dane * section = (struct dane * ) arg;
	
	sleep( calculate_second_to_task(section) ); //TODO sleep takes unsigned arg it is too small
	puts("TASK");
	
	//starting rPi things
	wiringPiSetupGpio();// i use BCM pin names
	pinMode(21, OUTPUT);
	digitalWrite(21, HIGH);
	sleep(3);
	digitalWrite(21, LOW);
}

int main(int argc, char **argv){
	
	// taking necessary data
	struct dane section1;
	section1.task_hour = 16;
	section1.task_min  = 38;
	section1.task_sec  = 00;
	section1.section_number=1;

	//creating thread
	pthread_t tid;
	pthread_create(&tid, NULL, section_thread, &section1);

	pthread_join(tid, NULL);


	calculate_second_to_task(&section1);
}
