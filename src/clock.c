#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include "global.h"

int tick;
sem_t sem_timer;
sem_t sem_pgen;
sem_t sem_scheduler;

void* erlojua(void *f_clock){
    float f = *((float*)f_clock);
    float t = 1.0/f;
    t *= 1000000;
    tick = 0;
    while(1){
//        if(tick % 2 == 0)
//            printf("[CLOCK] /_( ¬‿¬)_/ tick: %d\n", tick);
//        else
//            printf("[CLOCK] \\_(¬‿¬ )_\\ tick: %d\n", tick);
        tick++;
        usleep((int)t);
        sem_post(&sem_timer);
        sem_post(&sem_pgen);
    }
}
