#include<stdio.h>
#include<string.h>

#define MAX_LINE_WIDTH 256
#define MAX_FILE_LINES 100

int main(){

	FILE * pf;
	pf = fopen("dane", "r");
	if(pf==NULL){
		puts("error opening file");
		return(-1);	
	}
	char line[MAX_FILE_LINES][MAX_LINE_WIDTH];

	int i=0;
	while( fgets(line[i], sizeof(line), pf) != NULL){
	
		if(line[i][0] == '#')
			continue;
		if(line[i][0] == 'N')
			puts("wykrylem rozkaz N");
		if(line[i][0] == 'O')
			puts("wykrylem rozkaz O");
		if(line[i][0] == 'T')
			puts("wykrylem rozkaz T");
	i++;
	}	
	
	
	fclose(pf);
}
