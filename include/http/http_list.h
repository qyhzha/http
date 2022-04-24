#ifndef __HTTP_LIST_H__
#define __HTTP_LIST_H__

// linux kernel list

#include "http_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct http_list_t
{
    struct http_list_t *prev;
    struct http_list_t *next;
} http_list_t;

static inline void http_list_init(http_list_t *list)
{
    list->prev = list;
    list->next = list;
}

// static inline void http_list_free(http_list_t *list)
// {
//     list->prev = NULL;
//     list->next = NULL;
// }

static inline bool http_list_is_empty(http_list_t *list)
{
    return (list->next == list);
}

static inline void __http_list_add(http_list_t *prev, http_list_t *next, http_list_t *node)
{
    prev->next = node;
    next->prev = node;
    node->prev = prev;
    node->next = next;
}

static inline void http_list_add(http_list_t *list, http_list_t *node)
{
    __http_list_add(list, list->next, node);
}

static inline void http_list_add_tail(http_list_t *list, http_list_t *node)
{
    __http_list_add(list->prev, list, node);
}

static inline void __http_list_del(http_list_t *prev, http_list_t *next)
{
    prev->next = next;
    next->prev = prev;
}

static inline void http_list_del(http_list_t *node)
{
    __http_list_del(node->prev, node->next);
}

static inline void http_list_del_init(http_list_t *node)
{
    http_list_del(node);

    node->next = NULL;
    node->prev = NULL;
}

static inline void http_list_replace(http_list_t *old, http_list_t *new)
{
    __http_list_add(old->prev, old->next, new);
}

static inline void http_list_replace_init(http_list_t *old, http_list_t *new)
{
    http_list_replace(old, new);

    old->next = NULL;
    old->prev = NULL;
}

static inline void http_list_move(http_list_t *list, http_list_t *node)
{
    http_list_del(node);
    http_list_add(list, node);
}

static inline void http_list_move_tail(http_list_t *list, http_list_t *node)
{
    http_list_del(node);
    http_list_add_tail(list, node);
}

#define offsetof(type, member) ((size_t)&((type *)0)->member)

#define http_list_entry(node, type, member) \
    ( { \
        const http_list_t *__mptr = (node); \
        (type *)((char *)__mptr - offsetof(type,member)); \
    } )

#define http_list_next_entry(node, type, member) \
    http_list_entry((node)->next, type, member)

#define http_list_prev_entry(node, type, member) \
    http_list_entry((node)->prev, type, member)

#define http_list_first_entry(list, type, member) \
    http_list_next_entry(list, type, member)

#define http_list_last_entry(list, type, member) \
    http_list_prev_entry(list, type, member)

#define http_list_for_each_entry(pos, list, type, member) \
    for (pos = http_list_first_entry(list, type, member); \
         &pos->member != (head); \
         pos = http_list_next_entry(pos->member, type, member))

#define http_list_for_each_entry_safe(pos, next, list, type, member) \
    for (pos = http_list_first_entry(list, type, member), \
         next = http_list_next_entry(pos->member, type, member); \
         &pos->member != (head); \
         pos = next, http_list_next_entry(pos->member, type, member))

#define http_list_for_each_entry_reverse(pos, list, type, member) \
    for (pos = http_list_last_entry(list, type, member); \
         &pos->member != (head); \
         pos = http_list_prev_entry(pos->member, type, member))

#define http_list_for_each_entry_reverse_safe(pos, next, list, type, member) \
    for (pos = http_list_last_entry(list, type, member), \
         next = http_list_prev_entry(pos->member, type, member); \
         &pos->member != (head); \
         pos = http_list_prev_entry(pos->member, type, member))

#ifdef __cplusplus
}
#endif

#endif
