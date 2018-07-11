#define MAX_LINE_WIDTH 256
#define MAX_FILE_LINES 300

#define STD_ORDER_O_LENGTH 23

#define SEC_IN_HOUR 3600
#define SEC_IN_MIN 60
#define NUM_OF_SECTIONS 3
#define PIN_LED_1 21
#define PIN_BUTTON_1 20



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
