#include <stdio.h>
#include <stdlib.h>
#include "../include/global.h"
#include "../include/queue.h"

struct queue new_queue(int max_size){
    struct queue q;
    q.queue = malloc(max_size*sizeof(queue_t));
    q.front = -1;
    q.rear = -1;
    q.size = -1;
    q.max_size = max_size;
    
    return q;
}

void enqueue(struct queue q, struct process p){

    if (q.size < q.max_size){
	if (q.size < 0){
	    q.queue[0] = p;
	    q.front = q.rear = 0;
	    q.size = 1;
	}
	else if (q.rear == q.max_size-1){
	    q.queue[0] = p;
	    q.rear = 0;
	    q.size++;
	}
	else{
	    q.queue[q.rear+1] = p;
	    q.rear++;
	    q.size++;
	}
    }
    else
	printf("(ERR): queue full\n");
}

process_t dequeue(struct queue q){

    process_t p;
    if (q.size < 0)
	printf("(ERR): queue empty\n");
    else {
	p = q.queue[q.front];
	q.size--;
	q.front++;
    }
    return p;
}
