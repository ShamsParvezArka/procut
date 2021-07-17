#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define CAP 1000
int k = 1;

int cut(int argc, char *argv[], char path[CAP], char buff[CAP]);

int main(int argc, char *argv[])
{
	int choice;
	char path[CAP], buff[CAP], outname[CAP];
	printf("[*] Video path:");
	scanf("%[^\n]", path);
	printf("\t 1. Cut\n");
	printf("\t 2. Cut & Join\n");
	printf("[*] Choose option");
	scanf("%d", &choice);

	FILE *fp;
	
	if(choice==1){
		cut(argc, argv, path, buff);
		return 0;
	}
	
	else if(choice==2){
		cut(argc, argv, path, buff);
		fp = fopen("process/list", "w+");
		for(int i=1; i<k; i++){
			fprintf(fp, "file %d.mp4\n", i);
		}
		fclose(fp);

		system("ffmpeg -safe 0 -f concat -i process/list -c copy ~/programming/procut/output/final.mp4");

		return 0;
	}
}


int cut(int argc, char *argv[], char path[CAP], char buff[CAP])
{
	FILE *fp;
	fp = fopen("process/list", "w+");
	
	if((argc%2)-1 == 0){	
		for(int i=1; i<argc; i++){
			if(i%2 != 0){
				fprintf(fp, "ffmpeg -i %s -ss %s -to %s -c copy process/%d.mp4\n",path,argv[i],argv[i+1],k);
				k += 1;
			}
		}
	}
	else{
		printf("error: not sufficient arguments provided");
		return 0;
	}
	fclose(fp);

	fp = fopen("process/list", "r");
	for(int i=1; i<k; i++){
		fgets(buff, CAP, (FILE*)fp);
		system(buff);
	}
	fclose(fp);
}
