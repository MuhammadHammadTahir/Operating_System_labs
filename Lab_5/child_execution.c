#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
int main()
{
	char input[100];
	char *com[2];
	int status;
	pid_t pid;
	printf("Enter the Command to be run : ");
	fgets(input, sizeof(input), stdin);
	input[strcspn(input, "\n")] = '\0';
	com[0]=input;
	com[1]= NULL;
	pid=fork();
	if(pid==-1)
	{
		printf("Error in creating the child process\n");
		return -1;
	}
	if(pid==0)
	{
		printf("This is the child process\n");
		execv(com[0],com);
		perror("execv");
	}
	else
	{
		wait(&status);
		printf("This is the parent process\n");
	}
	return 0;
}
