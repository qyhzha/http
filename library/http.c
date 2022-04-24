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

int http_client_connect(http_client_t *client, http_config_t *config);
int http_client_disconnect(http_client_t *client);

//以下API应该在连接后调用
int http_client_get_status_code(http_client_t *client);
int http_client_get_version(http_client_t *client);
int http_client_get_content_length(http_client_t *client);       //如果body是chunked块。API返回0。
const char *http_client_get_content_type(http_client_t *client);
const char *http_client_get_header_by_key(http_client_t *client, const char *key);
int http_client_get_body(http_client_t *client, void *body, size_t body_len); //如果返回了0，表示数据已经读取结束
