#include "list.h"

void list_add_tail(listhead** head, listhead* node)
{
	node->next = *head;
	(*head)->prev = node;
	*head = node;
}

void list_add_head(listhead** last, listhead* node)
{
	(*last)->next = node;
	node->prev = *last;
	*last = node;
}

node* list_remove_tail(listhead** head)
{
	node* r = *head;
	(*head)->next->prev = NULL;
	*head = (*head)->next;
	INIT_LIST_HEAD(r);
	return r;
}

node* list_remove_head(listhead** last)
{
	node* r = *last;
	(*last)->prev->next = NULL;
	*last = (*last)->prev;
	INIT_LIST_HEAD(r)
	return r;
}

void ciclic_list_add_tail(listhead* head, listhead* node)
{
	node->next = head->next;
	node->prev = head;
	head->next->prev = node;
	head->next = node;
}

void ciclic_list_add_head(listhead* head, listhead* node)
{
	node->next = head;
	node->prev = head->prev;
	head->prev->next = node;
	head->prev = node;
}

node* ciclic_list_remove_tail(listhead* head)
{
	node* r = head->next;
	head->next = head->next->next;
	head->next->prev = head;
	INIT_CICLIC_LIST_HEAD(r);
	return r; 
}

node* ciclic_list_remove_head(listhead* head)
{
	node* r = head->prev;
	head->prev = head->prev->prev;
	head->prev->next = head;
	INIT_CICLIC_LIST_HEAD(r);
	return r; 
}
