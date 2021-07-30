#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>

#define CAP 1000

int k = 1;

void cut(int argc, char *argv[], char in_path[CAP], char buf[CAP]);
void merge(char buf[CAP]);
void only_merge(void);

void cut(int argc, char *argv[], char in_path[CAP], char buf[CAP])
{
	FILE *fp;
	fp = fopen("output/l", "w+");
		
	for(int i=1; i<argc; i++){
		if(i%2 == 0){
			fprintf(fp, "ffmpeg -i %s -ss %s -to %s -c copy output/%d.mp4\n",in_path,argv[i],argv[i+1],k);
			k += 1;
		}
	}

	fclose(fp);

	fp = fopen("output/l", "r");
	for(int i=1; i<k; i++){
		fgets(buf, CAP, (FILE*)fp);
		system(buf);
	}
	fclose(fp);
}

void merge(char buf[CAP])
{

	FILE *fp;
	fp = fopen("output/l", "w+");
	for(int i=1; i<k; i++){
		fprintf(fp, "file %d.mp4\n", i);
	}
	fclose(fp);
	system("ffmpeg -f concat -i output/l -c copy output/final.mp4");
	
	for(int i=1; i<k; i++){
		sprintf(buf, "output/%d.mp4", i);
		remove(buf);
	}

	
}

void only_merge(void)
{
	FILE *fp;
	DIR *path;
	struct dirent *dir;
	path = opendir("merge");
	
	if(path){
		fp = fopen("merge/l", "w+");
		while((dir = readdir(path)) != NULL){
			if(dir -> d_name[0] != '.' && dir -> d_name[0] != 'l'){
				fprintf(fp, "file %s\n", dir -> d_name);
			}
		}
		fclose(fp);
		closedir(path);
		system("ffmpeg -f concat -i merge/l -c copy output/final.mp4");	
	}

}
