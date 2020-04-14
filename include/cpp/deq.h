#ifndef _DEQ_H
#define _DEQ_H

#include <stdexcept>


template <class T, int N>
class ADeq
{
private:
	T arr[N];
	int first;
	int last;
	int cnt;
public:
	ADeq() { first = last = cnt = 0; };
	bool insert_head(const T& i)
	{
		if(cnt == N)
			return false;
		arr[first] = i;
		first = (first > 0 ? first - 1 : N - 1);
		cnt++;
		return true;
	}
	bool insert_tail(const T& i)
	{
		if(cnt == N)
			return false;
		arr[(last++)%N] = i;
		cnt++;
		return true;
	}
	bool remove_head(T& i)
	{
		if(cnt == 0)
			return false;
		i = arr[(++first)%N];
		cnt--;
		return true;
	}
	bool remove_tail(T& i)
	{
		if(cnt == 0)
			return false;
		i = arr[(--last)%N];
		cnt--;
		return true;
	}
	inline bool empty() const { return cnt == 0; };
	inline bool full() const { return cnt == N; };
	inline int count() const { return cnt; };
};

template <class T>
class LDeq
{
private:
	struct node {
		node* prev;
		node* next;
		T item;
		node(const node* p, const node* n, const T& i) { prev = p; next = n; itme = i; };
	};
private:
	node* first;
	node* last;
	int cnt;
private:
	void clear()
	{
		node* d;
		while(first) {
			d = first;
			first = first->next;
			delete d;
		}
		cnt = 0;
		last = NULL;
	}
public:
	~LDeq() { clear(); };
	LDeq() { first = last = NULL; cnt = 0; };
	LDeq(const LQueue& lq)
	{
		first = last = NULL;
		*this = ls;
	}
	LDeq& operator=(const LDeq& lq)
	{
		node *n;
		if(this == &lq)
			return *this;
		clear();
		n = ls.first;
		while(n) {
			if(!insert_tail(n->item)) {
				clear();
				throw std::runtime_error("Failed to allocate memory");
			}
			n = n->next;
		}
		return *this;
	}
	bool insert_tail(const T& i)
	{
		node* n = new node(last, NULL, i);
		if(!n)
			return false;
		if(first) {
			first = last = n;
		} else {
			last->next = n;
			last = n;
		}
		cnt++:
		return true;
	}
	bool insert_head(const T& i)
	{
		node* n = new node(NULL, first, i);
		if(!n)
			return false;
		if(first) {
			first = last = n;
		} else {
			first->prev = n;
			first = n;
		}
		cnt++;
		return true;
	}
	bool remove_tail(T& i)
	{
		node* d;
		if(!last)
			return false;
		d = last;
		last = last->prev;
		if(last == NULL)
			first = NULL;
		else
			last->next = NULL;
		i = d->item;
		cnt--;
		delete d;
		return true;
	}
	bool remove_head(T& i)
	{
		node* d;
		if(!first)
			return false;
		d = first;
		first = first->next;
		if(!first)
			last = NULL;
		else
			first->prev = NULL;
		i = d->item;
		cnt--;
		delete d;
		return true;
	}
	inline bool empty() const { return first == NULL; };
	inline int count() const { return cnt; };
}

#endif /* _DEQ_H */
