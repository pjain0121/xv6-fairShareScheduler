/*
 * Names: Preet Jain / Devam Punitbhai Patel
 * NSID: pvj636 / dns682
 * Student Numbers: 11270494 / 11316715
 */

#include "kernel/types.h"
#include "user/user.h"

int mainst()
{
	
	int rn, i;

	rn = rand() % 100;


	printf("Creating %d processes\n",rn);
	int pid[rn];

	for(i = 0; i < rn; i++)
	{
		
		pid[i] = fork();

		if(pid[i] == 0)
		{
			int sqRn, j;

			if((rand()%2) ==0)
			{
				printf("%d sleeping\n", getpid());
			
				sleep(rand() % 100);
			}

			sqRn = rand() % 1000;
	 
			printf("%d calling Square() %d times\n", getpid(), sqRn); 
			
			for(j = 0; j < sqRn; j++)
			{
				/*printf("Square() called\n");*/
				Square(rand() % 100);
			}
			
			printf("%d done calling Square() %d times\n", getpid(), sqRn);
			exit(0);

		}
	
	}
	
	for(i = 0; i < rn; i ++)
	{
		int s;
		wait(&s);
	}
	exit(0);

	return 0;
}
