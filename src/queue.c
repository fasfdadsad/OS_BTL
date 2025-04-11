#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int empty(struct queue_t * q) {
        if (q == NULL) return 1;
	return (q->size == 0);
}

void enqueue(struct queue_t * q, struct pcb_t * proc) {
        /* TODO: put a new process to queue [q] */
        if (q == NULL || proc == NULL) return;
        if (q->size < MAX_QUEUE_SIZE) {
                q->proc[q->size] = proc;
                q->size++;
        } else {
                fprintf(stderr, "Queue is full. Cannot enqueue process.\n");
        }
}

struct pcb_t * dequeue(struct queue_t * q) {
        /* TODO: return a pcb whose prioprity is the highest
         * in the queue [q] and remember to remove it from q
         * */
        if (empty(q)) return NULL;

        int highest_prio_ind = 0;
        for (int i = 1; i < q->size; i++) {
                if (q->proc[i]->prio < q->proc[highest_prio_ind]->prio) {  //The smaller the prio, the higher the priority
                        highest_prio_ind = i;
                }
        }
        // Retrieve the process with the highest priority
        struct pcb_t * highest_prio_proc = q->proc[highest_prio_ind];

        // Shift the remaining processes to fill the gap of the dequeued process
        for (int i = highest_prio_ind; i < q->size - 1; i++) {
                q->proc[i] = q->proc[i + 1];
        }

        q->size--;      // Decrease the size of the queue
	return highest_prio_proc;
}

