#ifndef _STACK_H
#define _STACK_H

#include <list.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define DECLARE_STACK(type) \
	typedef struct { \
		listhead head; \
		type item; \
	} type##_stack; \
	void type##_stack_init(type##_stack* stack) \
	{ \
		INIT_LIST_HEAD(stack->head); \
	} \
	bool type##_stack_pop(type##_stack* stack, type* val) \
	{ \
		listhead* v; \
		if(stack->head.next == &stack->head) \
			return false; \
		v = list_remove_head(&stack->head); \
		type##_stack* i = container_of(v, type##_stack, head); \
		*val = i->item; \
		free(i); \
		return true; \
	} \
	bool type##_stack_push(type##_stack* stack, const type* val) \
	{ \
		type##_stack* n = (type##_stack*)malloc(sizeof(type##_stack)); \
		if(!n) \
			return false; \
		n->item = *val; \
		INIT_LIST_HEAD(n->head); \
		list_add_head(&stack->head, &n->head); \
		return true; \
	} \
	bool type##_stack_is_empty(type##_stack* stack) \
	{ \
		stack->head.next == &stack->head; \
	} \
	void type##_stack_clear(type##_stack* stack) \
	{ \
		type##_stack* d; \
		listhead *x, *s; \
		list_for_each_safe(stack->head, x, s) { \
			d = container_of(x, type##_stack, head); \
			free(d); \
		} \
	}

#endif /* _STACK_H */