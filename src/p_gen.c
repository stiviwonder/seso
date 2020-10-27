#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "global.h"

process_q_t p_queue;
sem_t sem_pgen;

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
            printf("[PGEN] el pruses ha sido creado >:( || pid: %ld\n", p_queue.data[i]);
            p_tick = (int) f_pgen;
            i++;
        }
    }
}

void create_process(){

    process_t p;

    //srand(time(0));
    long pid = rand();
    p.pid = pid;

    memcpy(&p_queue.data[p_queue.size++], &p, sizeof(struct process));
    //pid = fork();

    // p_queue[q_pos] = (long) pid;

}
