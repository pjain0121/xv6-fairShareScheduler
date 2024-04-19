<h1>xv6 Fair Share Scheduler</h1>


<h2>Description</h2>
1. share = we are defining a share to be the tickets of cpu access a process 
	has and it is calculated based on my group's cpu share and number of
	childrens that I fork. A group is formed between a parent and all it's
	childrens.
	i.e. initially the initial process will have 100 shares then when it forks
		a children it's share becomes 
		myshare/(numberOfChildren(it forked) +1(for itself)) 
    Implementation of share:
		-> we are planning to keep track of our parent's share and number of 
		childrens parent has to calculate my shares.
        -> to do this we plan to store 5 variables: groupShare, 
		myShare, myChild, numCPURuns, calculatedShare.
        -> everytime a process forks in fork() we re-calculate p's (parent's)
		share and every child's myShare is just a pointer to it's parent's
		calculatedShare.
        -> the parent's calculatedShare is calculated based on 
		it's groupShare/it's total number of childrens+1.
        -> every new processes (or child's) groupShare is a pointer to p's 
		(parent's) myShare.
        -> every np has 0 childs initially.
        -> np's myShare is a pointer to it's parents calculatedShare.
		(Because in a parent child group each process will have same number of 
		shares which will be groupShare/number of group members and when a 
		parent forks it's count of childrens gets incremented and 
		the parent re calculates it's shares so each child's myShare which
		is a pointer to it's parent's calculatedShare gets automatically
		updated.)
        -> we plan to have a global variable int totalShares = 100;
		and the first user process in userinit's groupShare would point to it
		and for other processes groupShare would just be a pointer to parent's
		myShare which we will set in fork.
		-> there is one special case when a parent's calculated share becomes
		0 because of integer division, in this case we assign the parent 1 
		share.
        -> This way we would have shares for every process now we need to 
		decide how would we schedule them.

2. The basic idea is that every process keeps track of how many times it
	got scheduled and it can only get scheduled for number of shares it has
	times. And if every process runs for their respective number of shares 
	times we will reset every process's cpuTimes to 0 and start it again.


	-> I am planning to have 2 queues: "turnsLeft" with processes still having
		cpu runs left and "turnsOver" with processes that ran out of their CPUS
		i.e. they were scheduled for their shares number of times. 
	
	-> We are also having 1 list for free nodes which keeps track of nodes that
	have been freed or nodes of processes which exited and fork takes
	nodes from this list once nodeIndex becomes greater than or equal to
	NPROC.

	-> To run the scheduler on multiple CPUs we are using spinlocks and when 
	accessing our queues or freeList we first acquire the lock modify the 
	structure and release the lock. To avoid deadlocking we are maintaining
	an order to acquire and release the locks and every function acquires
	all the lock at once and release them at once and in the same order.

<br />
