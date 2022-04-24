#ifndef __HTTP_NETWORK_H__
#define __HTTP_NETWORK_H__

// 提供网络层的数据收发能力

#include "http_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct http_network_t
{
    void *argv;
    // int (*connect)(void *argv, const char *host, const char *port);
    // int (*disconnect)(void *argv);
    int (*read)(void *argv, void *buf, size_t nbyte);
    int (*write)(void *argv, const void *buf, size_t nbyte);
} http_network_t;

#ifdef HTTP_NET_ENABLE

typedef struct net_network_t
{
    int fd;
    http_network_t network;
} net_network_t;

int net_connect(void *arg, const char *scheme, const char *host, const char *port);
int net_disconnect(void *arg);
int net_read(void *arg, void *buf, size_t nbytes);
int net_write(void *arg, const void *buf, size_t nbytes);

#endif

#ifdef __cplusplus
}
#endif

#endif
