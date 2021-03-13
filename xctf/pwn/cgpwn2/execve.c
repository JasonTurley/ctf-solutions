// demo for exploit
// the challenge binary does not have the system() function, however it does
// have the syscall() function. Goal is to run syscall(execve('/bin/sh', NULL, NULL))
// to get a shell

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	/* 
	 * This is how a normal call to execve works:
	printf("Calling execve!\n");
	execve("/bin/sh", NULL, NULL);

	printf("Error: I should never return!\n");
	*/

	syscall(59, "/bin/sh", NULL, NULL);
	return 0;
}
