#include "http.h"

typedef struct http_url_t
{
    char *scheme;
    char *host;
    char *port;
    char *path;
} http_url_t;

static int http_url_match_scheme(http_url_t *url, const char *s)
{
    int ret = -1;

    url->scheme = NULL;

    if (http_strcasecmp(s, "http://") == 0)
    {
        url->scheme = http_strdup("http");
        ret = 7;
    }
    else if (http_strcasecmp(s, "https://") == 0)
    {
        url->scheme = http_strdup("https");
        ret = 8;
    }

    if (url->scheme == NULL)
        return -1;

    return ret;
}

static int http_url_match_host(http_url_t *url, const char *s)
{
    int ret = http_strcspn(s, ":/");

    url->host = NULL;

    if (ret > 0)
    {
        // ipv6
        if (s[0] == '[' && s[ret - 1] == ']')
        {
            url->host = (char *)http_malloc(ret - 1);
            if (url->host != NULL)
            {
                http_memcpy(url->host, s + 1, ret - 2);
                url->host[ret - 2] = 0;
            }
        }
        else
        {
            url->host = (char *)http_malloc(ret + 1);
            if (url->host != NULL)
            {
                http_memcpy(url->host, s, ret);
                url->host[ret] = 0;
            }
        }
    }

    if (url->host == NULL)
        return -1;

    return ret;
}

static int http_url_match_port(http_url_t *url, const char *s)
{
    int ret = http_strcspn(s, "/");

    url->port = NULL;

    if (ret == 0)
    {
        if (http_strcasecmp(url->scheme, "http://") == 0)
        {
            url->port = http_strdup("80");
        }
        else if (http_strcasecmp(url->scheme, "https://") == 0)
        {
            url->port = http_strdup("443");
        }
    }
    else if (ret > 1 && s[0] == ':')
    {
        url->port = (char *)http_malloc(ret);
        if (url->port != NULL)
        {
            http_memcpy(url->port, s + 1, ret - 1);
            url->port[ret - 1] = 0;
        }
    }

    if (url->port == NULL)
        return -1;

    return ret;
}

static int http_url_match_path(http_url_t *url, const char *s)
{
    int ret = strlen(s);

    if (ret == 0)
    {
        url->path = http_strdup("/");
    }
    else
    {
        url->path = http_strdup(s);
    }

    if (url->path == NULL)
        return -1;

    return ret;
}

static http_url_t *http_url_create(const char *s)
{
    if (s == NULL)
        return -1;

    http_url_t *url = (http_url_t *)http_malloc(sizeof(http_url_t));

    if (url == NULL)
        return -1;

    int pos = 0;
    if (((pos += http_url_match_scheme(url, s + pos)) < 0)
     || ((pos += http_url_match_host(url, s + pos)) < 0)
     || ((pos += http_url_match_port(url, s + pos)) < 0)
     || ((pos += http_url_match_path(url, s + pos)) < 0))
    {
        goto error_exit;
    }

    return url;

error_exit:
    if (url->scheme != NULL)
        http_free(url->scheme);

    if (url->host != NULL)
        http_free(url->host);

    if (url->port != NULL)
        http_free(url->port);

    if (url->path != NULL)
        http_free(url->path);

    return NULL;
}

static void http_url_destroy(http_url_t *url)
{
    if (url->scheme != NULL)
        http_free(url->scheme);

    if (url->host != NULL)
        http_free(url->host);

    if (url->port != NULL)
        http_free(url->port);

    if (url->path != NULL)
        http_free(url->path);

    http_free(url);
}

static void http_printf(http_client_t *client, const char *file, int line, int level, const char *format, ...)
{
    if (client->debug.level < level || client->debug.debug == NULL)
        return;

    va_list ap;
    char buffer[HTTP_LOG_MAX_LENGTH + 1];

    va_start(ap, format);
    http_vsnprintf(buffer, sizeof(buffer), format, ap);
    va_end(ap);

    client->debug.debug(client->debug.argv, file, line, buffer);
}

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

int http_client_set_url(http_client_t *client, const char *url)
{
    if (client == NULL || url == NULL)
        return -1;

    http_url_t *http_url = http_url_create(url);
    if (http_url == NULL)
        return -1;


}

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
