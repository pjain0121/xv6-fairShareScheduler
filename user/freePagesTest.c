/*
 * Names: Preet Jain / Devam Punitbhai Patel
 * NSID: pvj636 / dns682
 * Student Numbers: 11270494 / 11316715
 */

#include "kernel/types.h"
#include "user/user.h"

int main()
{
	int pid;
	printf("number of free pages before fork: %d\n", getNumFreePages());
	pid = fork();
	if(pid == 0)
	{
		printf("number of free pages after fork from child: %d\n", 
		getNumFreePages());
		exit(0);
	}
	else
	{
		int s;
		wait(&s);
		printf("number of free pages after fork from parent: %d\n", 
		getNumFreePages());
		exit(0);
	}
	return 0;
}
