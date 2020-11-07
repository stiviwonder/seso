#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../include/global.h"
#include "../include/tree.h"

sem_t sem_scheduler;
volatile node_t* leftmost;
node_t* root;
node_t* is_it;

node_t* pruses;

pthread_mutex_t lock;

void* scheduler(void *tid){
    while(1){
        sem_wait(&sem_scheduler);
        printf("[SCHEDULER] Scheduleando :)\n");
	
	//is_it = find_minimum(root);

        //printf("[SCHEDULER] BEFORE DELETE is it = %d :)\n", is_it->vruntime);
        //printf("[SCHEDULER] BEFORE DELETE leftmost = %d :)\n", leftmost->vruntime);


	//pthread_mutex_lock(&lock);
	//pruses = delete(root, leftmost->vruntime);
	//pthread_mutex_unlock(&lock);
//
        //printf("[SCHEDULER] BEFORE DELETE is it = %d :)\n", is_it->vruntime);
        //printf("[SCHEDULER] BEFORE DELETE leftmost = %d :)\n", leftmost->vruntime);


	//printf("\n");
	//printf("[SCHEDULER] ");
	//print_tree(root);
	//printf("\n");

    }
}
