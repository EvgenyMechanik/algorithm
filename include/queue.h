#ifndef _QUEUE_H
#define _QUEUE_H

#include <list.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define DECLARE_QUEUE(type) \
	typedef struct { \
		listhead head; \
		type item; \
	} type##_queue; \
	void type##_queue_init(type##_queue* queue) \
	{ \
		INIT_LIST_HEAD(queue->head); \
	} \
	bool type##_queue_remove(type##_queue* queue, type* val) \
	{ \
		listhead* v; \
		if(queue->head.next == &queue->head) \
			return false; \
		v = list_remove_head(&queue->head); \
		type##_queue* i = container_of(v, type##_queue, head); \
		*val = i->item; \
		free(i); \
		return true; \
	} \
	bool type##_queue_insert(type##_queue* queue, const type* val) \
	{ \
		type##_queue* n = (type##_queue*)malloc(sizeof(type##_queue)); \
		if(!n) \
			return false; \
		n->item = *val; \
		INIT_LIST_HEAD(n->head); \
		list_add_tail(&queue->head, &n->head); \
		return true; \
	} \
	bool type##_queue_is_empty(type##_queue* queue) \
	{ \
		queue->head.next == &queue->head; \
	} \
	void type##_queue_clear(type##_queue* queue) \
	{ \
		type##_queue* d; \
		listhead *x, *s; \
		list_for_each_safe(queue->head, x, s) { \
			d = container_of(x, type##_queue, head); \
			free(d); \
		} \
	}

#endif /* _QUEUE_H */