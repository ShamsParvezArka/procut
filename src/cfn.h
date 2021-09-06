#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>

#define CAP 1000

int k = 1;

void cut(int argc, char *argv[], char in_path[CAP], char buf[CAP]);
void merge(char buf[CAP]);
void only_merge(void);

