#include "http_url.h"

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

http_url_t *http_url_create(const char *s)
{
    if (s == NULL)
        return NULL;

    http_url_t *url = (http_url_t *)http_malloc(sizeof(http_url_t));

    if (url == NULL)
        return NULL;

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

void http_url_destroy(http_url_t *url)
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
