#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include "../include/global.h"
#include "../include/tree.h"
#include "../include/func.h"

/*====== GLOBAL VARIABLES ======*/
volatile int num_process;
sem_t sem_timer;
sem_t sem_pgen;
sem_t sem_scheduler;
struct cpu cpu;
int* mem_fisikoa;
volatile int mem_addr;
volatile int mem_p;

node_t* root;

/*====== FUNCTION IMPLEMENTATIONS ======*/

void execute(struct cpu cpu, int t){
    int i;

    int *command = malloc(5*sizeof(int));
    int data;
    int start; //program start address

    // Core guztiak begiratzen ditu 
    for (i=0; i<cpu.core_kop; i++){

	// Uneko core-a zerbait exekutatzen ari bada bere prozesuaren egoera eguneratzen du
	if (cpu.core[i].executing == 1){

	    // proces the command for execution
	    command = read_op(mem_fisikoa[cpu.core[i].pc]);
	    start = mem_fisikoa[cpu.core[i].execution.mem_man.pgb];
	    data = command[4];

	    // Core-aren prozesua amaitu badu QUANTUM-a agortu gabe 
	    if (command[0] == 15 && cpu.core[i].exec_time < QUANTUM){
		pthread_mutex_lock(&lock);
		
		// Core-a askatzen du
		cpu.core[i].executing = 0; 
		cpu.core[i].exec_time = 0;	
		free_the_mem(cpu.core[i].ptbr, cpu.core[i].execution.size);
		pthread_mutex_unlock(&lock);

		DEBUG_WRITE("\033[1;31m");   // color red
		DEBUG_WRITE("[CLOCK] Process finished\n");
		DEBUG_WRITE("\033[0m");
	    }

	    // Core-aren prozesua QUANTUM-en denbora agortzen bada
	    else if (cpu.core[i].exec_time >= QUANTUM){
		pthread_mutex_lock(&lock);
		
		// "Lehentasuna" jaitsi eta core-ko exekuzio denbora berbiarazi
		cpu.core[i].execution.vruntime += 10;	
		cpu.core[i].exec_time = 0;	

		// Prozesua zuhaitzan berriro sartzen da
		insert(root, cpu.core[i].execution);
		num_process++;
		
		// Core-a askatzen du
		cpu.core[i].executing = 0;
		pthread_mutex_unlock(&lock);

		DEBUG_WRITE("\033[1;31m");   // color red
		DEBUG_WRITE("[CLOCK] QUANTUM finished\n");
		DEBUG_WRITE("\033[0m");
	    }
	    
	    // Exekuzio denborak eguneratzen dira
	    else{
		switch (command[0]){
		    case 0: //ld
			if (cpu.core[i].execution.time >= LD){
			    cpu.core[i].pc += 4;
			    cpu.core[i].execution.time = 0;

			    DEBUG_WRITE("\033[1;31m");   // color red
			    DEBUG_WRITE("[CLOCK]CORE%d => ld r%d, %08x =>  %d\n",cpu.core[i].id, command[1], data, cpu.core[i].ir[command[1]]);
			    DEBUG_WRITE("\033[0m");
			}
			else{
			    cpu.core[i].ir[command[1]] = mem_fisikoa[mmu(start, data)]; // Ri <= xxxx
			    cpu.core[i].execution.time ++;
			}
			break;
		    case 1: //st
			if (cpu.core[i].execution.time >= ST){
			    cpu.core[i].pc += 4;
			    cpu.core[i].execution.time = 0;

			    DEBUG_WRITE("\033[1;31m");   // color red
			    DEBUG_WRITE("[CLOCK]CORE%d => st r%d, %08x =>  %d\n",cpu.core[i].id, command[1], data, cpu.core[i].ir[command[1]]);
			    DEBUG_WRITE("\033[0m");
			}
			else{
			    mem_fisikoa[mmu(start, data)] = cpu.core[i].ir[command[1]]; // Ri => xxxx
			    cpu.core[i].execution.time ++;
			}
			break;
		    case 2: //add
			if (cpu.core[i].execution.time >= ADD){
			    cpu.core[i].pc += 4;
			    cpu.core[i].execution.time = 0;

			    DEBUG_WRITE("\033[1;31m");   // color red
			    DEBUG_WRITE("[CLOCK]CORE%d => add r%d, r%d, r%d => %d = %d + %d\n", cpu.core[i].id, command[1], command[2], command[3], cpu.core[i].ir[command[1]], cpu.core[i].ir[command[2]], cpu.core[i].ir[command[3]]);
			    DEBUG_WRITE("\033[0m");
			}
			else{
			    cpu.core[i].ir[command[1]] = cpu.core[i].ir[command[2]] + cpu.core[i].ir[command[3]];
			    cpu.core[i].execution.time ++;
			}
			break;
		}
		cpu.core[i].exec_time += t;	 // core exec time in ms
	    }
	}
    }
}

void* erlojua(void *f_clock){
    int tick;
    float f = *((float*)f_clock);   // Erlojuaren maiztasuna jaso
    float t = 1.0/f;		    // Maiztasunaren arabera periodoa lortu
    float t_tick;		    // Exkuziorako datua

    t *= 1000000;		    // Periodoa microsegundura pasa
    t_tick = t/10000;		    // Periodoa milisegundutan lortu
    tick = 0;
    while(1){
	// Uncomment for printing the tick number
        //if(tick % 2 == 0)
        //    printf("[CLOCK] /_( ¬‿¬)_/ tick: %d\n", tick);
        //else
        //    printf("[CLOCK] \\_(¬‿¬ )_\\ tick: %d\n", tick);
	
        tick++;

	// Prozesuak exekutatu
	execute(cpu, (int)t_tick);

	// Periodoa itxioin beste hariei maiztasun egokiarekin mugitzeko
        usleep((int)t);

	// Timer-arekin eta Prozesu generatzailearekin sinkronizatu
        sem_post(&sem_timer);
        sem_post(&sem_pgen);
    }
}

