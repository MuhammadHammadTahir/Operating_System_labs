#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
char input[10];
char *com[2];

pid_t pid;
	while(1)
	{
		printf("Enter the command to excecute : ");
		fgets(input, sizeof(input), stdin);
		input[strcspn(input, "\n")] = '\0';
		com[0]=input;
		com[1]=NULL;
		pid= fork();
		if(pid<0)
		{
			perror("Error in creating child process");
			return 0;
		}
		if(pid==0)
		{
			printf("Child process\n");
			execv(com[0],com);
			perror("execv");
			break;
		}
		else
		{
			sleep(2);
			printf("Parent process");
			break;
		}
	}
	return 0;
}


