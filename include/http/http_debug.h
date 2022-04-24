#ifndef __HTTP_DEBUG_H__
#define __HTTP_DEBUG_H__

// 提供基于日志的调试方法

#include "http_types.h"

#ifdef __cplusplus
extern "C" {
#endif

// 一次日志输出的最大长度
#define HTTP_DEBUG_MAX_LENGTH      (512)

typedef struct http_debug_t
{
    int level;
    void *argv;
    void (*debug)(void *argv, const char *file, int line, const char *info);
} http_debug_t;

#define http_error_log(fmt, ...) \
    __http_debug(client, __FILE__, __LINE__, 0, fmt, ##__VA_ARGS__)
#define http_debug_log(fmt, ...) \
    __http_debug(client, __FILE__, __LINE__, 1, fmt, ##__VA_ARGS__)
#define http_trace_log(fmt, ...) \
    __http_debug(client, __FILE__, __LINE__, 2, fmt, ##__VA_ARGS__)

void __http_debug(http_client_t *client, const char *file, size_t line, size_t level, const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif
