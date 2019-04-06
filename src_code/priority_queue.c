//
// Latest edit on 2019/2/28.
//

#include <stdlib.h>
#include <string.h>
#include "priority_queue.h"

void exch(sy_pq_t *sy_pq, size_t i, size_t j){
    void *tmp = sy_pq->pq[i];
    sy_pq->pq[i] = sy_pq->pq[j];
    sy_pq->pq[j] = tmp;
}

void swim(sy_pq_t *sy_pq, size_t k){
    while (k > 1 && sy_pq->comp(sy_pq->pq[k], sy_pq->pq[k/2])){
        exch(sy_pq, k, k/2);
        k /= 2;
    }
}

int sink(sy_pq_t *sy_pq, size_t k){
    size_t j;
    size_t nalloc = sy_pq->nalloc;
    while((k << 1) <= nalloc){
        j = k << 1;
        if((j < nalloc) && (sy_pq->comp(sy_pq->pq[j+1], sy_pq->pq[j])))
            j++;

        if(!sy_pq->comp(sy_pq->pq[j], sy_pq->pq[k]))
            break;

        exch(sy_pq, j, k);
        k = j;
    }
    return k;
}

int sy_pq_sink(sy_pq_t *sy_pq, size_t i){
    return sink(sy_pq, i);
}

int sy_pq_init(sy_pq_t *sy_pq, sy_pq_comparator_pt comp, size_t size){
    // 为sy_pq_t节点的pq分配(void *)指针
    sy_pq->pq = (void **)malloc(sizeof(void *) * (size + 1));
    if (!sy_pq->pq)
        return -1;

    sy_pq->nalloc = 0;
    sy_pq->size = size + 1;
    sy_pq->comp = comp;
    return 0;
}

int sy_pq_is_empty(sy_pq_t *sy_pq){
    // 通过nalloc值款快速判断是否为空
    return (sy_pq->nalloc == 0) ? 1 : 0;
}

size_t sy_pq_size(sy_pq_t *sy_pq){
    // 获取优先队列大小
    return sy_pq->nalloc;
}

void *sy_pq_min(sy_pq_t *sy_pq){
    // 优先队列最小值直接返回第一个元素（指针）
    if (sy_pq_is_empty(sy_pq))
        return (void *)(-1);

    return sy_pq->pq[1];
}


int resize(sy_pq_t *sy_pq, size_t new_size){
    if(new_size <= sy_pq->nalloc)
        return -1;

    void **new_ptr = (void **)malloc(sizeof(void *) * new_size);
    if(!new_ptr)
        return -1;
    // 将原本nalloc + 1个元素值拷贝到new_ptr指向的位置
    memcpy(new_ptr, sy_pq->pq, sizeof(void *) * (sy_pq->nalloc + 1));
    // 释放旧元素
    free(sy_pq->pq);
    // 重新改写优先队列元素pq指针为new_ptr
    sy_pq->pq = new_ptr;
    sy_pq->size = new_size;
    return 0;
}

int sy_pq_delmin(sy_pq_t *sy_pq){
    if(sy_pq_is_empty(sy_pq))
        return 0;

    exch(sy_pq, 1, sy_pq->nalloc);
    --sy_pq->nalloc;
    sink(sy_pq, 1);
    if((sy_pq->nalloc > 0) && (sy_pq->nalloc <= (sy_pq->size - 1)/4)){
        if(resize(sy_pq, sy_pq->size / 2) < 0)
            return -1;
    }
    return 0;
}

int sy_pq_insert(sy_pq_t *sy_pq, void *item){
    if(sy_pq->nalloc + 1 == sy_pq->size){
        if(resize(sy_pq, sy_pq->size * 2) < 0){
            return -1;
        }
    }
    sy_pq->pq[++sy_pq->nalloc] = item;
    swim(sy_pq, sy_pq->nalloc);
    return 0;
}



