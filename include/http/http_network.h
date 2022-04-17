#ifndef __HTTP_NETWORK_H__
#define __HTTP_NETWORK_H__

#include "http_types.h"
#include "http_platform.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct http_network_t
{
    int (*connect)(void *user_arg, const char *host, const char *port);
    int (*disconnect)(void *user_arg);
    int (*read)(void *user_arg, void *buf, size_t nbyte);
    int (*write)(void *user_arg, const void *buf, size_t nbyte);
} http_network_t;

#ifdef USE_TCP

typedef struct tcp_network_t
{
    int fd;
    http_network_t network;
} tcp_network_t;

int tcp_connect(void *arg, const char *host, const char *port);
int tcp_disconnect(void *arg);
int tcp_read(void *arg, void *buf, size_t nbytes);
int tcp_write(void *arg, const void *buf, size_t nbytes);

static inline void http_network_init_by_tcp(tcp_network_t *network)
{
    network->fd = -1;
    network->network.connect = tcp_connect;
    network->network.disconnect = tcp_disconnect;
    network->network.read = tcp_read;
    network->network.write = tcp_write;
}

#endif

#ifdef __cplusplus
}
#endif

#endif
