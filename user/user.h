struct stat;

/* system calls */
int fork(void);
int exit(int) __attribute__((noreturn));
int wait(int*);
int pipe(int*);
int write(int, const void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(const char*, char**);
int open(const char*, int);
int mknod(const char*, short, short);
int unlink(const char*);
int fstat(int fd, struct stat*);
int link(const char*, const char*);
int mkdir(const char*);
int chdir(const char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
int trace(int mask );
int getNumFreePages(void);
/* ulib.c */
int stat(const char*, struct stat*);
char* strcpy(char*, const char*);
void *memmove(void*, const void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void fprintf(int, const char*, ...);
void printf(const char*, ...);
char* gets(char*, int max);
uint strlen(const char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);
int memcmp(const void *, const void *, uint);
void *memcpy(void *, const void *, uint);
/*CMPT 332 GROUP 15 Change, Fall 2023*/
/*For mutex*/
typedef int lock_id;

lock_id mtx_create(int locked);
int mtx_lock(lock_id id);
int mtx_unlock(lock_id id);

/*Thread Functions so that other files can use it*/
void thread_init(void);
void thread_schedule(void);
void thread_create(void (*func)());
void thread_yield(void);


/*for random number generator Assignment 3*/
int rand(void);

int Square(int);
/*CMPT 332 GROUP 15 Change, Fall 2023*/

