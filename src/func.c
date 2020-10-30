#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "func.h"
#include "clock.h"
#include "timer.h"
#include "p_gen.h"
#include "scheduler.h"
#include "global.h"

void create_threads(float f_clock, int f_timer, int f_pgen){
    int i, err;
    pthread_t *threads;
    threads = malloc(4*sizeof(pthread_t));
    
    err = pthread_create(&threads[0], NULL, erlojua, (void *)&f_clock);
    if (err){
        fprintf(stderr, "(ERR) Unable to create threads, %d\n", err);
        exit(-1);
    }

    err = pthread_create(&threads[1], NULL, timer, (void *)&f_timer); 
    if (err){
        fprintf(stderr, "(ERR) Unable to create threads, %d\n", err);
        exit(-1);
    }

    err = pthread_create(&threads[2], NULL, process_gen, (void *)&f_pgen); 
    if (err){
        fprintf(stderr, "(ERR) Unable to create threads, %d\n", err);
        exit(-1);
    }

    i=3;
    err = pthread_create(&threads[3], NULL, scheduler, (void*)&i); 
    if (err){
        fprintf(stderr, "(ERR) Unable to create threads, %d\n", err);
        exit(-1);
    }

    for(i=0; i<4; i++)
        pthread_join(threads[i], NULL);
}
