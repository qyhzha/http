#include "http_network.h"

#ifdef HTTP_NET_ENABLE

#include <errno.h>
#include <sys/netdb.h>
#include <sys/sockets.h>

int tcp_connect(void *arg, const char *host, const char *port, size_t proto)
{
    tcp_network_t *tcp = (tcp_network_t *)arg;
    struct addrinfo hints, *addr_list, *cur;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if (getaddrinfo(host, port, &hints, &addr_list) != 0)
        return -1;

    int ret = -1;
    for (cur = addr_list; cur != NULL; cur = cur->ai_next)
    {
        tcp->fd = socket(cur->ai_family, cur->ai_socktype, cur->ai_protocol);
        if (tcp->fd < 0)
        {
            continue;
        }

        if (connect(tcp->fd, cur->ai_addr, cur->ai_addrlen) == 0)
        {
            break;
        }

        close(tcp->fd);
        ret = -1;
    }

    freeaddrinfo(addr_list);

    return ret;
}

int tcp_disconnect(void *arg)
{
    tcp_network_t *tcp = (tcp_network_t *)arg;
    int ret = -1;

    if (tcp->fd > -1)
    {
        ret = close(tcp->fd);
    }

    return ret;
}

int tcp_read(void *arg, void *buf, size_t nbytes)
{
    tcp_network_t *tcp = (tcp_network_t *)arg;
    int ret = -1;

    if (tcp->fd > -1)
    {
        ret = readn(tcp->fd, buf, nbytes);
    }

    return ret;
}

int tcp_write(void *arg, const void *buf, size_t nbytes)
{
    tcp_network_t *tcp = (tcp_network_t *)arg;
    int ret = -1;

    if (tcp->fd > -1)
    {
        ret = writen(tcp->fd, buf, nbytes);
    }

    return ret;
}

#endif
