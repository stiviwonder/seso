#include <semaphore.h>

volatile extern int tick;
extern sem_t sem_timer;
extern sem_t sem_pgen;
extern sem_t sem_scheduler;
extern struct process_q{
    long pid;
};
extern struct process_q* p_queue;

