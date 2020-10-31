#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "global.h"
#include "p_gen.h"
#include "tree.h"

process_q_t p_queue;
sem_t sem_pgen;
node_t* root;
volatile node_t* leftmost;

void* process_gen(void *f_pgen){
    int i = 0;
    int p_tick = *(int*) f_pgen;

    // crear el primer proceso para iniciar el arbol
    process_t p;

    long pid = rand();
    p.pid = pid;

    int vruntime = rand() % 250; // aleatorio el 250

    root = new_node(vruntime, p, NULL);
    leftmost = root;

//    p_queue.data = malloc(300*sizeof(struct process_q));
//    p_queue.size = 0;

    while(1){
        sem_wait(&sem_pgen);
        srand(time(0));
        p_tick--;
        if (p_tick == 0){
            create_process();
            printf("[PGEN] el pruses ha sido creado >:(\n");
            printf("[PGEN] ");
	    print_tree(root);
            printf("\n");
            printf("[PGEN] leftmost: %d\n", leftmost->vruntime);
            p_tick = *(int*) f_pgen;
            i++;
        }
    }
}

void create_process(){

    process_t p;

    long pid = rand();
    p.pid = pid;

    int vruntime = rand() % 250; // aleatorio el 250

    insert(root, vruntime, p , root);
    // memcpy(&p_queue.data[p_queue.size++], &p, sizeof(struct process));


}
