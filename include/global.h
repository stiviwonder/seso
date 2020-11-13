#include <semaphore.h>


/*====== STRUCT DEFINITIONS ======*/

typedef struct process{
    long pid;
    int vruntime;
    int time;
    int exec_time;
}process_t;


typedef struct queue{
    struct process* queue;
    int front;
    int rear;
    int size;
    int max_size;
}queue_t;

struct core{
    int id;
    process_t execution;
    int executing;
};

typedef struct cpu{
    struct core* core;
    int core_kop;
}cpu_t;


typedef struct node{
    struct process process;
    struct node* dadi;
    struct node* right;
    struct node* left;
    
}node_t;

/*====== GLOBAL VARIABLES ======*/

extern int tick; //esta no creo que haga falta global

extern sem_t sem_timer;
extern sem_t sem_pgen;
extern sem_t sem_scheduler;

extern pthread_mutex_t lock;

extern node_t* root;
extern volatile node_t* leftmost;

extern struct cpu cpu;

/*====== DEFINES ======*/
#define QUANTUM 50
