/* Physical memory allocator, for user processes, */
/* kernel stacks, page-table pages, */
/* and pipe buffers. Allocates whole 4096-byte pages. */

#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "riscv.h"
#include "defs.h"
void freerange(void *pa_start, void *pa_end);

extern char end[]; /* first address after kernel. */
                   /* defined by kernel.ld. */

/* CMPT 332 GROUP XX Change, Fall 2023 */
struct refCounts{
	struct spinlock lock;
	int refs[(PHYSTOP - KERNBASE)/4096];
};
struct freePages{
	struct spinlock lock;
	uint64 freePages;
};
struct refCounts references;
struct freePages fp;
struct run {
  struct run *next;
};

struct {
  struct spinlock lock;
  struct run *freelist;
} kmem;

int incrementRef(void *pa){
/*	printf("%d", *(uint64 *)pa);*/
	int index = ((uint64)pa - KERNBASE)/PGSIZE;
	acquire(&references.lock);
	references.refs[index]++;
	release(&references.lock);


/*	printf("Index: %d for page : %d\n", index, *(uint64 *)pa);*/
	return 1;
}
int decrementRef(void *pa){
/*	printf("%d", *(uint64 *)pa);*/
	int index =( (uint64)pa - KERNBASE)/PGSIZE;
	acquire(&references.lock);
	references.refs[index]--;


	release(&references.lock);

/*	printf("Index: %d for page : %d\n", index, *(uint64 *)pa);*/
	return 1;
}
int getCount(void *pa){
	int value;
	int index = ( (uint64)pa - KERNBASE)/PGSIZE;
	acquire(&references.lock);
	value = references.refs[index];
	release(&references.lock);
	return value;
}

/* CMPT 332 GROUP XX Change, Fall 2023 */
void
kinit()
{
  initlock(&kmem.lock, "kmem");
	initlock(&fp.lock, "fp");
	initlock(&references.lock, "ref");
/*	memset(references.refs, 0, (PHYSTOP - KERNBASE)/4096);*/
	acquire(&fp.lock);
	fp.freePages = 0;
	release(&fp.lock);
  freerange(end, (void*)PHYSTOP);
/*	memset(references.refs, 0, (PHYSTOP - KERNBASE)/4096);*/
	printf("Kinit end \n");

}

void
freerange(void *pa_start, void *pa_end)
{
  char *p;
  p = (char*)PGROUNDUP((uint64)pa_start);
  for(; p + PGSIZE <= (char*)pa_end; p += PGSIZE){
/* CMPT 332 GROUP XX Change, Fall 2023 */   
		references.refs[((uint64)p - KERNBASE)/PGSIZE] = 0; 
		kfree(p);
	}
}
/* CMPT 332 GROUP XX Change, Fall 2023 */   
/* Free the page of physical memory pointed at by pa, */
/* which normally should have been returned by a */
/* call to kalloc().  (The exception is when */
/* initializing the allocator; see kinit above.) */
void
kfree(void *pa)
{
/*If reference count for pa is == 1 only than free th page otherwise just 
 * decreasee the counter */
/*	if (getCount(pa) == 1){*/
		

  	struct run *r;

  	if(((uint64)pa % PGSIZE) != 0 || (char*)pa < end || (uint64)pa >= PHYSTOP)
    	panic("kfree");

  	/* Fill with junk to catch dangling refs. */
  	memset(pa, 1, PGSIZE);
		if(getCount(pa) > 0){
			decrementRef(pa);
		}

  	r = (struct run*)pa;
		if(getCount(pa)<=0){
		acquire(&fp.lock);
		fp.freePages++;
		release(&fp.lock);
		/*printf("Freed Page: no. of pages:  %d\n" , fp.freePages );*/
  	acquire(&kmem.lock);
  	r->next = kmem.freelist;
  	kmem.freelist = r;
  	release(&kmem.lock);
	}
/*	else{
		decrementRef(pa);
	}*/
}

/* Allocate one 4096-byte page of physical memory. */
/* Returns a pointer that the kernel can use. */
/* Returns 0 if the memory cannot be allocated. */
void *
kalloc(void)
{
  struct run *r;

  acquire(&kmem.lock);
  r = kmem.freelist;
  if(r)
    kmem.freelist = r->next;
  release(&kmem.lock);
	acquire(&fp.lock);
	fp.freePages--;
	release(&fp.lock);
/*	printf("r %d", *r);*/
	incrementRef(r);
/*	printf("Allocated a  Page: no. of pages:  %d\n" , fp.freePages );*/

  if(r)
    memset((char*)r, 5, PGSIZE); /* fill with junk */
  return (void*)r;
}

uint64 getNumFreePages(void){
	return fp.freePages;
}

/* CMPT 332 GROUP XX Change, Fall 2023 */   
