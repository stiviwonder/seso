#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "../include/global.h"
#include "../include/p_gen.h"
#include "../include/tree.h"

process_q_t p_queue;
sem_t sem_pgen;
node_t* root;
volatile node_t* leftmost;
pthread_mutex_t lock;

void* process_gen(void *f_pgen){
    int p_tick = *(int*) f_pgen;

    // crear el primer proceso para iniciar el arbol
    process_t p;

    long pid = rand();
    p.pid = pid;

    int vruntime = rand() % 250; // aleatorio el 250

    root = new_node(vruntime, p, NULL);
    leftmost = root;

    while(1){
        sem_wait(&sem_pgen);
        srand(time(0));
        p_tick--;
        if (p_tick == 0){
            create_process();
            printf("[PGEN] ");
	    print_tree(root);
	    printf("\n");

            printf("[PGEN] leftmost: %d\n", leftmost->vruntime);
            p_tick = *(int*) f_pgen;

        }
    }
}

void create_process(){

    process_t p;

    long pid = rand();
    p.pid = pid;

    int vruntime = rand() % 250 + 1; // aleatorio el 250
    printf("[PGEN] new pruses: %d\n", vruntime);

//    pthread_mutex_lock(&lock);
    insert(root, vruntime, p , root);
//    pthread_mutex_unlock(&lock);



}
