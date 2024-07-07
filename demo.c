#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>
void exitfunc() { 
printf("Called cleanup function - exitfunc()\n"); 
return; 
} 
int main() { 
atexit(exitfunc); 
printf("Exit Call!\n"); 
_exit (0); 
} 
