/*
 * Names: Preet Jain / Devam Punitbhai Patel
 * NSID: pvj636 / dns682*
 * Student NUmber: 11270494 / 11316715
 */
#include "kernel/types.h"
#include "kernel/stat.h"
#include <time.h>
#include"user/user.h"
int mutex;
lock_id id;
int empty;
int full;
int buffer[10];
void producer(void)
{
	int random_number=0;
	while(1){
		if(mtx_lock(id)){
			printf("Cannot Aquire mutex\n");

		}else{

			/*Check for the Empty buffer*/
			if(empty == 0){
				/*Release the lock if no buffer available*/
				mtx_unlock(id);
				printf("No empty buffer, yielding CPU\n");
				thread_yield();
				continue;
			}
			else{
				/*Entering CS*/
				printf("Mutex Acquired by Producer\n");
				printf("Produced Item :%d\n",random_number );
				buffer[full] = random_number;
				random_number++;	
				full++;
				empty--;
				mtx_unlock(id);
				
			}
		}
	}
}
void consumer(void){
	while(1){
		if(mtx_lock(id)){
			printf("Cannot Aquire mutex\n");
			
		}
		else{
			/*get mutex*/
			if(full <= 0){
				/*If there is no filled buffer realease the mutex and continue*/
				mtx_unlock(id);
				printf("No filled buffer, yielding CPU\n");

				thread_yield();
				continue;
			}
			else{
				printf(" Consumer yielding CPU in CS\n");
				thread_yield();
				printf("Mutex Acquired by Consumer\n");
				printf("Consumed Item :%d\n",buffer[full -1] );
				full--;
				empty++;
				mtx_unlock(id);
			}
		}
	}
}
void mainpc(){
	id = mtx_create(mutex);
	empty = 10;
	full = 0;
	thread_init();
	thread_create(producer);
	printf("Producer Started\n");
	thread_create(consumer);
	printf("Consumer Started\n");

	thread_schedule();
	exit(0);
}
