#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
	pid_t pid, mypid, myppid;
	pid= getpid();
	printf("Before fork call: Process id = %d\n", pid);
	pid=fork();
	if(pid<0){
	perror("fork():failure\n");
	return 1;}
	if(pid==0){
	printf("This is a child process.\n");
	mypid= getpid();
	myppid = getppid();
	printf("process ID is %d and PPID is %d\n", mypid, myppid);
	}
	else{
	sleep(2);
	printf("This is the parent process\n");
	mypid= getpid();
	myppid= getppid();
	printf("Process id is %d and Parent process id id %d\n", mypid, myppid);
	printf("Newly created process id or Child process id is %d\n", pid);
	}
	return 0;
}
