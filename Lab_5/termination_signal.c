#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
int main()
{
	pid_t pid;
	pid= fork();
	if(pid==-1)
	{
		printf("Error in creating the child process\n");
		return -1;
	}
	if(pid==0)
	{
		while(1)
		{
			printf("Child process Executing.......\n");
			sleep(2);
		}
	}
	else
	{
		printf("This is the parent process\n");
		sleep(6);
		kill(pid, SIGINT);
		perror("kill");
	}
	return 0;
}
