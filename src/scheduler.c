#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../include/global.h"
#include "../include/tree.h"

sem_t sem_scheduler;
volatile node_t* leftmost;
node_t* root;

process_t run_p;

pthread_mutex_t lock;

void* scheduler(void *tid){
    int i = 0;
    int last_core = 0;
    while(1){
        sem_wait(&sem_scheduler);
        printf("\n[SCHEDULER] Scheduleando :)\n");
	
	// busca uno libre y si no hay adios muy buenas
	while(cpu.core[i].executing == 1 && i < last_core){
	    i = (i+1) % cpu.core_kop;
	}

	if (cpu.core[i].executing == 0){

	    run_p = leftmost->process;

	    pthread_mutex_lock(&lock);
	    root = delete(root, leftmost->process.vruntime);
	    leftmost = find_minimum(root);

	    cpu.core[i].execution = run_p;
	    cpu.core[i].executing = 1;
	    pthread_mutex_unlock(&lock);

	    last_core = i;
	    i = (i+1) % cpu.core_kop;

	}

    }
}
