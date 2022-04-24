#ifndef __HTTP_REQUEST_H__
#define __HTTP_REQUEST_H__

#include "http_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct http_request_t
{
    const char     *url;
    size_t          method;       //默认使用GET
    http_version_t  version;      //默认使用HTTP/1.1
    http_list_t     header;       //键值对
    const char     *username;
    const char     *password;
    const void     *body;
    const char     *body_file;      //和body同时使用时，这项的配置是不生效的。
    size_t          body_len;
} http_request_t;

void http_request_init(http_request_t *request);
void http_request_free(http_request_t *request);

int http_request_set_url(http_request_t *client, const char *url);
int http_request_set_method(http_request_t *client, int method);
int http_request_set_version(http_request_t *client, int version);
int http_request_set_authinfo(http_request_t *client, const char *username, const char *password);
//默认拥有Host: <host>，Connection: closed；设置了Body后自动拥有：Content-Length: <body_len>，Content-Type: text/plain
int http_request_set_add_header(http_request_t *client, const http_header_t *header);
int http_request_set_delete_header(http_request_t *client, const char *key);
int http_request_set_body(http_request_t *client, const void *body, size_t body_len);
int http_request_set_body_file(http_request_t *client, const char *body_file, size_t body_len);

#ifdef __cplusplus
}
#endif

#endif
