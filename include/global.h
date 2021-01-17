#ifndef global_h
#define global_h
#include <semaphore.h>


/*====== STRUCT DEFINITIONS ======*/

typedef struct mm{
    int pgb;	// Orri taularen helbide fisikoa
    int code;	// Kodearen helbide birtuala
    int data;	// Datuen helbide birtuala
}mm_t;

typedef struct process{
    long pid;
    int vruntime;
    int time;
    int pc; // execution address
    int ir[20];
    struct mm mem_man;
    int size;
}process_t;

struct core{
    int id;
    process_t execution;
    int executing;
    int exec_time;

    int pc; // execution address
    int ir[20];
    int ptbr;
};

typedef struct cpu{
    struct core* core;
    int core_kop;
}cpu_t;

typedef struct node{
    struct process process;
    struct node* right;
    struct node* left;
}node_t;

struct free_spaces{
    int addr;
    int size;
};

/*====== GLOBAL VARIABLES ======*/

extern volatile int num_process;

extern sem_t sem_timer;
extern sem_t sem_pgen;
extern sem_t sem_scheduler;

extern pthread_mutex_t lock;

extern node_t* root;
extern volatile node_t* leftmost;

extern struct cpu cpu;

extern int* mem_fisikoa;
extern volatile int freespace;
extern volatile int mem_addr;
extern volatile int mem_p; //page addr

extern struct free_spaces *mem_free;
extern volatile int free_count;
/*====== DEFINES ======*/

#define QUANTUM 300

#define LD 7
#define ST 7
#define ADD 5
#define EXIT 3

#define MEM_SIZE 4194304 // 2^22

#ifdef DEBUG
    #define DEBUG_WRITE(...) printf(__VA_ARGS__)
#else
    #define DEBUG_WRITE(...)
#endif // DEBUG
#endif //global
