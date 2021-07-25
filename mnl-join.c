#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include "corefn.h"

#define CAP 1000

int main()
{	
	time_t start, end;
	double cpu_time;

	FILE *fp;
	DIR *path;
	struct dirent *dir;
	path = opendir("join");
	
	time(&start);
	fp = fopen("process/l", "w+");
	while((dir = readdir(path)) != NULL){
		if(dir->d_name[0] != '.' && dir->d_name[0] != 'l'){
			fprintf(fp, "file %s\n", dir->d_name);
		}
	}
	fclose(fp);
	closedir(path);
	
	join();
	time(&end);
	cpu_time = difftime(end,start);
	printf("[\033[0;33mINFO\033[0m] Video exported in the 'output' directory\n");
	printf("[\033[0;32mSUCESS\033[0m] Exporting video done in %f seconds\n", cpu_time); 

	return 0;
}
