#include <semaphore.h>

volatile int tick;
sem_t sem_timer;
sem_t sem_pgen;
sem_t sem_scheduler;
struct process_q p_queue;
