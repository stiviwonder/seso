#include <semaphore.h>

extern int tick;
extern sem_t sem_timer;
extern sem_t sem_pgen;
extern sem_t sem_scheduler;
extern struct process{
    long pid;
};
struct process_q{
    struct process* data;
    short size;
};

extern struct process_q p_queue;

