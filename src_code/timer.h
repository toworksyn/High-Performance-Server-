//
// Latest edit on 2019/2/28.
//

#ifndef SY_TIMER_H
#define SY_TIMER_H

#include "priority_queue.h"
#include "http_request.h"

#define TIMEOUT_DEFAULT 500     /* ms */

// 函数指针，负责超时处理，sy_add_timer时指定处理函数
typedef int (*timer_handler_pt)(sy_http_request_t* request);

typedef struct sy_timer{
    size_t key;    // 标记超时时间
    int deleted;    // 标记是否被删除
    timer_handler_pt handler;    // 超时处理，add时指定
    sy_http_request_t* request;    // 指向对应的request请求
} sy_timer_t;

// sy_pq_t定义在"priority_queue.h"中，优先队列中节点
extern sy_pq_t sy_timer;
extern size_t sy_current_msec;

int sy_timer_init();
int sy_find_timer();
void sy_handle_expire_timers();
void sy_add_timer(sy_http_request_t* request, size_t timeout, timer_handler_pt handler);
void sy_del_timer(sy_http_request_t* request);
int timer_comp(void *ti, void *tj);

#endif