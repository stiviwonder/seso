#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "../include/global.h"
#include "../include/p_gen.h"
#include "../include/tree.h"

/*====== GLOBAL VARIABLES ======*/

sem_t sem_pgen;
node_t* root;
volatile node_t* leftmost;
pthread_mutex_t lock;
volatile int num_process;

/*====== FUNCTION IMPLEMENTATIONS ======*/

void* process_gen(void *f_pgen){
    srand(time(0));

    int p_tick = *(int*) f_pgen;    // Maiztasunaren parametroa jaso

    // Hasieratze prozesua sortu zuhaitza hasieratzeko
    process_t p;

    long pid = rand();
    int vruntime = rand() % 250; // aleatorio el 250
    int time = vruntime + ((rand()%10)-5);

    p.pid = pid;
    p.vruntime = vruntime;
    p.time = time;
    p.exec_time = 0;


    root = new_node(p);
    leftmost = root;
    num_process = 0;

    while(1){

	// Erlojuarekin sinkronizazio semaforoa
        sem_wait(&sem_pgen);

	// Erloju tick-ak kontatu
        p_tick--;
        if (p_tick == 0){
	    
	    // Prozesua sortu
            create_process();
	    num_process++;

	    DEBUG_WRITE("[PGEN] process created, num_process = %d\n", num_process);

	    // Tick-ak kontatzeko tick pribatua berbiarazi
            p_tick = *(int*) f_pgen;
        }
    }
}

void create_process(){

    process_t p;

    long pid = rand();			    // ID aleatoria sortu
    int vruntime = rand() % 250 + 1;	    // virtual runtime aleatorioa sortu 
    int time = vruntime + ((rand()%10)-5);  // Exekuzio denbora sortu, vruntime-en inguruan

    // Prozesua hasieratu
    p.pid = pid;
    p.vruntime = vruntime;
    p.time = time;
    p.exec_time = 0;

    // Zuhaitzan sartu
    pthread_mutex_lock(&lock);
    insert(root, p);
    pthread_mutex_unlock(&lock);
}
