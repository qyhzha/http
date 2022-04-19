#ifndef __HTTP_LIST_H__
#define __HTTP_LIST_H__

// linux kernel list

#include "http_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct list_t
{
    struct list_t *prev;
    struct list_t *next;
} list_t;

static inline void list_init(list_t *list)
{
    list->prev = list;
    list->next = list;
}

static inline void list_free(list_t *list)
{
    list->prev = NULL;
    list->next = NULL;
}

static inline int list_is_empty(list_t *list)
{
    return (list->next == list);
}

static inline void __list_add(list_t *prev, list_t *next, list_t *node)
{
    prev->next = node;
    next->prev = node;
    node->prev = prev;
    node->next = next;
}

static inline void list_add(list_t *list, list_t *node)
{
    __list_add(list, list->next, node);
}

static inline void list_add_tail(list_t *list, list_t *node)
{
    __list_add(list->prev, list, node);
}

static inline void __list_del(list_t *prev, list_t *next)
{
    prev->next = next;
    next->prev = prev;
}

static inline void list_del(list_t *node)
{
    __list_del(node->prev, node->next);
}

static inline void list_del_init(list_t *node)
{
    list_del(node);

    node->next = NULL;
    node->prev = NULL;
}

static inline void list_replace(list_t *old, list_t *new)
{
    __list_add(old->prev, old->next, new);
}

static inline void list_replace_init(list_t *old, list_t *new)
{
    list_replace(old, new);

    old->next = NULL;
    old->prev = NULL;
}

static inline void list_move(list_t *list, list_t *node)
{
    list_del(node);
    list_add(list, node);
}

static inline void list_move_tail(list_t *list, list_t *node)
{
    list_del(node);
    list_add_tail(list, node);
}

#define offsetof(type, member) ((size_t)&((type *)0)->member)

#define list_entry(node, type, member) \
    ( { \
        const list_t *__mptr = (node); \
        (type *)((char *)__mptr - offsetof(type,member)); \
    } )

#define list_next_entry(node, type, member) \
    list_entry((node)->next, type, member)

#define list_prev_entry(node, type, member) \
    list_entry((node)->prev, type, member)

#define list_first_entry(list, type, member) \
    list_next_entry(list, type, member)

#define list_last_entry(list, type, member) \
    list_prev_entry(list, type, member)

#define list_for_each_entry(pos, list, type, member) \
    for (pos = list_first_entry(list, type, member); \
         &pos->member != (head); \
         pos = list_next_entry(pos->member, type, member))

#define list_for_each_entry_safe(pos, next, list, type, member) \
    for (pos = list_first_entry(list, type, member), \
         next = list_next_entry(pos->member, type, member); \
         &pos->member != (head); \
         pos = next, list_next_entry(pos->member, type, member))

#define list_for_each_entry_reverse(pos, list, type, member) \
    for (pos = list_last_entry(list, type, member); \
         &pos->member != (head); \
         pos = list_prev_entry(pos->member, type, member))

#define list_for_each_entry_reverse_safe(pos, next, list, type, member) \
    for (pos = list_last_entry(list, type, member), \
         next = list_prev_entry(pos->member, type, member); \
         &pos->member != (head); \
         pos = list_prev_entry(pos->member, type, member))

#ifdef __cplusplus
}
#endif

#endif
