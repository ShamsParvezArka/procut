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
	char ch, in_path[CAP], buff[CAP], *parm_join, *parm_cut, *parm_cut_merge, *parm_help;
	time_t start, end;
	
	parm_join = "--only-merge";
	parm_cut =  "--only-cut";
	parm_cut_merge = "--cut-merge";
	parm_help = "--help";

	if(strcmp(argv[1],parm_join) == 0){
		only_merge();
		return 0;
	}
	
	else if(((argc%2) == 0) && (strcmp(argv[1],parm_cut) == 0)){
		printf("[\033[0;33m*\033[0m] Source video path: ");
		scanf("%[^\n]", in_path);
		
		FILE *fp;
		
		time(&start);
		cut(argc, argv, in_path, buff);
		time(&end);	

		cpu_time = difftime(end,start);
		printf("\n");
		printf("[\033[0;33mINFO\033[0m] All trimmed videos are saved in the 'output' directory\n");	
		printf("[\033[0;32mSUCESS\033[0m] Exporting video done in %f s\n", cpu_time);
		printf("\n");
		
		return 0;
	}
		
	else if(((argc%2) == 0) && (strcmp(argv[1], parm_cut_merge) == 0)){
		FILE *fp;
		time(&start);
		cut(argc, argv, in_path, buff);
		fp = fopen("output/l", "w+");
		for(int i=1; i<k; i++){
			fprintf(fp, "file %d.mp4\n", i);
		}
		fclose(fp);
		merge();
		time(&end);

		cpu_time = difftime(end,start); 
		printf("\n");
		printf("[\033[0;33mINFO\033[0m] Video exported in the 'output' directory\n");
		printf("[\033[0;32mSUCESS\033[0m] Exporting video done in %f s\n", cpu_time); 
		printf("\n");

		return 0;

	}

	else if(strcmp(argv[1], parm_help) == 0){
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


