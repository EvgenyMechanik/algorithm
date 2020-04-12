#ifndef _DEQ_H
#define _DEQ_H

#include <list.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define DECLARE_DEQ(type) \
	typedef struct { \
		listhead head; \
		type item; \
	} type##_deq; \
	void type##_deq_init(type##_deq* deq) \
	{ \
		INIT_LIST_HEAD(deq->head); \
	} \
	bool type##_deq_remove_head(type##_deq* deq, type* val) \
	{ \
		listhead* v; \
		if(deq->head.next == &deq->head) \
			return false; \
		v = list_remove_head(&deq->head); \
		type##_deq* i = container_of(v, type##_deq, head); \
		*val = i->item; \
		free(i); \
		return true; \
	} \
	bool type##_deq_remove_tail(type##_deq* deq, type* val) \
	{ \
		listhead* v; \
		if(deq->head.next == &deq->head) \
			return false; \
		v = list_remove_tail(&deq->head); \
		type##_deq* i = container_of(v, type##_deq, head); \
		*val = i->item; \
		free(i); \
		return true; \
	} \
	bool type##_deq_insert_tail(type##_deq* deq, const type* val) \
	{ \
		type##_deq* n = (type##_deq*)malloc(sizeof(type##_deq)); \
		if(!n) \
			return false; \
		n->item = *val; \
		INIT_LIST_HEAD(n->head); \
		list_add_tail(&deq->head, &n->head); \
		return true; \
	} \
	bool type##_deq_insert_head(type##_deq* deq, const type* val) \
	{ \
		type##_deq* n = (type##_deq*)malloc(sizeof(type##_deq)); \
		if(!n) \
			return false; \
		n->item = *val; \
		INIT_LIST_HEAD(n->head); \
		list_add_head(&deq->head, &n->head); \
		return true; \
	} \
	bool type##_deq_is_empty(type##_deq* deq) \
	{ \
		deq->head.next == &deq->head; \
	} \
	void type##_deq_clear(type##_deq* deq) \
	{ \
		type##_deq* d; \
		listhead *x, *s; \
		list_for_each_safe(deq->head, x, s) { \
			d = container_of(x, type##_deq, head); \
			free(d); \
		} \
	}

#endif /* _DEQ_H */