#ifndef _STACK_H
#define _STACK_H

#include <stdexcept>

template <class T, int N>
class AStack
{
private:
	T arr[N];
	int top;
	int cnt;
public:
	AStack() { top = cnt = 0; };
	bool push(const T& i)
	{
		if(top == N)
			return false;
		arr[top++] = i;
		cnt++;
		return true;
	}
	bool pop(T& i)
	{
		if(top == 0)
			return false;
		i = arr[--top];
		cnt--;
		return true;
	}
	inline bool empty() const { return top == 0; };
	inline bool full() const { return top == N; };
	inline int count() const { return cnt; };
};

template <class T>
class LStack
{
private:
	struct node {
		node* next;
		T item;
		node(const node* n, const T& i) { next = n; itme = i; };
	};
private:
	node* top;
	int cnt;
private:
	void clear()
	{
		node* d;
		while(top) {
			d = top;
			top = top->next;
			delete d;
		}
		cnt = 0;
	}
public:
	~LStack() { clear(); };
	LStack() { top = NULL; cnt = 0; };
	LStack(const LStack& ls)
	{
		top = NULL;
		*this = ls;
	}
	LStack& operator=(const LStack& ls)
	{
		node *n, *nn, *last;
		if(this == &ls)
			return *this;
		clear();
		n = ls.top;
		while(n) {
			nn = new node(NULL, n->item);
			if(!nn) {
				clear();
				throw std::runtime_error("Failed to allocate memory");
			}
			if(!top) {
				top = last = nn;
			} else {
				last->next = nn;
				last = nn;
			}
			n = n->next;
		}
		cnt = ls.cnt;
		return *this;
	}
	bool push(const T& i)
	{
		node* n = new node(top, i);
		if(!n)
			return false;
		top = n;
		cnt++:
		return true;
	}
	bool pop(T& i)
	{
		node* d;
		if(!top)
			return false;
		d = top;
		top = top->next;
		i = d->item;
		cnt--;
		delete d;
		return true;
	}
	inline bool empty() const { return top == NULL; };
	inline int count() const { return cnt; };
}

#endif /* _STACK_H