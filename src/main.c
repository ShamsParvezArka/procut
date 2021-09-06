#include "cfn.h"


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
		printf("[\033[0;33m INFO\033[0m ] Video exported in the 'output' directory\n");
		printf("[\033[0;32mSUCESS\033[0m] Exporting video done in %f seconds\n", cpu_time);
		printf("\n");
		return 0;
	}
	
	else if(((argc%2) == 0) && (strcmp(argv[1],parameters[1]) == 0)){
		printf("[\033[0;33m*\033[0m] Source video path: ");
		scanf("%[^\n]", in_path);			
		
		FILE *fp;
		if((fp = fopen(in_path, "r"))){
			time(&start);
			cut(argc, argv, in_path, buf);
			time(&end);	
	
			cpu_time = difftime(end,start);
			printf("\n");
			printf("[\033[0;33m INFO\033[0m ] All trimmed videos are saved in the 'output' directory\n");	
			printf("[\033[0;32mSUCESS\033[0m] Exporting video done in %f s\n", cpu_time);
			printf("\n");
			
			return 0;
		}
		else{
			fprintf(stderr, "[\033[0;31mERROR\033[0m] Cannot start '%s' : No such file\n", in_path);
			return 1;
		}
	}
		
	else if(((argc%2) == 0) && (strcmp(argv[1], parameters[2]) == 0)){
		FILE *fp;
		printf("[\033[0;33m*\033[0m] Source video path: ");
		scanf("%[^\n]", in_path);
		if((fp = fopen(in_path, "r"))){
			time(&start);
			cut(argc, argv, in_path, buf);
			merge(buf);
			time(&end);
	
			cpu_time = difftime(end,start); 
			printf("\n");
			printf("[\033[0;33m INFO\033[0m ] Video exported in the 'output' directory\n");
			printf("[\033[0;32mSUCESS\033[0m] Exporting video done in %f s\n", cpu_time); 
			printf("\n");
	
			return 0;
		}
		else{
			fprintf(stderr, "[\033[0;31mERROR\033[0m] Cannot start '%s' : No such file\n", in_path);
			return 1;
		}
	}

	else if(strcmp(argv[1], parameters[3]) == 0){
		FILE *fp;
		fp = fopen("src/help", "r");
		while((ch = fgetc(fp)) != EOF){
			printf("%c", ch);
		}
		fclose(fp);

	}

	//error handling 
	else if(((argc%2) != 0) && ((strcmp(argv[1],parameters[1]) == 0) || (strcmp(argv[1], parameters[2]) == 0))){
		fprintf(stderr, "[\033[0;31mERROR\033[0m] Invalid parameter provided!\n");
		fprintf(stderr, "[\033[0;33mINFO\033[0m ] Use --help option for user manual\n");
		return 1;
		}


	else{
		fprintf(stderr, "[\033[0;31mERROR\033[0m] Invalid argument provided!\n");
		fprintf(stderr, "[\033[0;33mINFO\033[0m ] Use --help option for user manual\n");
		return 1;
	}
	
	
}
