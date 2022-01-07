#include "headers.h"
#include "execute_com.c"
char** tokenise_commands(char *input);
 void statusCommand(int stat);
char *get_input()
{
    ssize_t input_size = 0;
    char *input_line = NULL;
    getline(&input_line, &input_size, stdin);
    return input_line;
}

void prompt1(char* s)
{
    namePrompt=s;
        }

void prompt(){
printf("%s:",namePrompt);
}

char **tokenize(char *input){
no = 0;

    char *p = strtok (input, ";");
    char **array = malloc(256 * sizeof(char *));

    
    while (p != NULL)
    {
        array[no++] = p;
        p = strtok (NULL, ";");
    }

    return array;
}


void shell()
{
    char *input;

    do
    {
        CHILD_ID = -1;
        prompt();
        input = get_input();
    
        char **commands;
        commands = tokenize(input);
       
      
        for(int i = 0; i < no; i++){
        
            execute_com(commands[i]);
            if(strcmp(commands[i], "!!") == 0){
        //    printf("%s The last command was \n", history(commands[i]));
    execute_com(history(commands[i]));}
            
              else if(strcmp(commands[i], "quit") == 0)
    {
       // write_history();
     //  overkill();
        exit(0);
    }
    
    }
          
                     //  if(strcmp("prompt",commands[0])==0&&strcmp("=",commands[1])==0)
                 //  {
                 //  namePrompt="lala";
           //     prompt1(commands[2]);}
            

    } while(1);
}


void ctrl_c(int signum)
{
    pid_t p = getpid();
    if(p < 0)
        perror("Error");
    
    else if (p != SHELL_ID)
        return;

    if (CHILD_ID != -1)
        kill(CHILD_ID, SIGINT);        
    
    signal(SIGINT, ctrl_c);
      printf("\n");
    printf("you typed Control-C!");
    printf("\n");
   printf("%s:",namePrompt);
   fflush(stdout);
} 
char** tokenise_commands(char *i)
{
 k = 0;
char **array1 = malloc(256 * sizeof(char *));
    char *p1=strtok (i, " ");
     while (p1 != NULL)
    {
        array1[k++] = p1;
        p1 = strtok (NULL, " ");
    }
    return array1;
   
    
         }
int main()
{

   // gethostname(HOST, sizeof(HOST));
  //  getlogin_r(USER, sizeof(USER));
    char *DIR;
  
    pid_t p_id;
    p_id = getpid();
    SHELL_ID = p_id;
    char *exe = malloc(sizeof(char) *(40));
   // sprintf(exe,"/proc/%d/exe", p_id);
    int ret = readlink(exe, HOME, 1000);
    HOME[ret] = '\0';

    for(int i = strlen(HOME)-1; i>=0; i--)
    {
        if(HOME[i] == '/')
        {
            HOME[i] = '\0';
            break;
        }
    }
    
  // load_history();
  
   
    //signal(SIGTSTP, ctrl_z);
    signal(SIGINT, ctrl_c);
    signal(SIGCHLD, handler);
    // signal(SIGCHLD, handler2);
  
    shell();
    return 0;
}
