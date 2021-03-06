#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <limits.h>
#include "../include/global.h"
#include "../include/loader.h"
#include "../include/tree.h"

/*====== GLOBAL VARIABLES ======*/

sem_t sem_pgen;
node_t* root;
volatile node_t* leftmost;
pthread_mutex_t lock;
volatile int num_process;

int* mem_fisikoa;
volatile int mem_addr;
volatile int mem_p;
volatile int freespace;
volatile int free_count;
struct free_spaces *mem_free;

/*====== FUNCTION IMPLEMENTATIONS ======*/

int locate_space(int size){
    int i;
    int addr = -1;

    for (i=0; i<free_count; i++){
	if (mem_free[i].size >= size){
	    addr = mem_free[i].addr;
	    
	    // update the free space incase it was bigger
	    if (mem_free[i].size > size){
		mem_free[i].addr += size;
		mem_free[i].size -= size;
	    }
	}
    }
    return addr; // -1 => error
}

process_t create_process(char *filename){

    process_t p;
    p.size = 0;
    mm_t mm;
    int bin, i;

    long pid = rand();			    // ID aleatoria sortu
    int vruntime = rand() % 250 + 1;	    // virtual runtime aleatorioa sortu 

    char data[20];
    FILE *file = fopen(filename, "r");

    fscanf(file, "%s %x", data, &mm.code);
    if (strncmp(data, ".text",5)){
	fprintf(stderr, "[ERR] .text missing");
	exit(-1);
    }

    fscanf(file, "%s %x", data, &mm.data);
    if (strncmp(data, ".data",5)){
	fprintf(stderr, "[ERR] .data missing");
	exit(-1);
    }

    mem_fisikoa[mem_p] = mem_addr;
    mm.pgb = mem_p; //process page index
    mem_p++;

    p.pc = mem_addr; //first command address

    // load file in memory
    while (fscanf(file, "%8x", &bin) != EOF){
	mem_fisikoa[mem_addr] = bin;
	mem_addr += 4;
	p.size++;
    }
    fclose(file);

    // Prozesua hasieratu
    p.pid = pid;
    p.vruntime = vruntime;
    p.time = 0;
    p.mem_man = mm;
    p.size *= 4;
    //for (i=0; i<20;i++){p.ir[i] = 0;}
    memset(p.ir, 0, 20*sizeof(int));

    return p;
}

void* loader(void *f_pgen){
    srand(time(0));

    int p_tick = *(int*) f_pgen;    // Maiztasunaren parametroa jaso
    int i = 0;
    int p_size = 0;
    char line[16];

    char file[23];
    FILE *elf;
    // Hasieratze prozesua sortu zuhaitza hasieratzeko
    process_t p;


    //p = create_process();
    p.vruntime = INT_MAX;
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
	    sprintf(file, "programak/prog%03d.elf", i);
	    elf = fopen(file, "r");
	    if (elf == NULL){
		fprintf(stderr, "[ERR] can't open file");
		exit(-1);
	    }
	    while (fgets(line, sizeof(line), elf) != NULL){
		p_size++;
	    }
	    fclose(elf);
	    p_size = (p_size-2)*4;

	    mem_addr = locate_space(p_size);

	    if (mem_addr != -1){
		p = create_process(file);
		freespace -= p_size;

		// Zuhaitzan sartu
		pthread_mutex_lock(&lock);
		insert(root, p);
		pthread_mutex_unlock(&lock);

		num_process++;

		// color yellow
		DEBUG_WRITE("\033[1;33m[LOADER] process created, num_process = %d\033[0m\n", num_process);


		i = (i+1) % 50;
		p_size = 0;
	    }
	    else{
		// color yellow
		DEBUG_WRITE("\033[1;33m[LOADER] ERR: process not created. Not enough space\033[0m\n");
	    }
	    // Tick-ak kontatzeko tick pribatua berbiarazi
            p_tick = *(int*) f_pgen;
        }
    }
}

