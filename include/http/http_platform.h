#ifndef __HTTP_PLATFORM_H__
#define __HTTP_PLATFORM_H__

// 提供对不同平台的适配能力

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define http_memset     memset
#define http_memcpy     memcpy
#define http_strdup     strdup
#define http_strcasecmp strcasecmp
#define http_strcspn    strcspn
#define http_snprintf   snprintf
#define http_vsnprintf  vsnprintf
#define http_remove     remove
#define http_malloc     malloc
#define http_free       free
#define http_va_list    va_list
#define http_va_start   va_start
#define http_va_end     va_end

#endif
