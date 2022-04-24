#ifndef __HTTP_RESPONSE_H__
#define __HTTP_RESPONSE_H__

#include "http_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct http_response_t
{
    size_t          status_code;
    http_version_t  version;
    list_t          header;
    void           *body;
    char           *body_file;
    size_t          body_len;
} http_response_t;

void http_response_init(http_response_t *response);
void http_response_free(http_response_t *response);

//以下API应该在连接后调用
int http_response_get_status_code(http_response_t *client);
int http_response_get_version(http_response_t *client);
const char *http_response_get_header_by_key(http_response_t *client, const char *key);
int http_response_get_content_length(http_response_t *client);       //如果body是chunked块。API返回0。
const char *http_response_get_content_type(http_response_t *client);
int http_response_get_body(http_response_t *client, void *body, size_t body_len); //如果返回了0，表示数据已经读取结束

#ifdef __cplusplus
}
#endif

#endif
