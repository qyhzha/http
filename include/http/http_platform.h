#ifndef __HTTP_PLATFORM_H__
#define __HTTP_PLATFORM_H__

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define http_memset     memset
#define http_memcpy     memcpy
#define http_strdup     strdup
#define http_strcasecmp strcasecmp
#define http_strcspn    strcspn
#define http_snprintf   snprintf
#define http_vsnprintf  vsnprintf
#define http_remove     remove
#define http_malloc     malloc
#define http_calloc     calloc
#define http_free       free

#define USE_TCP

#endif
