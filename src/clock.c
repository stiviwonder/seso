#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include "../include/global.h"
#include "../include/tree.h"

int tick;
sem_t sem_timer;
sem_t sem_pgen;
sem_t sem_scheduler;
struct cpu cpu;

node_t* root;


void execute(struct cpu cpu, int t){
    int i;

    for (i=0; i<cpu.core_kop; i++){

	if (cpu.core[i].executing == 1){
	    printf("[CLOCK] core%d: time left: %d\n", cpu.core[i].id, cpu.core[i].execution.time);
	    printf("[CLOCK] core%d: execution time: %d\n", cpu.core[i].id, cpu.core[i].execution.exec_time);

	    if (cpu.core[i].execution.time <= 0 && cpu.core[i].execution.exec_time < QUANTUM){
		pthread_mutex_lock(&lock);
		cpu.core[i].execution.vruntime += 10;
		insert(root, cpu.core[i].execution, root);
		cpu.core[i].executing = 0;
		pthread_mutex_unlock(&lock);
		printf("[CLOCK] Process finished\n");
	    }
	    else if (cpu.core[i].execution.exec_time >= QUANTUM){
		pthread_mutex_lock(&lock);
		cpu.core[i].executing = 0;
		pthread_mutex_unlock(&lock);
		printf("[CLOCK] QUANTUM finished\n");
	    }
	    else{
		cpu.core[i].execution.time -= t;
		cpu.core[i].execution.exec_time += t;
	    }
	}
    }
}

void* erlojua(void *f_clock){
    float f = *((float*)f_clock);
    float t = 1.0/f;
    float t_tick;

    t *= 1000000;
    t_tick = t/10000;
    tick = 0;
    while(1){
        //if(tick % 2 == 0)
        //    printf("[CLOCK] /_( ¬‿¬)_/ tick: %d\n", tick);
        //else
        //    printf("[CLOCK] \\_(¬‿¬ )_\\ tick: %d\n", tick);
        tick++;
	execute(cpu, (int)t_tick);
        usleep((int)t);
        sem_post(&sem_timer);
        sem_post(&sem_pgen);
    }
}

