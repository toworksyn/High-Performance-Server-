//
// Latest edit on 2019/2/28.
//

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdlib.h>

#define SY_PQ_DEFAULT_SIZE 10

typedef int (*sy_pq_comparator_pt)(void *pi, void *pj);

typedef struct priority_queue{
    void **pq;
    size_t nalloc;
    size_t size;
    sy_pq_comparator_pt comp;
}sy_pq_t;

int sy_pq_init(sy_pq_t *sy_pq, sy_pq_comparator_pt comp, size_t size);
int sy_pq_is_empty(sy_pq_t *sy_pq);
size_t sy_pq_size(sy_pq_t *sy_pq);
void *sy_pq_min(sy_pq_t *sy_pq);
int sy_pq_delmin(sy_pq_t *sy_pq);
int sy_pq_insert(sy_pq_t *sy_pq, void *item);
int sy_pq_sink(sy_pq_t *sy_pq, size_t i);

#endif 
