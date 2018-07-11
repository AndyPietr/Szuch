#include<stdio.h>
#include<string.h>
#include"mylib.h"

char* filePath = "dane";

int import(void* arg){

	MyData* pmydata = (MyData*) arg; 
	

	FILE * pf;
	pf = fopen(filePath, "r");
	if(pf==NULL){
		puts("error opening file");
		return(-1);	
	}
	char line[MAX_FILE_LINES][MAX_LINE_WIDTH];

// 	główna pętla czytająca
	int i=0;
	while( fgets(line[i], sizeof(line), pf) != NULL){
		
		//	wykrywa komentarze
		if(line[i][0] == '#')
			continue;//pomijam linie komentarza
		
		//wykrywa rozkazy 'N'	
		else if(line[i][0] == 'N'){
				
			//	sprawdza długość rozkazu 'O'
			if( STD_ORDER_O_LENGTH != strlen(line[i])){
				printf("line %d non standard line lenght(%d) watch out for spaces\n", i , STD_ORDER_O_LENGTH);
				continue;
			}

			printf("linia %d wykrylem rozkaz N, analizuje...\n", i);
			//tworzę zmienne tymczasowe
			char type;
			int sc, h1, m1, s1, h2, m2, s2;
			if( EOF == sscanf(line[i], "%c %d %d:%d:%d %d:%d:%d", &type, &sc, &h1, &m1, &s1, &h2, &m2, &s2) ){
				printf("błąd odczytu lini %d sprawdz format rozkazu pomijam\n", i);
				continue;
			}
			printf("%c %d %d:%d:%d %d:%d:%d\n", type, sc,h1,m1,s1,h2,m2,s2);
			//sprawdzam poprawność danych
			if(h1>24 || h2>24 || m1>60 || m2>60 || s1>60 || s2>60){
				printf("jedna z danych przekroczyla zakres w lini %d pomijam rozkaz\n",i);
				continue;
			}
			//wpisuje dane do MyData
			pmydata->kind_of_order  = type;
			pmydata->section_number = sc; 
			pmydata->task_hour_ON	= h1;
			pmydata->task_min_ON	= m1;
			pmydata->task_sec_ON	= s1;
			pmydata->task_hour_OFF	= h2;
			pmydata->task_min_OFF	= m2;
			pmydata->task_sec_OFF	= s2;

			printf("dane wpisane do struktury programu, %c %d %d:%d:%d %d:%d:%d\n",pmydata->kind_of_order,pmydata->section_number,pmydata->task_hour_ON,	pmydata->task_min_ON,pmydata->task_sec_ON,pmydata->task_hour_OFF,pmydata->task_min_OFF,	pmydata->task_sec_OFF);
		
		}
		else if(line[i][0] == 'O'){
			puts("wykrylem rozkaz O wpisuje do MyData");
			pmydata->kind_of_order = 'O';
			printf("pmydata->kind_of_order = %c\n", pmydata->kind_of_order );
			puts("scaned line below");
			puts(line[i]);

		}
		else if(line[i][0] == 'T'){
			puts("wykrylem rozkaz T, wpisuje do MyData");
			pmydata->kind_of_order = 'T';
			printf("pmydata->kind_of_order = %c\n", pmydata->kind_of_order );
			puts("scaned line below");
			puts(line[i]);

		}
		else{
			puts("nieznany rozkaz");
			printf("i=%d\n", i);
			puts(line[i]);
		}
	i++;
	}	
	
	
	fclose(pf);
	return 0;
}
