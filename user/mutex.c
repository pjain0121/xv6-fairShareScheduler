/*
 * Names: Preet Jain / Devam Punitbhai Patel
 * NSID: pvj636 / dns682
 * Student Numbers: 11270494 / 11316715*/
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define MAXMUTEXS 200
typedef struct Mutex{
	int* lock;
	lock_id id;

}mutex;
mutex list[MAXMUTEXS];
int num_mutex;

lock_id mtx_create(int locked){
	/*Check */
	if(num_mutex < MAXMUTEXS){
		locked = 1;
		list[num_mutex].lock = &locked;
		list[num_mutex].id = num_mutex;
		num_mutex++;
		return list[num_mutex].id;
	}
	else{
		return -1;
	}
	
}

int mtx_lock(lock_id id){
	/*busy wait on mutex*/
	if(id > MAXMUTEXS){
		return 1;
	}
	else{
		while(*list[id].lock){
			/*if mutex locked , yield cpu to next thread*/
			printf("Mutex Yileding CPU Cause Lock not available \n");
			thread_yield();
		}
		*list[id].lock = 1;
		return 0;
	}
}

int mtx_unlock(lock_id id){
	if(id > MAXMUTEXS){
		return 1;
	}
	
	*list[id].lock = 0;
	return 0;
}
