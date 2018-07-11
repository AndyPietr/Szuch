#define MAX_LINE_WIDTH 256
#define MAX_FILE_LINES 300

#define STD_ORDER_N_LENGTH 23




typedef struct dane{
	char kind_of_order;
	int section_number ;
	int task_hour_ON;
	int task_min_ON;
	int task_sec_ON;
	int task_hour_OFF;
	int task_min_OFF;
	int task_sec_OFF;
	int task_period_in_min;
	int task_lasting_in_sec;
} MyData;


int import(void*);
int creatingThreads(void*, int);
void* threadFunction(void* arg);
long int calculate_sec_to(int, int, int);
int my_delay(long int); 
void* N_task(void*);
void* T_task(void*);
void* O_task(void*);
