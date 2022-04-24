#ifndef __HTTP_H__
#define __HTTP_H__

#include "http_config.h"
#include "http_debug.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HTTP_DEFAULT_BUFFER_SIZE (1024)

typedef enum http_mode_t
{
    HTTP_MODE_NO_CACHE,
    HTTP_MODE_CACHE,
    HTTP_MODE_FLASH,
} http_mode_t;

typedef enum http_operation_t
{
    HTTP_OPERATION_INIT,
    HTTP_OPERATION_FREE,
    HTTP_OPERATION_CONFIG,
    HTTP_OPERATION_REQUEST,
    HTTP_OPERATION_RESPONSE,
} http_operation_t;

typedef struct http_config_t
{
    http_network_t  network;
    http_mode_t     mode;         //同步标志。默认使用异步。
    void           *cache;        // if mode == HTTP_MODE_CACHE, this is useful.
    size_t          cache_size;
    const char     *save_file;     // if mode == HTTP_MODE_FLASH, this is useful.
} http_config_t;

typedef struct http_client_t
{
    http_opreations_t    operation;
    http_debug_t         debug;
    http_network_t       network;
} http_client_t;

void http_client_init(http_client_t *client);
void http_client_free(http_client_t *client);

int http_client_request(http_client_t *client, const http_request_t *req);
int http_client_response(http_client_t *client, http_response_t *response);

#ifdef __cplusplus
}
#endif

#endif
