#ifndef _LIST_H
#define _LIST_H

typedef struct listhead {
	struct dlistnode* prev;
	struct dlistnode* next;
} listhead;

#define INIT_LIST_HEAD(x) x->next = x->prev = NULL
#define INIT_CICLIC_LIST_HEAD(x) x->next = x->prev = x

void list_add_tail(listhead* head, listhead* node);
void list_add_head(listhead* last, listhead* node);
node* list_remove_tail(listhead** head);
node* list_remove_head(listhead** last);

void ciclic_list_add_tail(listhead* head, listhead* node);
void ciclic_list_add_head(listhead* head, listhead* node);
node* ciclic_list_remove_tail(listhead* head);
node* ciclic_list_remove_head(listhead* head);

#endif /* _LIST_H */