#ifndef __HTTP_CONFIG_H__
#define __HTTP_CONFIG_H__

#include "http_platform.h"
#include "http_network.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum http_mode_t
{
    HTTP_MODE_ASYNC,
    HTTP_MODE_SYNC,
} http_mode_t;

typedef struct http_config_t
{
    const http_network_t *network;
    http_mode_t           mode;         //同步标志。默认使用异步。
    size_t                chunk_size;        //块大小。用于异步操作时，描述希望一次读取的字节数。
    char                 *chunk_buffer;
    const char           *save_file;    //应答存放文件。用于同步模式下，描述应答存放到文件。
} http_config_t;

static inline void http_config_init(http_config_t *config)
{
    http_memset(config, 0, sizeof(http_config_t));
}

static inline void http_config_free(http_config_t *config)
{

}

static inline void http_config_network(http_config_t *config, const http_network_t *network)
{
    config->network = network;
}

//块大小。用于异步操作时，描述希望一次读取的字节数。
static inline int http_config_chunk_size(http_config_t *config, size_t chunk_size)
{
    config->chunk_size = chunk_size;
}

static inline int http_config_sync(http_config_t *config)
{
    config->mode = HTTP_MODE_SYNC;
}

static inline int http_config_async(http_config_t *config)
{
    config->mode = HTTP_MODE_ASYNC;
}

static inline int http_config_save_file(http_config_t *config, const char *save_file)
{
    config->save_file = save_file;
}

#ifdef __cplusplus
}
#endif

#endif
