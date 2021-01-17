#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../include/func.h"
#include "../include/clock.h"
#include "../include/timer.h"
#include "../include/loader.h"
#include "../include/scheduler.h"
#include "../include/global.h"

/*====== GLOBAL VARIABLES ======*/

pthread_mutex_t lock;
cpu_t cpu;

/*====== FUNCTION IMPLEMENTATIONS ======*/

void create_threads(float f_clock, int f_timer, int f_pgen){
    int i, err;
    pthread_t *threads;
    threads = malloc(4*sizeof(pthread_t));
    
    // Mutex-a hasieratu
    if (pthread_mutex_init(&lock, NULL) != 0){
        fprintf(stderr, "\n(ERR) Mutex init failed\n");
        exit(-1);
    }
    
    // Erloju haria hasieratu
    err = pthread_create(&threads[0], NULL, erlojua, (void *)&f_clock);
    if (err){
        fprintf(stderr, "(ERR) Unable to create threads, %d\n", err);
        exit(-1);
    }

    // Timer haria hasieratu
    err = pthread_create(&threads[1], NULL, timer, (void *)&f_timer); 
    if (err){
        fprintf(stderr, "(ERR) Unable to create threads, %d\n", err);
        exit(-1);
    }

    // Prozesu generatzaile haria hasieratu
    err = pthread_create(&threads[2], NULL, loader, (void *)&f_pgen); 
    if (err){
        fprintf(stderr, "(ERR) Unable to create threads, %d\n", err);
        exit(-1);
    }

    // Scheduler haria hasieratu
    i=3;
    err = pthread_create(&threads[3], NULL, scheduler, (void*)&i); 
    if (err){
        fprintf(stderr, "(ERR) Unable to create threads, %d\n", err);
        exit(-1);
    }

    pthread_mutex_destroy(&lock);
    for(i=0; i<4; i++)
        pthread_join(threads[i], NULL);
    free(threads);
}

void init_cpu(int core_kop){
    int i;

    // CPU hasieratu core kopuraren arabera
    cpu.core = malloc(core_kop*sizeof(struct core));
    cpu.core_kop = core_kop;

    printf("\n---------------------\n");
    printf("|        CPU        |\n");
    printf("---------------------\n");

    // Core guztiei ID bat jarri eta askatu egoeran ezarri
    for (i=0; i<core_kop;i++){
	cpu.core[i].id = i;
	cpu.core[i].executing = 0;
	cpu.core[i].exec_time = 0;
	printf("| core%d initialized |\n", cpu.core[i].id);
    }
    printf("---------------------\n");
}

int mmu(int faddr, int vaddr){

    return faddr + vaddr;
}

int* read_op(int bin){
    int *command = malloc(5*sizeof(int));

    command[0] = (bin >> 28) & 0x0F; // op
    command[1] = (bin >> 24) & 0x0F; // r1
    command[2] = (bin >> 20) & 0x0F; // r2
    command[3] = (bin >> 16) & 0x0F; // r3
    command[4] = bin & 0x00FFFFFF;   // vaddr

    //switch (command[0]){
    //    case 0: //ld
    //        printf(" [%08x] op: ld r%d, 0x%06x\n",bin, command[1], command[4]);
    //        break;
    //    case 1: //st
    //        printf(" [%08x] op: st r%d, 0x%06x\n",bin, command[1], command[4]);
    //        break;
    //    case 2: //add
    //        printf(" [%08x] op: add r%d, r%d, r%d\n",bin, command[1], command[2], command[3]);
    //        break;
    //    case 15: //exit
    //        printf(" [%08x] op: exit\n",bin);
    //        break;
    //}
    return command;
}

void free_the_mem(int addr, int size){

    struct free_spaces fs;
    fs.addr = addr;
    fs.size = size;
    mem_free[free_count] = fs;
    free_count++;
}

