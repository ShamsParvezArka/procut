#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "corefn.h"

#define CAP 1000

int main(int argc, char *argv[])
{
	double cpu_time;
	char ch, in_path[CAP], buf[CAP], *parameters[CAP];
	time_t start, end;
	
	parameters[0] = "--only-merge";
	parameters[1] = "--only-cut";
	parameters[2] = "--cut-merge";
	parameters[3] = "--help";

	if(strcmp(argv[1],parameters[0]) == 0){	
		time(&start);
		only_merge();
		time(&end);
		cpu_time = difftime(end,start);	
		printf("\n");
		printf("[\033[0;33mINFO\033[0m] Video exported in the 'output' directory\n");
		printf("[\033[0;32mSUCESS\033[0m] Exporting video done in %f seconds\n", cpu_time);
		printf("\n");
		return 0;
	}
	
	else if(((argc%2) == 0) && (strcmp(argv[1],parameters[1]) == 0)){
		printf("[\033[0;33m*\033[0m] Source video path: ");
		scanf("%[^\n]", in_path);
		
		FILE *fp;
		
		time(&start);
		cut(argc, argv, in_path, buf);
		time(&end);	

		cpu_time = difftime(end,start);
		printf("\n");
		printf("[\033[0;33mINFO\033[0m] All trimmed videos are saved in the 'output' directory\n");	
		printf("[\033[0;32mSUCESS\033[0m] Exporting video done in %f s\n", cpu_time);
		printf("\n");
		
		return 0;
	}
		
	else if(((argc%2) == 0) && (strcmp(argv[1], parameters[2]) == 0)){
		printf("[\033[0;33m*\033[0m] Source video path: ");
		scanf("%[^\n]", in_path);
		
		time(&start);
		cut(argc, argv, in_path, buf);
		merge(buf);
		time(&end);

		cpu_time = difftime(end,start); 
		printf("\n");
		printf("[\033[0;33mINFO\033[0m] Video exported in the 'output' directory\n");
		printf("[\033[0;32mSUCESS\033[0m] Exporting video done in %f s\n", cpu_time); 
		printf("\n");

		return 0;

	}

	else if(strcmp(argv[1], parameters[3]) == 0){
		FILE *fp;
		fp = fopen("src/help", "r");
		while((ch = fgetc(fp)) != EOF){
			printf("%c", ch);
		}
		fclose(fp);

	}

	else{
		printf("[\033[0;31mERROR\033[0m]  Invalid parameters provided!\n");
		printf("[\033[0;33mINFO\033[0m] Use --help option for user manual\n");
		return 0;
	}
	
	
}


