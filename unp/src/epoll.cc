
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <iostream>

#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <strings.h>

using namespace std;

#define MAX_EVENTS  1024000

struct myevent_s
{
    int fd;
    void (*callback)(int fd, int events, void *arg);
    int events;
    void *arg;
    int status;
    char buff[128];
    int len;
    int s_offset;
    long last_active;
};

// set events
void EventSet(myevent_s *ev, int fd, void (*callback)(int, int, void*), void *arg)
{
    ev->fd = fd;
    ev->callback = callback;
    ev->arg = arg;
    ev->status = 0;
    bzero(ev->buff, sizeof(ev->buff));
    ev->s_offset = 0;
    ev->len = 0;
    ev->last_active = time(NULL);
}

// add/mod an event to epoll
void EventAdd(int epollfd, int events, myevent_s *ev)
{
    struct epoll_event epv = {0, {0}};
    int op;
    epv.data.ptr = ev;
    epv.events = ev->events = events;

    if (ev->status == 1) 
    {
        op = EPOLL_CTL_MOD;
    }
    else
    {
        op = EPOLL_CTL_ADD;
        ev->status = 1;
    }

    if (epoll_ctl(epollfd, op, ev->fd, &epv) < 0)
        printf("Event Add failed[fd=%d], events[%d]\n", ev->fd, events);
    else
        printf("Event Add succeess[fd=%d], op=%d, events[%d]\n", ev->fd, op, events);
}

void EvnetDel(int epoll_fd, myevent_s *ev)
{
    struct epoll_event epv = {0, {0}};
    if (ev->status != 1) 
        return;
    epv.data.ptr = ev;
    ev->status = 0;
    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, ev->fd, &epv);
}

int g_epoll_fd;
myevent_s g_events[MAX_EVENTS + 1];

void recvdata(int fd, int events, void *arg);
void senddata(int fd, int events, void *arg);
void accept_connection(int fd, int events, void *arg)
{
    struct sockaddr_in sin;
    int nfd, i;
    socklen_t len = sizeof(struct sockaddr_in);
    if ((nfd = accept(fd, (struct sockaddr *)&sin, &len)) == -1)
    {
        if (errno != EAGAIN && errno != EINTR)
        {
            printf("%s: accept, %d", __func__, errno);
            return;
        }
    }
    do
    {
        for (i = 0; i < MAX_EVENTS; i++)
        {
            if (g_events[i].status == 0)
                break;
            if (i == MAX_EVENTS)
            {
                printf("%s:max connection limit[%d].", __func__, MAX_EVENTS);
                break;
            }
        }
            
        // set nonblocking
        int ret = 0;
        if ((ret = fcntl(fd, F_SETFL, O_NONBLOCK)) < 0)
        {
            printf("%s: fcntl nonblocking failed:%d", __func__, ret);
            break;
        }

        // add a read event for receive data
        EventSet(&g_events[i], nfd, recvdata, &g_events[i]);
        EventAdd(g_epoll_fd, EPOLLIN, &g_events[i]);

    } while (0);
    printf("new conn[%s:%d][time:%ld], pos[%d]\n", inet_ntoa(sin.sin_addr), ntohs(sin.sin_port), g_events[i].last_active, i);
}

