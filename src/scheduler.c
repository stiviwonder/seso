#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "global.h"

void scheduler(void *tid){
    while(1){
        sem_wait(&sem_scheduler);
        printf("[SCHEDULER] Scheduleando :)\n");
    }
}
