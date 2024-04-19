/*
 * Names: Preet Jain / Devam Punitbhai Patel
 * NSID: pvj636 / dns682
 * Student Numbers: 11270494 / 11316715
 */

#include "kernel/types.h"
#include "user/user.h"

int main()
{
	/*to store the read/write fd when we create pipe*/
	int p1[2];

	/*for the second pipe*/
	int p2[2];

	/*to store the process id of child process*/
	int pid;

	/*to store write's result*/
	int wr;

	/*to store read's result*/
	int rr;

	/*to store character read*/
	char buf[512];

	/*create a pipe and store the fds in p*/
	pipe(p1);

	/*create other pipe*/
	pipe(p2);

	/*create a child process and store it's id in pid*/
	pid = fork();

	if(pid > 0)
	{
		/*it means we are in parent process*/
		
		/*write from parent in pipe's write fd*/
		wr = write(p1[1], "i", 1);

		if(wr != 1)
		{
			printf("parent process's write on pipe failed!\n");
		}
		


		/*once the child exits we can read from pipe 2*/

		rr = read(p2[0], buf, 1);

		if(rr != 1)
		{
			printf("parent's read from pipe 2 failed!\n");
		}
		else
		{
			printf("%d: received pong\n", getpid());
			/*close pipe2*/
			close(p2[0]);
			close(p2[1]);
		}

		exit(0);
	}
	else if(pid == 0)
	{
		/*it means we are in child process*/

		/*read from child from the pipe's read fd*/
		/*because it is a read, it will wait until someone writes in pipe
		 * so we don't need to worry if child process is executed first*/
		rr = read(p1[0], buf, 1);

		if(rr != 1)
		{
			printf("child's read from pipe failed!\n");
		}
		else
		{
			/*print child's process ID and received ping*/
			printf("%d: received ping\n", getpid());

			/*close both */
			close(p1[0]);
			close(p1[1]);

			/*now write in other pipe*/
			wr = write(p2[1], buf, 1);

			if(wr != 1)
			{
				printf("child process's write on pipe 2 failed!\n");
			}
			/*then exit*/
			exit(0);
		}

	}
	else
	{
		printf("fork error!\n");
	}


	return 0;
}
