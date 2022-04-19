#ifndef __HTTP_DEBUG_H__
#define __HTTP_DEBUG_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct http_debug_t
{
    int level;
    void *argv;
    void (*debug)(void *argv, const char *file, int line, const char *info);
} http_debug_t;

#define http_debug_log(level, fmt, ...) http_printf(client, __FILE__, __LINE__, level, fmt, ##__VA_ARGS__)

void http_printf(http_client_t *client, const char *file, int line, int level, const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif
