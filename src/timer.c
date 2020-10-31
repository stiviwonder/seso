#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include "global.h"

sem_t sem_timer;

void* timer(void *f_timer){
    int p_tick = *(int*) f_timer;
    while(1){
        sem_wait(&sem_timer);
        p_tick--;
        if (p_tick == 0){
            printf("[TIMER] es la hora del scheduler :) !!\n");
            sem_post(&sem_scheduler);
            p_tick = *(int*) f_timer;
        }
    }
}
