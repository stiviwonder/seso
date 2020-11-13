#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include "../include/global.h"

/*====== GLOBAL VARIABLES ======*/

sem_t sem_timer;
sem_t sem_scheduler;

/*====== FUNCTION IMPLEMENTATIONS ======*/

void* timer(void *f_timer){
    int p_tick = *(int*) f_timer;     // Maiztasunaren parametroa jaso

    while(1){

	// Erlojuarekin sinkronizazio semaforoa
        sem_wait(&sem_timer);
	
	// Erloju tick-ak kontatu
        p_tick--;

        if (p_tick == 0){

	    // Scheduler-a sinkronizatzeko semaforoa
            sem_post(&sem_scheduler);

	    // Tick-ak kontatzeko tick pribatua berbiarazi
            p_tick = *(int*) f_timer;
        }
    }
}
