#include <stdio.h>
#include <semaphore.h>
#include "func.h"
#include "clock.h"
#include "timer.h"
#include "p_gen.h"
#include "scheduler.h"
#include "global.h"

int main(int argc, char* argv[]){

    sem_init(&sem_timer, 0, 0);
    sem_init(&sem_pgen, 0, 0);
    sem_init(&sem_scheduler, 0, 0);
    create_threads(2, 4, 5);
    sem_destroy(&sem_timer);
    sem_destroy(&sem_pgen);
    sem_destroy(&sem_scheduler);
    return 0;
}
