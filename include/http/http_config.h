#ifndef __HTTP_CONFIG_H__
#define __HTTP_CONFIG_H__

#include "http_platform.h"
#include "http_network.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum http_mode_t
{
    HTTP_MODE_NO_CACHE,
    HTTP_MODE_CACHE,
    HTTP_MODE_FLASH,
} http_mode_t;

typedef struct http_config_t
{
    http_network_t  network;
    http_mode_t     mode;         //同步标志。默认使用异步。
    void           *cache;        // if mode == HTTP_MODE_CACHE, this is useful.
    size_t          cache_size;
    const char     *save_file;     // if mode == HTTP_MODE_FLASH, this is useful.
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
static inline int http_config_mode(http_config_t *config, http_mode_t mode)
{
    config->mode = mode;
}

static inline int http_config_cache(http_config_t *config, void *cache, int cache_size)
{
    config->cache = cache;
    config->cache_size = cache_size;
}

static inline int http_config_save_file(http_config_t *config, const char *save_file)
{
    config->save_file = save_file;
}

#ifdef __cplusplus
}
#endif

#endif
