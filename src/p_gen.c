#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "global.h"

void process_gen(void *f_pgen){
    printf("soi el p generatorl !!\n");
    int i = 0;
    int p_tick = (int) f_pgen;

    p_queue = malloc(300*sizeof(struct process_q));
    while(1){
        sem_wait(&sem_pgen);
        srand(time(0));
        p_tick--;
        if (p_tick == 0){
            create_process(p_queue[i]);
            printf("[PGEN] el pruses ha sido creado >:( || pid: %ld\n", p_queue[i].pid);
            p_tick = (int) f_pgen;
            i++;
        }
    }
}

void create_process(struct process_q elem){

    long pid = rand();
    elem.pid = pid;
    //pid = fork();

    // p_queue[q_pos] = (long) pid;

}
