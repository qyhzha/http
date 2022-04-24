#include "http.h"
#include "http_debug.h"

void __http_debug(http_client_t *client, const char *file, int line, int level, const char *format, ...)
{
    if (client == NULL || client->debug.level < level || client->debug.debug == NULL)
        return;

    char buffer[HTTP_DEBUG_MAX_LENGTH + 1];
    http_va_list ap;

    http_va_start(ap, format);
    http_vsnprintf(buffer, sizeof(buffer), format, ap);
    http_va_end(ap);

    client->debug.debug(client->debug.argv, file, line, buffer);
}