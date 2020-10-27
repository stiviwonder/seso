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

typedef struct cpu{
    int core;
    int thread;
}cpu_t;

extern process_q_t p_queue;

