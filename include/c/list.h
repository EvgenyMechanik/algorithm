#ifndef _LIST_H
#define _LIST_H

#include <stddef.h>

typedef struct listhead {
	struct listhead* prev;
	struct listhead* next;
} listhead;

#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})

#define INIT_LIST_HEAD(head) (&head)->next = (&head)->prev = &head 
#define list_for_each(head, x) for(x = (&head)->next; x != &head; x = x->next)
#define list_for_each_safe(head, x, s) for(x = (&head)->next, s = x->next; x != &head; x = s, s = x->next)  

void list_add_tail(listhead* head, listhead* node);
void list_add_head(listhead* head, listhead* node);
listhead* list_remove_tail(listhead* head);
listhead* list_remove_head(listhead* head);

#endif /* _LIST_H */