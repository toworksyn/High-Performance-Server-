//
// Latest edit on 2019/2/28.
//

#ifndef EPOLL_H
#define EPOLL_H

#include <sys/epoll.h>
#include "http.h"
#include "threadpool.h"

#define MAXEVENTS 1024

int sy_epoll_create(int flags);
int sy_epoll_add(int epoll_fd, int fd, sy_http_request_t* request, int events);
int sy_epoll_mod(int epoll_fd, int fd, sy_http_request_t* request, int events);
int sy_epoll_del(int epoll_fd, int fd, sy_http_request_t* request, int events);
int sy_epoll_wait(int epoll_fd, struct epoll_event *events, int max_events, int timeout);
void sy_handle_events(int epoll_fd, int listen_fd, struct epoll_event* events,
                      int events_num, char* path, sy_threadpool_t* tp);

#endif
