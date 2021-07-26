#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>

#define CAP 1000

int k = 1;

void cut(int argc, char *argv[], char in_path[CAP], char buff[CAP]);
void join(void);
void only_join(void);

void cut(int argc, char *argv[], char in_path[CAP], char buff[CAP])
{
	FILE *fp;
	fp = fopen("process/l", "w+");
		
	for(int i=1; i<argc; i++){
		if(i%2 != 0){
			fprintf(fp, "ffmpeg -i %s -ss %s -to %s -c copy process/%d.mp4\n",in_path,argv[i],argv[i+1],k);
			k += 1;
		}
	}

	fclose(fp);

	fp = fopen("process/l", "r");
	for(int i=1; i<k; i++){
		fgets(buff, CAP, (FILE*)fp);
		system(buff);
	}
	fclose(fp);
}

void join(void)
{
	system("ffmpeg -f concat -i process/l -c copy output/final.mp4");
}

void only_join(void)
{
	time_t start, end;
	double cpu_time;

	FILE *fp;
	DIR *path;
	struct dirent *dir;
	path = opendir("join");
	
	if(path){	
		time(&start);
		fp = fopen("join/l", "w+");
		while((dir = readdir(path)) != NULL){
			if(dir->d_name[0] != '.' && dir->d_name[0] != 'l'){
				fprintf(fp, "file %s\n", dir->d_name);
			}
		}
		fclose(fp);
		closedir(path);
		system("ffmpeg -f concat -i join/l -c copy output/final.mp4");
		time(&end);
	
		cpu_time = difftime(end,start);
		printf("\n");
		printf("[\033[0;33mINFO\033[0m] Video exported in the 'output' directory\n");
		printf("[\033[0;32mSUCESS\033[0m] Exporting video done in %f seconds\n", cpu_time);
	}

}
