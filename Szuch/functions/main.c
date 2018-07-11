#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<unistd.h>
#include"mylib.h"



int main(int argc, char **argv){
	
	MyData mydata[MAX_FILE_LINES];
	int iloscOdczytanychStruktur = import(mydata);
	creatingThreads(mydata, iloscOdczytanychStruktur);
	return 0;
}
