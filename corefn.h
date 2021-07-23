#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define CAP 1000

int k = 1;

int cut(int argc, char *argv[], char path[CAP], char buff[CAP]);

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
