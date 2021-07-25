#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "corefn.h"

#define CAP 1000

int main(int argc, char *argv[])
{
	int choice;
	double cpu_time;
	char in_path[CAP], buff[CAP];
	time_t start, end;

	printf("[\033[0;33m*\033[0m] Source video path: ");
	scanf("%[^\n]", in_path);
	printf("\n");
	printf("\t 1. Cut\n");
	printf("\t 2. Cut & Join\n");
	printf("[\033[0;33m*\033[0m] Choose option: ");
	scanf("%d", &choice);
	
	FILE *fp;
	
	if(choice==1){
		time(&start);
		cut(argc, argv, in_path, buff);
		time(&end);	

//		printf("\e[1;1H\e[2J");
		cpu_time = difftime(end,start);
		printf("[\033[0;33mINFO\033[0m] All trimmed videos are saved in the 'process' directory\n");	
		printf("[\033[0;32mSUCESS\033[0m] Exporting video done in %f seconds\n", cpu_time);
		
		return 0;
	}
	
	else if(choice==2){
		time(&start);
		cut(argc, argv, in_path, buff);
		fp = fopen("process/l", "w+");
		for(int i=1; i<k; i++){
			fprintf(fp, "file %d.mp4\n", i);
		}
		fclose(fp);
		join();
		time(&end);

//		printf("\e[1;1H\e[2J");
		cpu_time = difftime(end,start); 
		printf("[\033[0;33mINFO\033[0m] Video exported in the 'output' directory\n");
		printf("[\033[0;32mSUCESS\033[0m] Exporting video done in %f seconds\n", cpu_time); 
		
		return 0;
	}
}


