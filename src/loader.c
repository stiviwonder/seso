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

process_t create_process(int i){

    process_t p;
    mm_t mm;
    int bin, addr, op, v_addr;
    int reg1, reg2, reg3;
    //int* codium, *datum;

    long pid = rand();			    // ID aleatoria sortu
    int vruntime = rand() % 250 + 1;	    // virtual runtime aleatorioa sortu 
    int time = 0;

    char file[23];
    sprintf(file, "programak/prog%03d.elf", i);

    FILE* elf = fopen(file, "r");

    if (elf == NULL){
	fprintf(stderr, "[ERR] can't open file");
	exit(-1);
    }

    // ACUERDATE DE ESTEEE
    //printf("\n\n %s \n\n", file);
    // ACUERDATE DE ESTEEE

    char data[20];

    fscanf(elf, "%s %x", data, &mm.code);
    if (strncmp(data, ".text",5)){
	fprintf(stderr, "[ERR] .text missing");
	exit(-1);
    }

    fscanf(elf, "%s %x", data, &mm.data);
    if (strncmp(data, ".data",5)){
	fprintf(stderr, "[ERR] .data missing");
	exit(-1);
    }
    // codium = malloc(mm.data*sizeof(int));

    mem_fisikoa[mem_p] = mem_addr;
    mem_p++;

    addr = mm.code;
    mm.pgb = mem_addr;
    while (fscanf(elf, "%8x", &bin) != EOF){
	if (addr < mm.data){
	    // hacer array de los comandos para luego hacer en la ejecucion
	    op = (bin >> 28) & 0x0F;
	    reg1 = (bin >> 24) & 0x0F;
	    reg2 = (bin >> 20) & 0x0F;
	    reg3 = (bin >> 16) & 0x0F;
	    v_addr = bin & 0x00FFFFFF;
	    switch (op){
		case 0: //ld
		    //printf("[code] 0x%06x: [%08x] op: ld r%d, 0x%06x\n",addr,bin, reg1, v_addr);
		    time += LD;
		    break;
		case 1: //st
		    //printf("[code] 0x%06x: [%08x] op: st r%d, 0x%06x\n",addr,bin, reg1, v_addr);
		    time += ST;
		    break;
		case 2: //add
		    //printf("[code] 0x%06x: [%08x] op: add r%d, r%d, r%d\n",addr,bin, reg1, reg2, reg3);
		    time += ADD;
		    break;
		case 15: //exit
		    //printf("[code] 0x%06x: [%08x] op: exit\n",addr,bin);
		    time += EXIT;
		    break;
	    }
	}
	else{
	    //printf("[data] 0x%06x: [%08x] %d\n",addr,bin,bin);
	}
	mem_fisikoa[mem_addr] = bin;
	mem_addr += 4;
	addr += 4;
    }
    fclose(elf);

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
    int i = 0;

    // Hasieratze prozesua sortu zuhaitza hasieratzeko
    process_t p;


    p = create_process(i);
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
            p = create_process(i);

	    // Zuhaitzan sartu
	    pthread_mutex_lock(&lock);
	    insert(root, p);
	    pthread_mutex_unlock(&lock);

	    num_process++;

	    DEBUG_WRITE("[PGEN] process created, num_process = %d\n", num_process);

	    // Tick-ak kontatzeko tick pribatua berbiarazi
            p_tick = *(int*) f_pgen;
	    i = (i+1) % 999;
        }
    }
}

