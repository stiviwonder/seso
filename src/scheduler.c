#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../include/global.h"
#include "../include/tree.h"

/*====== GLOBAL VARIABLES ======*/

sem_t sem_scheduler;
volatile node_t* leftmost;
node_t* root;
process_t run_p;
pthread_mutex_t lock;
volatile int num_process;

/*====== FUNCTION IMPLEMENTATIONS ======*/

void* scheduler(void *tid){

    // Core-etatik iteratzeko aldagaiak
    int i = 0;
    int last_i_core = 0;

    while(1){
	
	// Timer-arekin sinkronizazio semaforoa
        sem_wait(&sem_scheduler);
	DEBUG_WRITE("[SCHEDULER] scheduling ...\n");

	if (num_process >= 1){

	    // Core guztitik iteratzen du behin, core askatu bat aurkitu arte
	    while(cpu.core[i].executing == 1 && i < last_i_core){
		i = (i+1) % cpu.core_kop;
	    }

	    if (cpu.core[i].executing == 0){

		// Exekutatu behar den prozesua gorde
		run_p = leftmost->process;

		pthread_mutex_lock(&lock);

		// Prozesua zuhaitzetik ezabatu
		root = delete(root, leftmost->process.vruntime);
		leftmost = find_minimum(root);
		num_process--;
		
		DEBUG_WRITE("[SCHEDULER] num_process = %d\n", num_process);

		// Core-an prozesua exekutatzen jarri
		cpu.core[i].execution = run_p;
		cpu.core[i].executing = 1;
		DEBUG_WRITE("[SCHEDULER] core%d: execution time: %d\n", cpu.core[i].id, cpu.core[i].exec_time);
		pthread_mutex_unlock(&lock);

		// Hurrengo iterazioan uneko coreraino bilatzeko
		last_i_core = i;
		i = (i+1) % cpu.core_kop;
	    }
	}
    }
}
