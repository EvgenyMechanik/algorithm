#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdexcept>

template <class T, int N>
class AQueue
{
private:
	T arr[N];
	int first;
	int last;
	int cnt;
public:
	AQueue() { first = last = cnt = 0; };
	bool insert(const T& i)
	{
		if(cnt == N)
			return false;
		arr[(last++)%N] = i;
		cnt++;
		return true;
	}
	bool remove(T& i)
	{
		if(cnt == 0)
			return false;
		i = arr[(first++)%N];
		cnt--;
		return false;
	}
	inline bool empty() const { return cnt == 0; };
	inline bool full() const { return cnt == N; };
	inline int count() const { return cnt; };
};

template <class T>
class LQueue
{
private:
	struct node {
		node* next;
		T item;
		node(const node* n, const T& i) { next = n; itme = i; };
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
	~LQueue() { clear(); };
	LQueue() { first = last = NULL; cnt = 0; };
	LQueue(const LQueue& lq)
	{
		first = last = NULL;
		*this = ls;
	}
	LQueue& operator=(const LQueue& lq)
	{
		node *n;
		if(this == &lq)
			return *this;
		clear();
		n = ls.first;
		while(n) {
			if(!insert(n->item)) {
				clear();
				throw std::runtime_error("Failed to allocate memory");
			}
			n = n->next;
		}		
		return *this;
	}
	bool insert(const T& i)
	{
		node* n = new node(NULL, i);
		if(!n)
			return false;
		if(!first) {
			first = last = n;
		} else {
			last->n = n;
			last = n;
		}
		cnt++;
		return true;
	}
	bool remove(T& i)
	{
		node* d;
		if(!first)
			return false;
		d = first;
		first = first->next;
		if(!first)
			last = NULL;
		i = d->item;
		cnt--;
		delete d;
		return true;
	}
	inline bool empty() const { return first == NULL; };
	inline int count() const { return cnt; };
}

#endif /* _QUEUE_H */