#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define CAP 1000

int k = 1;

int cut(int argc, char *argv[], char in_path[CAP], char buff[CAP]);
int join(void);

int cut(int argc, char *argv[], char in_path[CAP], char buff[CAP])
{
	FILE *fp;
	fp = fopen("process/l", "w+");
	
	if((argc%2)-1 == 0){	
		for(int i=1; i<argc; i++){
			if(i%2 != 0){
				fprintf(fp, "ffmpeg -i %s -ss %s -to %s -c copy process/%d.mp4\n",in_path,argv[i],argv[i+1],k);
				k += 1;
			}
		}
	}
	else{
		printf("error: not sufficient arguments provided");
		return 0;
	}
	fclose(fp);

	fp = fopen("process/l", "r");
	for(int i=1; i<k; i++){
		fgets(buff, CAP, (FILE*)fp);
		system(buff);
	}
	fclose(fp);
}

int join(void)
{
	
	system("ffmpeg -safe 0 -f concat -i process/l -c copy output/final.mp4");

	return 0;
}

