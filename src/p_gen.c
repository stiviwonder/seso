#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "../include/global.h"
#include "../include/p_gen.h"
#include "../include/tree.h"

sem_t sem_pgen;
node_t* root;
volatile node_t* leftmost;
pthread_mutex_t lock;

void* process_gen(void *f_pgen){

    int p_tick = *(int*) f_pgen;

    // crear el primer proceso para iniciar el arbol
    process_t p;

    long pid = rand();
    int vruntime = rand() % 250; // aleatorio el 250

    p.pid = pid;
    p.vruntime = vruntime;


    root = new_node(p, NULL);
    leftmost = root;

    while(1){
        sem_wait(&sem_pgen);
        srand(time(0));
        p_tick--;
        if (p_tick == 0){
            create_process();
            //printf("[PGEN] ");
	    //print_tree(root);
	    //printf("\n");

   //         printf("[PGEN] leftmost: %d\n", leftmost->process.vruntime);
            p_tick = *(int*) f_pgen;


        }
    }
}

void create_process(){

    process_t p;

    long pid = rand();
    int vruntime = rand() % 250 + 1; // aleatorio el 250
    int time = vruntime + ((rand()%10)-5);

    p.pid = pid;
    p.vruntime = vruntime;
    p.time = time;
    p.exec_time = 0;


    pthread_mutex_lock(&lock);
    insert(root, p , root);
    pthread_mutex_unlock(&lock);



}
