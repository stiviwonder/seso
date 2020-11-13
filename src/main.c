#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include "../include/func.h"
#include "../include/clock.h"
#include "../include/timer.h"
#include "../include/p_gen.h"
#include "../include/scheduler.h"
#include "../include/global.h"
#include "../include/tree.h"

node_t* root;
volatile node_t* leftmost;
cpu_t cpu;
int main(int argc, char* argv[]){

    // Declare parameters
    float clock_f;
    int timer_f;
    int pgen_f;
    int core_kop;

    printf("\n");
    printf(" $$$$$$$\\  $$$$$$\\   $$$$$$$\\  $$$$$$\\\n");  
    printf("$$  _____|$$  __$$\\ $$  _____|$$  __$$\\\n");
    printf(" \\$$$$$$\\ $$$$$$$$ |\\$$$$$$\\  $$ /  $$ |\n");
    printf("  \\____$$\\$$   ____| \\____$$\\ $$ |  $$ |\n");
    printf("$$$$$$$  |\\$$$$$$$\\ $$$$$$$  |\\$$$$$$  |\n");
    printf("\\_______/  \\_______|\\_______/  \\______/\n");
    printf("\n");

    // Ask user for parameters
    printf("=================================================\n");
    printf("\nSelect clock rate (MHz): ");
    scanf("%f", &clock_f);
    printf("Select scheduler action rate (clock ticks): ");
    scanf("%d", &timer_f);
    printf("Select process generation rate (clock ticks): ");
    scanf("%d", &pgen_f);
    printf("Select number of cores: ");
    scanf("%d", &core_kop);

    // Initialize cpu
    printf("\n-------------------------------------------------\n");
    init_cpu(core_kop);
    printf("-------------------------------------------------\n");

//    printf("=================================================\n");
//    for (i=0; i<cpu.core_kop; i++)
//	printf("core%d initialized\n",cpu.core[i].id);
//    printf("=================================================\n");

    sem_init(&sem_timer, 0, 0);
    sem_init(&sem_pgen, 0, 0);
    sem_init(&sem_scheduler, 0, 0);
    create_threads(clock_f, timer_f, pgen_f);
    sem_destroy(&sem_timer);
    sem_destroy(&sem_pgen);
    sem_destroy(&sem_scheduler);

    return 0;
}
