/*
 * Preet Jain
 * pvj636
 * 11270494
 *
 * Devam Punitbhai Patel
 * dns682
 * 11316715
 * */
/*
#include<partA1.h>
#include<stdio.h>
extern struct ThreadData* threadArray;
extern struct Parameters* params;
*/


#include "kernel/types.h"
#include "user/user.h"
int Square(int N)
{
    /*int threadID = getIndex();*/
	/* This loop checks whther current thread is present in the array if 
	 * it is than increment the counter by 1 in this way we account for
	 * all the recurring instances of sqaure and the same array will be 
	 * accessed by all the instamces of sqaure no count will be missed*/
	/*
    if(threadID == -1 ){
		printf("The threadID is not in threadArray");
	}
	else{
		threadArray[threadID].counter += 1;
	}
	*/
	
    /*for(i =0; i < params->numThreads;i++ ){
	if (threadArray[i].SystemId == threadID ){		
	    threadArray[i].counter += 1;
	}
    }*/

    if(N == 0) {
        return 0;
    }
    return (Square(N - 1) + N + N - 1);
}

int mainSq()
{
	return 0;
}
