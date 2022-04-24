#ifndef __HTTP_URL_H__
#define __HTTP_URL_H__

// 提供对URL的解析能力

#ifdef __cplusplus
extern "C" {
#endif

typedef struct http_url_t
{
    char *scheme;
    char *host;
    char *port;
    char *path;
} http_url_t;

http_url_t *http_url_create(const char *s);
void http_url_destroy(http_url_t *url);

#ifdef __cplusplus
}
#endif

#endif
