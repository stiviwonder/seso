#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "global.h"

void process_gen(void *f_pgen){
    printf("soi el p generatorl !!\n");
    int i = 0;
    int p_tick = (int) f_pgen;

    p_queue.data = malloc(300*sizeof(struct process_q));
    p_queue.size = 0;

    while(1){
        sem_wait(&sem_pgen);
        srand(time(0));
        p_tick--;
        if (p_tick == 0){
            create_process();
            printf("[PGEN] el pruses ha sido creado >:( || ");
            p_tick = (int) f_pgen;
            i++;
        }
    }
}

void create_process(){

    struct process p;

    //srand(time(0));
    long pid = rand();
    p.pid = pid;

    memcpy(&p_queue.data[p_queue.size++], &p, sizeof(struct process));
    //pid = fork();

    // p_queue[q_pos] = (long) pid;

}
