#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define CAP 1000

int main(int argc, char *argv[])
{
	int k;
	char path[CAP], buff[CAP], cmd[CAP], outname[CAP];
	k = 1;
	printf("[*] Video path:");
	scanf("%[^\n]", path);

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

	fp = fopen("process/list", "w+");
	for(int i=1; i<k; i++){
		fprintf(fp, "file %d.mp4\n", i);
	}
	fclose(fp);

	system("ffmpeg -safe 0 -f concat -i process/list -c copy ~/programming/procut/output/final.mp4");
	printf("-------------------------------\n");

	return 0;
}
