#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<unistd.h>


#define SEC_IN_HOUR 3600
#define SEC_IN_MIN 60
#define NUM_OF_SECTIONS 3
#define PIN_LED_1 21
#define PIN_BUTTON_1 20

typedef struct dane{
	//task time
	char kind_of_order;
	int task_hour;
	int task_min;
	int task_sec;
	int section_number ;
} mydata;

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
/*
//turn LED on for 3 second
void task_rPi(int section ){
	//starting rPi things
	wiringPiSetupGpio();// i use BCM pin names
	pinMode(PIN_BUTTON_1, )
	pinMode(PIN_LED_1, OUTPUT);
	if(HIGH == digitalRead(){}
	digitalWrite(PIN_LED_1, HIGH);
	sleep(3);
	digitalWrite(PIN_LED_1, LOW);

}
*/
void * section_thread(void* arg){
	puts("hello form thread");
	struct dane * section = (struct dane * ) arg;
	
	sleep( calculate_second_to_task(section) ); //TODO sleep takes unsigned arg it is too small
	puts("TASK");
	

}

/*void take_sections_data_from_file(void * arg){
	mydata * section = (mydata*) arg;
	
	
	section->task_hour=12;
	section->task_min=23;
	section->task_sec=43;
	section->section_number=1 ;

	FILE * outfile;
	outfile=fopen("data.dat", "r");
	if(outfile == NULL){
		puts("error");
		exit(1);
	}

	

}*/

int main(int argc, char **argv){
	
	// taking necessary data
	mydata section[NUM_OF_SECTIONS];
	FILE * fp;
	fp=fopen("time_table", "r");
	if(fp == NULL){
		puts("error");
		exit(1);
	}
	char string[20];
	fgets(string, 12, fp);//zabiera pierwszy wiersz
	int i;
	for(i=0; i< NUM_OF_SECTIONS; i++){
	
		fscanf(fp, "%d %d %d %d", &section[i].section_number, &section[i].task_hour, &section[i].task_min, &section[i].task_sec);
		printf("%d %d %d %d\n", section[i].section_number, section[i].task_hour, section[i].task_min, section[i].task_sec);
	}
// end of taking necessary data	
	

	pthread_t tid[NUM_OF_SECTIONS];
	//creating threads
	for(i=0; i<NUM_OF_SECTIONS; i++){

		pthread_create(&tid[i], NULL, section_thread, &section[i]);
	}
	
	for(i=0; i<NUM_OF_SECTIONS; i++){

		pthread_join(tid[i], NULL);

	}
	//calculate_second_to_task(&section1);
	
}
