#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

int empty(struct queue_t *q) { return (q->size == 0); }

void enqueue(struct queue_t *q, struct pcb_t *proc) {
  /* TODO: put a new process to queue [q] */
  if (q->size == MAX_QUEUE_SIZE)
    return;
  q->proc[q->size++] = proc;
}

struct pcb_t *dequeue(struct queue_t *q) {
  /* TODO: return a pcb whose priority is the highest
   * in the queue [q] and remember to remove it from q
   * */
  if (!q->size)
    return NULL;
  int maxPriority = q->proc[0]->priority;
  int index = 0;

  // Find highest priority
  for (int i = 0; i < q->size; i++) {
    if (q->proc[i]->priority > maxPriority) {
      maxPriority = q->proc[i]->priority;
      index = i;
    }
  }
  struct pcb_t *proc = q->proc[index];

  // Shift element to delete and reduce size
  for (int i = index; i < q->size - 1; i++) {
    // 1 2 3 4 5
    q->proc[i] = q->proc[i + 1];
  }
  q->size--;

  return proc;
}
