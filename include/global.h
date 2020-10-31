#include <semaphore.h>

extern int tick;
extern sem_t sem_timer;
extern sem_t sem_pgen;
extern sem_t sem_scheduler;

typedef struct process{
    long pid;
}process_t;

typedef struct process_q{
    struct process* data;
    short size;
}process_q_t;

struct core{
    int th_kop;
    pthread_t th;
};

typedef struct cpu{
    struct core* core;
}cpu_t;

extern process_q_t p_queue;

typedef struct node{
    int vruntime;
    struct process process;
    struct node* dadi;
    struct node* right;
    struct node* left;
    
}node_t;

extern node_t* root;
extern volatile node_t* leftmost;
