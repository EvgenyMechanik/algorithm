#include <c/list.h>
#include<stdlib.h>

void list_add_head(listhead* head, listhead* node)
{
	node->next = head->next;
	node->prev = head;
	head->next->prev = node;
	head->next = node;
}

void list_add_tail(listhead* head, listhead* node)
{
	node->next = head;
	node->prev = head->prev;
	head->prev->next = node;
	head->prev = node;
}

listhead* list_remove_head(listhead* head)
{
	listhead* r = head->next;
	head->next = head->next->next;
	head->next->prev = head;
	r->prev = r->next = NULL;
	return r; 
}

listhead* list_remove_tail(listhead* head)
{
	listhead* r = head->prev;
	head->prev = head->prev->prev;
	head->prev->next = head;
	r->prev = r->next = NULL;
	return r; 
}
