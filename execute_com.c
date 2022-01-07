#include "headers.h"
#include "pwd.c"
#include "cd.c"
#include "echo.c"
#include "run.c"

#include "history.c"

#include "redirection.c"

void execute_com(char *command);

void cron(char **args, int no_args)
{
    int ti, total, note;
    if(no_args < 7)
        printf("Enter command in the form `cronjob -c ls -t 3 -p 6`");
  
    else 
    {
        for(int i=0; i < no_args; i++)
        {
            if(strcmp(args[i],"-c") == 0)
                note = i+1;

            else if(strcmp(args[i],"-t") == 0)
                ti = atoi(args[i+1]);

            else if(strcmp(args[i],"-p") == 0)
                total = atoi(args[i+1]);
        }
    
        no_args -= 6;

        for(int i=0; i < no_args; i++)
            args[i] = args[i+note];

        args[no_args] = NULL;
    } 

    int repeat = total / ti;
    pid_t pid = fork();
    if (pid == 0)
    {
        char *str = malloc(1000* sizeof(char));
        // printf("%s\n", str);
        while (repeat > 0)
        {
            strcpy(str, args[0]);
            for(int i=1; args[i] != NULL; i++)
            {
                strcat(str, " ");
                strcat(str, args[i]);
            }
            repeat--;
            sleep(ti);
            execute_com(str);
            prompt();
            fflush(stdout);
        }

        free(str);

        exit(0);
    } 
    
}

char **pipe_elements(char *input)
{
    char *p = strtok (input, "|");
    char **pipe_args = malloc(256 * sizeof(char *));

    int oof = 0;

    while (p != NULL)
    {
        pipe_args[oof++] = p;
        p = strtok (NULL, "|");
    }

    return pipe_args;
}

void piping(char *command)
{
    char **pipe_args = pipe_elements(command);
    int pipes[2], fd = 0; pid_t proc;

    for(int j=0; pipe_args[j]!= NULL; j++)
    {
        pipe(pipes);
        proc = fork();
        
        if(proc < 0) perror("hello");
        
        else if(proc > 0)
        {
            wait(NULL);
            close(pipes[1]);
            fd = pipes[0];
        }

        else if(proc == 0)
        {
            dup2(fd , 0);
            
            if(pipe_args[j+1]!=NULL) 
                dup2(pipes[1],1);
            
            close(pipes[0]);
            execute_com(pipe_args[j]);
            exit(2);
        }
    }
}

int check_redirection(char *command)
{
    char *out = strstr(command, ">");
    char *in = strstr(command, "<");

    if((out != NULL) && (in != NULL))
        return 3;
    
    else if(out != NULL)
        return 2;
    
    else if(in != NULL)
        return 1;

    else return 0;
}

int check_piping(char *command)
{
    char *is_pipe = strstr(command, "|");
    if(is_pipe != NULL)
        return 1;

    else return 0;
}

void removeSpaces(char *str) 
{ 
    int count = 0; 
    for (int i = 0; str[i]; i++) 
        if (str[i] != ' ' && str[i]!='\t' && str[i]!='\n') 
            str[count++] = str[i]; 

    str[count] = '\0'; 
} 


void execute_com(char *command)
{
    
    char *com = (char *)malloc(sizeof(char) *2000);
    char *com2 = (char *)malloc(sizeof(char) *2000);
    strcpy(com, command);
    strcpy(com2, command);
    removeSpaces(com2);
    int up = 0;
    com = strtok(com, " \n\t\r");
    
    if(com == NULL)
        return;

   
    strcpy(hist[hist_i % 20], command);
    hist_i++;

    char **args = (char**)malloc(sizeof(char*) * 100);
    int no_args = 0;
    
    while (com != NULL)
    {
        //printf("%s\n",com);
        args[no_args]  = (char *)malloc(sizeof(char) *strlen(com)+10);
        strcpy(args[no_args], com);
        com = strtok(NULL, " \n\t\r");
        no_args++;
    }

    if(check_piping(command))
    {
        piping(command);
        //fork_pipes(command);
        return;
    }

    if(check_redirection(command))
    {
        redirection(command);
        return;
    }

    command = strtok(command, " \n\t\r");

 
 if(!strcmp(args[no_args-1], "&"))
    {
        args[no_args-1] = NULL;
        run(args, no_args, 1);
    }



  

    else if(strcmp(command, "pwd") == 0)
        pwd();

    else if(strcmp(command, "cd")==0)
        cd(command);

    else if(strcmp(command ,"echo")==0)
        echo(status,args);


 //else if(strcmp(command, "!!") == 0)
   // history(command);
 
 


    else run(args, no_args, 0);
    
    for(int j=0; j < no_args && args[j]!=NULL; j++)
        free(args[j]);

        free(com2);
        free(com);
        free(args);  
    
}
