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
    while(1){
        sem_wait(&sem_scheduler);
        printf("[SCHEDULER] Scheduleando :)\n");
	
	//pthread_mutex_lock(&lock);
	if (cpu.core[i].executed == 1){
	    run_p = leftmost->process;
	    root = delete(root, leftmost->process.vruntime);
	    //pthread_mutex_unlock(&lock);
	    leftmost = find_minimum(root);

	    cpu.core[i].execution = run_p;
	}

	i += 1 % cpu.core_kop;

    }
}
