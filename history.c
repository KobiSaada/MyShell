#include "headers.h"

char hist_filename[2000];

void load_history()
{
    strcpy(hist_filename, HOME);
    strcat(hist_filename, "/history.txt");
    FILE *file = fopen (hist_filename, "r" );
    if( file != NULL )
    {
        char line[128]; 
        int no = 0;
        while (fgets(line, sizeof(line), file) != NULL ) 
        {
            if(no == 0)
            {
                hist_i = atoi(line);
                no = 1;
            }

            else 
            {
                strcpy(hist[no-1], line);
                no++;
            }
        }

        fclose(file);
    }
    else perror ("history.txt"); 
    return;
}

void write_history()
{
    FILE *file = fopen (hist_filename, "w" );
    int n;

    if(hist_i < 20)
        n = hist_i;
    else n = 20;

    fprintf(file, "%d\n",hist_i);
    for(int i = 0; i < n; i++)
        fprintf (file, "%s", hist[i]);

    fclose(file);
}

char * history(char *command)
{
    char *token = command;
    token = strtok(NULL, " \"\n\t\r"); 

    int n = 10;
    if(token != NULL)
        n = atoi(token);

    int count = n;
    int i;
    printf("%s",hist[i-2]);
   // printf("%s The last command was \n", hist[i-2]);
    for(i = hist_i - count; count > 0; i++, count--)
    {
       
        //count++;
    }
    printf("The last command was\n");
    printf( hist[i-2],"%s The last command was\n ");
    return hist[i-2];
    
}
