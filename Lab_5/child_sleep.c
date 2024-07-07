#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main()
{
	pid_t pid;
	pid=fork();
	if(pid==-1)
	{
		printf("Error in creating the child process");
		return -1;
	}
	if(pid==0)
	{
		execl("/bin/sleep","sleep","10",NULL);
		perror("execl");
		printf("Child Process\n");

	}
	else
	{
		printf("This is the Parent process\n");
		return 0;
	}
	return 0;
}
