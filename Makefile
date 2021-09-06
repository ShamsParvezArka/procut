CC = gcc

procut: src/main.c src/cfn.h
	$(CC) -ggdb src/main.c src/cfn.h -o bin/procut
