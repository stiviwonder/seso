#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../include/global.h"
#include "../include/tree.h"

sem_t sem_scheduler;
volatile node_t* leftmost;
node_t* root;

volatile node_t* run_p;

pthread_mutex_t lock;

void* scheduler(void *tid){
    while(1){
        sem_wait(&sem_scheduler);
        printf("[SCHEDULER] Scheduleando :)\n");
	
	//pthread_mutex_lock(&lock);
	run_p = leftmost;
	root = delete(root, leftmost->vruntime);
	//pthread_mutex_unlock(&lock);
	leftmost = find_minimum(root);



    }
}
