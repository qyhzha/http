#ifndef __HTTP_TYPES_H__
#define __HTTP_TYPES_H__

// 提供HTTP基础数据结构

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "http_list.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum http_method_t
{
    HTTP_METHOD_GET,
    HTTP_METHOD_POST,
    HTTP_METHOD_DELETE,
    HTTP_METHOD_HEAD,
    HTTP_METHOD_PUT
} http_method_t;

typedef enum http_version_t
{
    HTTP_VERSION_1_0,
    HTTP_VERSION_1_1
} http_version_t;

typedef enum http_error_t
{
    HTTP_ERROR_OK,
    HTTP_ERROR_DNS_FAIL     = -0x01,
    HTTP_ERROR_SOCKET_FAIL  = -0x02,
    HTTP_ERROR_CONNECT_FAIL = -0x03,
    HTTP_ERROR_WANT_READ    = -0x10,
    HTTP_ERROR_WANT_WRITE   = -0x20,
} http_error_t;

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
