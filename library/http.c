#include "http.h"

void http_client_init(http_client_t *client)
{
    if (client == NULL)
        return;

    http_memset(client, 0, sizeof(http_client_t));

    client->request.method = HTTP_METHOD_GET;
    client->request.version = HTTP_VERSION_1_1;
    list_init(&client->request.header);
    list_init(&client->response.header);
    client->mode = HTTP_MODE_ASYNC;
}

void http_client_free(http_client_t *client)
{
    if (client == NULL)
        return;

    if (client->response.body != NULL)
    {
        http_free(client->response.body);
    }

    if (client->response.body_file != NULL)
    {
        http_remove(client->response.body_file);
    }
}

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
