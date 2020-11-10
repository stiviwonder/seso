#include <stdio.h>
#include <stdlib.h>
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
cpu_t cpu;
int main(int argc, char* argv[]){

    // Declare parameters
    float clock_f = 4;
    int timer_f = 10;
    int pgen_f = 5;
    int core_kop = 4;

    // Initialize cpu
    init_cpu(core_kop);

    sem_init(&sem_timer, 0, 0);
    sem_init(&sem_pgen, 0, 0);
    sem_init(&sem_scheduler, 0, 0);
    create_threads(clock_f, timer_f, pgen_f);
    sem_destroy(&sem_timer);
    sem_destroy(&sem_pgen);
    sem_destroy(&sem_scheduler);

    return 0;
}
