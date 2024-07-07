#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
int main ()
{
	int status;
	pid_t pid;
	pid=fork();
	if(pid==-1)
 	{
		printf("Error in creating the child process\n");
		return -1;
	}
	else
	{
		if(pid==0 )
		{
			printf("This is the child process\n");
			execl("/bin/ls","ls",NULL);
			perror("execl");
		}
		else
		{
			wait(&status);
			printf("This is the parent process\n");
		}
	}
	return 0;
}
