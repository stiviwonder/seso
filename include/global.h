#include <semaphore.h>

//====== STRUCT DEFINITIONS ======\\

typedef struct process{
    long pid;
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
    int th_kop;
    //pthread_t th;
    queue_t queue;
};

typedef struct cpu{
    struct core* core;
}cpu_t;


typedef struct node{
    int vruntime;
    struct process process;
    struct node* dadi;
    struct node* right;
    struct node* left;
    
}node_t;

//====== GLOBAL VARIABLES ======\\

extern int tick; //esta no creo que haga falta global

extern sem_t sem_timer;
extern sem_t sem_pgen;
extern sem_t sem_scheduler;

extern pthread_mutex_t lock;

extern node_t* root;
extern volatile node_t* leftmost;

extern cpu_t cpu;
