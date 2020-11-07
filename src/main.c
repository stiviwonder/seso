#include <stdio.h>
#include <semaphore.h>
#include "../include/func.h"
#include "../include/clock.h"
#include "../include/timer.h"
#include "../include/p_gen.h"
#include "../include/scheduler.h"
#include "../include/global.h"
#include "../include/tree.h"

node_t* root;
volatile node_t* leftmost;

int main(int argc, char* argv[]){

    sem_init(&sem_timer, 0, 0);
    sem_init(&sem_pgen, 0, 0);
    sem_init(&sem_scheduler, 0, 0);
    create_threads(4, 20, 5);
    sem_destroy(&sem_timer);
    sem_destroy(&sem_pgen);
    sem_destroy(&sem_scheduler);

    return 0;
}
