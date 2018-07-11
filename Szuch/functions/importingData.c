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
	int numerStruktury = 0;
	while( fgets(line[i], sizeof(line), pf) != NULL){
		
		//	wykrywa komentarze
		if(line[i][0] == '#')
			continue;//pomijam linie komentarza
		
		//wykrywa rozkazy 'N'	
		else if(line[i][0] == 'N'){
			
			printf("linia %d wykrylem rozkaz 'N', analizuje...\n", i);
				
			//	sprawdza długość rozkazu 'N'
			if( STD_ORDER_N_LENGTH != strlen(line[i])){
				printf("line %d non standard line lenght(%d) watch out for spaces\n", i , STD_ORDER_N_LENGTH);
				continue;
			}

			//tworzę zmienne tymczasowe
			char type;
			int sc, h1, m1, s1, h2, m2, s2;
			if( EOF == sscanf(line[i], "%c %d %d:%d:%d %d:%d:%d", &type, &sc, &h1, &m1, &s1, &h2, &m2, &s2) ){
				printf("błąd odczytu lini %d sprawdz format rozkazu pomijam\n", i);
				continue;
			}
			//sprawdzam poprawność danych
			if(h1>24 || h2>24 || m1>60 || m2>60 || s1>60 || s2>60){
				printf("jedna z danych przekroczyla zakres w lini %d pomijam rozkaz\n",i);
				continue;
			}
			//wpisuje dane do MyData
			(pmydata + numerStruktury)->kind_of_order	= type;
			(pmydata + numerStruktury)->section_number	= sc; 
			(pmydata + numerStruktury)->task_hour_ON	= h1;
			(pmydata + numerStruktury)->task_min_ON		= m1;
			(pmydata + numerStruktury)->task_sec_ON		= s1;
			(pmydata + numerStruktury)->task_hour_OFF	= h2;
			(pmydata + numerStruktury)->task_min_OFF	= m2;
			(pmydata + numerStruktury)->task_sec_OFF	= s2;


			/*

			//drukuje komunikat na stdout
			printf("dane wpisane do struktury [%2d] programu, %c %d %d:%d:%d %d:%d:%d\n",numerStruktury,
			(pmydata + numerStruktury)->kind_of_order,
			(pmydata + numerStruktury)->section_number,
			(pmydata + numerStruktury)->task_hour_ON,
			(pmydata + numerStruktury)->task_min_ON,
			(pmydata + numerStruktury)->task_sec_ON,
			(pmydata + numerStruktury)->task_hour_OFF,
			(pmydata + numerStruktury)->task_min_OFF,	
			(pmydata + numerStruktury)->task_sec_OFF  );
			*/		
		//inkrementuje numer Struktury
			numerStruktury++;

		}
		//wykrywam rozkaz 'O'
		else if(line[i][0] == 'O'){
				
			printf("linia %d wykrylem rozkaz 'O', analizuje...\n", i);
				
			//tworzę zmienne tymczasowe
			char type;
			int sc, h1, m1, s1, okres, h2, m2, s2, czas_trwania_rozkazu;
			if( EOF == sscanf(line[i], "%c %d %d:%d:%d %d %d:%d:%d %d", &type, &sc, &h1, &m1, &s1, &okres, &h2, &m2, &s2, &czas_trwania_rozkazu) ){
				printf("błąd odczytu lini %d, sprawdz format!, rozkaz pomijam\n", i);
				continue;
			}
			//sprawdzam poprawność danych
			if(sc>99 || h1>24 || m1>60 || s1>60 || okres>1440 || h2>24 || m2>60 || s2>60 || (czas_trwania_rozkazu/60)>okres){
				printf("jedna z danych przekroczyla zakres w lini %d pomijam rozkaz\n",i);
				continue;
			}
			if(h1<0 || m1<0 || okres<0 || s1<0 || h2<0 || m2<0 || okres<0 || s2<0 || czas_trwania_rozkazu<0 ){
				printf("jedna z danych ujemna w lini %d pomijam rozkaz\n",i);
				continue;
			}
		//wpisuje dane do MyData
			(pmydata + numerStruktury)->kind_of_order		= type;
			(pmydata + numerStruktury)->section_number		= sc; 
			(pmydata + numerStruktury)->task_hour_ON		= h1;
			(pmydata + numerStruktury)->task_min_ON			= m1;
			(pmydata + numerStruktury)->task_sec_ON			= s1;
			(pmydata + numerStruktury)->task_period_in_min	= okres;
			(pmydata + numerStruktury)->task_lasting_in_sec	= czas_trwania_rozkazu;
			(pmydata + numerStruktury)->task_hour_OFF		= h2;
			(pmydata + numerStruktury)->task_min_OFF		= m2;
			(pmydata + numerStruktury)->task_sec_OFF		= s2;

			/*
			//drukuje komunikat na stdout
			printf("dane wpisane do struktury[%d] programu, '%c' %d %d:%d:%d %d %d:%d:%d %d\n", 
			numerStruktury,
			(pmydata + numerStruktury)->kind_of_order, 
			(pmydata + numerStruktury)->section_number,
			(pmydata + numerStruktury)->task_hour_ON,
			(pmydata + numerStruktury)->task_min_ON,
			(pmydata + numerStruktury)->task_sec_ON, 
			(pmydata + numerStruktury)->task_period_in_min,
			(pmydata + numerStruktury)->task_hour_OFF,
			(pmydata + numerStruktury)->task_min_OFF, 
			(pmydata + numerStruktury)->task_sec_OFF, 
			(pmydata + numerStruktury)->task_lasting_in_sec );
			*/
		//inkrementuje numer Struktury
			numerStruktury++;

		}
		// WYKRYWAM ROZKAZ T 
		else if(line[i][0] == 'T'){
			printf("linia %d wykrylem rozkaz 'T', analizuje...\n", i);
						
			//tworzę zmienne tymczasowe
			char type;
			int sc, h1, m1, s1, czas_trwania_rozkazu;
			if( EOF == sscanf(line[i], "%c %d %d:%d:%d %d", &type, &sc, &h1, &m1, &s1, &czas_trwania_rozkazu) ){
				printf("błąd odczytu lini %d, sprawdz format!, rozkaz pomijam\n", i);
				continue;
			}
			//sprawdzam poprawność danych
			if(sc>99 || h1>24 || m1>60 || s1>60 || czas_trwania_rozkazu>84600){
				printf("jedna z danych przekroczyla zakres w lini %d pomijam rozkaz\n",i);
				continue;
			}
			if(h1<0 || m1<0 || s1<0 || czas_trwania_rozkazu<0 ){
				printf("jedna z danych ujemna w lini %d pomijam rozkaz\n",i);
				continue;
			}
		//wpisuje dane do MyData
			(pmydata + numerStruktury)->kind_of_order		= type;
			(pmydata + numerStruktury)->section_number		= sc; 
			(pmydata + numerStruktury)->task_hour_ON		= h1;
			(pmydata + numerStruktury)->task_min_ON			= m1;
			(pmydata + numerStruktury)->task_sec_ON			= s1;
			(pmydata + numerStruktury)->task_lasting_in_sec	= czas_trwania_rozkazu;
			/*
			//drukuje komunikat na stdout
			printf("dane wpisane do struktury[%d] programu, '%c' %d %d:%d:%d %d", 
			numerStruktury,
			(pmydata + numerStruktury)->kind_of_order, 
			(pmydata + numerStruktury)->section_number,
			(pmydata + numerStruktury)->task_hour_ON,
			(pmydata + numerStruktury)->task_min_ON,
			(pmydata + numerStruktury)->task_sec_ON, 
			(pmydata + numerStruktury)->task_lasting_in_sec );
			*/
		//inkrementuje numer Struktury
			numerStruktury++;

		}
		else{
			printf("linia %d NIEZNANY ROZKAZ: ", i);
			printf("%s popraw formule ", line[i]);
		}
	//zwiększenie licznika linii
	i++;
	}	

	

	//zamyka plik	
	fclose(pf);
	return numerStruktury;
}
