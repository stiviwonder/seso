#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "../include/global.h"
#include "../include/loader.h"
#include "../include/tree.h"

/*====== GLOBAL VARIABLES ======*/

sem_t sem_pgen;
node_t* root;
volatile node_t* leftmost;
pthread_mutex_t lock;
volatile int num_process;

/*====== FUNCTION IMPLEMENTATIONS ======*/

process_t create_process(){

    process_t p;
    mm_t mm;

    mm.code = 0x0;
    mm.data = 0x0;
    mm.pgb = 0x0;
    long pid = rand();			    // ID aleatoria sortu
    int vruntime = rand() % 250 + 1;	    // virtual runtime aleatorioa sortu 
    int time = vruntime + ((rand()%10)-5);  // Exekuzio denbora sortu, vruntime-en inguruan

    // Prozesua hasieratu
    p.pid = pid;
    p.vruntime = vruntime;
    p.time = time;
    p.mem_man = mm;

    return p;
}

void* loader(void *f_pgen){
    srand(time(0));

    int p_tick = *(int*) f_pgen;    // Maiztasunaren parametroa jaso

    // Hasieratze prozesua sortu zuhaitza hasieratzeko
    process_t p;


    p = create_process();
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
            p = create_process();

	    // Zuhaitzan sartu
	    pthread_mutex_lock(&lock);
	    insert(root, p);
	    pthread_mutex_unlock(&lock);

	    num_process++;

	    DEBUG_WRITE("[PGEN] process created, num_process = %d\n", num_process);

	    // Tick-ak kontatzeko tick pribatua berbiarazi
            p_tick = *(int*) f_pgen;
        }
    }
}

