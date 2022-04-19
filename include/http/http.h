#ifndef __HTTP_H__
#define __HTTP_H__

#include "http_list.h"
#include "http_config.h"
#include "http_debug.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HTTP_DEFAULT_BUFFER_SIZE (1024)
#define HTTP_LOG_MAX_LENGTH      (512)

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

typedef struct http_header_t
{
    const char *key;
    const char *value;
    list_t node;
} http_header_t;

typedef struct http_request_t
{
    const char     *url;
    size_t          method;       //默认使用GET
    http_version_t  version;      //默认使用HTTP/1.1
    list_t          header;        //键值对
    const char     *username;
    const char     *password;
    const void     *body;
    const char     *body_file;      //和body同时使用时，这项的配置是不生效的。
    size_t          body_len;
} http_request_t;

typedef struct http_response_t
{
    size_t          status_code;
    http_version_t  version;
    list_t          header;
    void           *body;
    char           *body_file;
    size_t          body_len;
} http_response_t;

typedef struct http_client_t
{
    http_debug_t         debug;
    const http_config_t *config;
    http_request_t       request;
    http_response_t      response;
} http_client_t;

void http_client_init(http_client_t *client);
void http_client_free(http_client_t *client);

int http_client_set_url(http_client_t *client, const char *url);
int http_client_set_method(http_client_t *client, int method);
int http_client_set_version(http_client_t *client, int version);
int http_client_set_authinfo(http_client_t *client, const char *username, const char *password);
//默认拥有Host: <host>，Connection: closed；设置了Body后自动拥有：Content-Length: <body_len>，Content-Type: text/plain
int http_client_set_add_header(http_client_t *client, const http_header_t *header);
int http_client_set_delete_header(http_client_t *client, const char *key);
int http_client_set_body(http_client_t *client, const void *body, size_t body_len);
int http_client_set_body_file(http_client_t *client, const char *body_file, size_t body_len);

int http_client_connect(http_client_t *client, http_config_t *config);
int http_client_disconnect(http_client_t *client);

//以下API应该在连接后调用
int http_client_get_status_code(http_client_t *client);
int http_client_get_version(http_client_t *client);
int http_client_get_content_length(http_client_t *client);       //如果body是chunked块。API返回0。
const char *http_client_get_content_type(http_client_t *client);
const char *http_client_get_header_by_key(http_client_t *client, const char *key);
int http_client_get_body(http_client_t *client, void *body, size_t body_len); //如果返回了0，表示数据已经读取结束

#ifdef __cplusplus
}
#endif

#endif
