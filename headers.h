#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <dirent.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <sys/wait.h>
#include<sys/types.h>
#include <fcntl.h> 

#define EXIT_FAILURE 1
char * namePrompt="hello";
char *argv[10];
char command[1024];

char *token;
char HOST[1024], USER[1024], CWD[2048], HOME[2048];
int no, back_g;
char hist[20][1000];
int bang_flag;
int hist_i;
int status;
int k;
pid_t SHELL_ID, CHILD_ID = -1;
char CURR_JOB[2000];

struct bg_job
{
    char job_name[300];
    pid_t PID;  
};

typedef struct bg_job bg_job;
bg_job jobs[50];
  void statusCommand(int stat) {
	// Checks to see if the last stat was succesful or not and prints out the value
	if (WIFEXITED(stat))
		stat = WEXITSTATUS(stat);
	else
		stat = WTERMSIG(stat);
	printf("%d\n", stat);
}
void filewrite();
void history_execute_with_constants();
void fileprocess ();
void prompt1(char* s);
void prompt();
char * read_file(char *filename, int n);
#endif
