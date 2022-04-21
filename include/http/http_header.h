#ifndef __HTTP_HEADER_H__
#define __HTTP_HEADER_H__

#include "http_list.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct http_header_t
{
    const char *key;
    const char *value;
    http_list_t node;
} http_header_t;

#ifdef __cplusplus
}
#endif

#endif
