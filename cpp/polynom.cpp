#include <cpp/polynom.h>

#include <iostream>
using namespace std;

APolynom::APolynom(const Ratio& v, int ss)
{		
	s = ss;
	arr = new Ratio[s + 1];
	if(!arr)
		throw std::runtime_error("Failed to allocate memory");	
	for(int i = 0; i < s; i++)
		arr[i] = Ratio(0, 1);	
	arr[s] = v;
}

APolynom::APolynom(const std::initializer_list<Ratio>& va)
{
	int i = 0;
	s = va.size() - 1;
	arr = new Ratio[s + 1];
	if(!arr)
		throw std::runtime_error("Failed to allocate memory");	
	for(auto r = va.begin(); r != va.end(); r++, i++) 
		arr[i] = *r; 
}

APolynom::APolynom(const APolynom& ap)
{
	arr = NULL;
	*this = ap;
}

APolynom& APolynom::operator=(const APolynom& ap)
{
	if(this == &ap)
		return *this;
	delete[] arr;
	s = ap.s;
	arr = new Ratio[s + 1];
	if(!arr)
		throw std::runtime_error("Failed to allocate memory");
	for(int i = 0; i <= s; i++)
		arr[i] = ap.arr[i];
	return *this;
}

APolynom APolynom::delproc(const APolynom& ap, const bool del)
{
	APolynom r(Ratio(0, 1), 0), y(Ratio(0, 1), 0), x = *this;
	while(x.s >= ap.s) {
		y = APolynom(x.arr[x.s] / ap.arr[ap.s], x.s - ap.s);
		r += y;
		y *= ap;
		x -= y;
	}
	return (del ? r : x);	
}

APolynom APolynom::operator+(const APolynom& ap)
{
	APolynom result(Ratio(0, 1), ap.s > s ? ap.s : s);
	for(int i = 0; i <= s; i++)
		result.arr[i] = arr[i];
	for(int i = 0; i <= ap.s; i++)
		result.arr[i] += ap.arr[i];
	return result;
}

APolynom& APolynom::operator+=(const APolynom& ap)
{
	*this = *this + ap;
	return *this;
}

APolynom APolynom::operator-(const APolynom& ap)
{
	APolynom result(Ratio(0, 1), ap.s > s ? ap.s : s);
	for(int i = 0; i <= s; i++)
		result.arr[i] = arr[i];
	for(int i = 0; i <= ap.s; i++)
		result.arr[i] -= ap.arr[i];
	for(int i = result.s; i >= 0 && !result.arr[i]; i--, result.s--);
	return result;
}

APolynom& APolynom::operator-=(const APolynom& ap)
{
	*this = *this - ap;
	return *this;
}

APolynom APolynom::operator*(const APolynom& ap)
{
	APolynom result(Ratio(0, 1), ap.s + s);
	for(int i = 0; i <= s; i++)
		for(int j = 0; j <= ap.s; j++)
			result.arr[i + j] += arr[i] * ap.arr[j];
	return result;
}

APolynom& APolynom::operator*=(const APolynom& ap)
{
	*this = *this * ap;
	return *this;
}

APolynom APolynom::operator/(const APolynom& ap)
{
	return delproc(ap, true);
}

APolynom& APolynom::operator/=(const APolynom& ap)
{
	*this = *this / ap;
	return *this;
}

APolynom APolynom::operator%(const APolynom& ap)
{
	return delproc(ap, false);
}

APolynom& APolynom::operator%=(const APolynom& ap)
{
	*this = *this % ap;
	return *this;
}

APolynom APolynom::differential()
{
	APolynom result(Ratio(0, 1), s - 1);
	for(int i = s; i > 0; i--)
		result.arr[i - 1] = arr[i] * Ratio(i, 1);
	return result;
}

APolynom APolynom::integral()
{
	APolynom result(Ratio(0, 1), s + 1);
	for(int i = 0; i <= s; i++)
		result.arr[i + 1] = arr[i] / Ratio(i + 1, 1);
	return result;
}

float APolynom::evaluate(float val)
{	
	float result = arr[s];
	for(int i = s; i > 0; i--)
		result = result * val + (float)arr[i - 1];	
	return result;
}

std::ostream& operator<<(std::ostream& os, const APolynom& ap)
{	
	for(int i = ap.s; i > 0; i--)
		if(ap.arr[i])
			os << ap.arr[i] << "x^" << i;
	if(ap.arr[0])
		os << ap.arr[0]; 
	return os;
}

LPolynom::LPolynom(const Ratio& r, int ss)
{
	node* n = new node(NULL, NULL, r, ss);
	if(!n)
		throw std::runtime_error("Failed to allocate memory");
	first = last = n;
}

LPolynom::LPolynom(const std::initializer_list<std::pair<Ratio, int>>& l)
{
	first = last = NULL;
	node* n;
	for(auto r = l.begin(); r != l.end(); r++) {
		n = new node(last, NULL, (*r).first, (*r).second);
		if(!n) {
			clear();
			throw std::runtime_error("Failed to allocate memory");
		}
		if(!first) {
			first = last = n;
		} else {
			last->next = n;
			last = n;
		}
	}
}

LPolynom::LPolynom(const LPolynom& lp)
{
	first = last = NULL;
	*this = lp;
}

void LPolynom::clear()
{
	node *d;
	while(first) {
		d = first;
		first = first->next;
		delete d;
	}
	last = NULL;
}

LPolynom LPolynom::delproc(const LPolynom& lp, const bool del)
{
	LPolynom r, y, x = *this; 
	while(x.last->item.s >= lp.last->item.s) {
		y = LPolynom(x.last->item.r / lp.last->item.r, x.last->item.s - lp.last->item.s);
		r += y;
		y *= lp;
		x -= y;
	}
	return (del ? r : x);	
}

LPolynom LPolynom::plus_minus(const LPolynom& lp, const bool plus)
{
	LPolynom result;
	node *n1 = first, *n2 = lp.first, *n3, *nn;
	while(n1) {
		nn = new node(result.last, NULL, n1->item.r, n1->item.s);
		if(!nn) {
			result.clear();
			throw std::runtime_error("Failed to allocate memory");
		}
		if(!result.first) {
			result.first = result.last = nn;
		} else {
			result.last->next = nn;
			result.last = nn;
		}
		n1 = n1->next;
	}

	n3 = result.first;
	while(n2) {
		while(n3 && n3->item.s < n2->item.s)
			n3 = n3->next;
		nn = new node(NULL, NULL, (plus ? n2->item.r : -n2->item.r), n2->item.s);
		if(!nn) {
			result.clear();
			throw std::runtime_error("Failed to allocate memory");
		}
		if(!n3) {
			if(!result.first) {
				result.first = result.last = nn;
			} else {
				nn->prev = result.last;
				result.last->next = nn;
				result.last = nn;
			}
		} else if(n2->item.s == n3->item.s) {
			if(nn->item.r + n3->item.r == 0) {
				node* t = n3->next;
				if(n3 != result.first)
					n3->prev->next = n3->next;
				else
					result.first = n3->next;
				if(n3 != result.last)
					n3->next->prev = n3->prev;
				else
					result.last = n3->prev;
				delete n3;
				n3 = t;
			} else {
				n3->item.r += nn->item.r;	
			}
			delete nn;
		} else {
			nn->prev = n3->prev;
			nn->next = n3;
			if(n3 == result.first)
				result.first = nn;
			else
				n3->prev->next = nn;
			n3->prev = nn;
		}		
		n2 = n2->next;
	}	
	return result;
}

LPolynom& LPolynom::operator=(const LPolynom& lp)
{
	node *n, *nn;
	if(this == &lp)
		return *this;
	clear();
	n = lp.first;
	while(n) {
		nn = new node(last, NULL, n->item.r, n->item.s);
		if(!nn) {
			clear();
			throw std::runtime_error("Failed to allocate memory");
		}
		if(!first) {
			first = last = nn;
		} else {
			last->next = nn;
			last = nn;
		}
		n = n->next;
	}
	return *this;
}

LPolynom LPolynom::operator+(const LPolynom& lp)
{
	return plus_minus(lp, true);
}

LPolynom& LPolynom::operator+=(const LPolynom& lp)
{
	*this = *this + lp;
	return *this;
}

LPolynom LPolynom::operator-(const LPolynom& lp)
{
	return plus_minus(lp, false);
}

LPolynom& LPolynom::operator-=(const LPolynom& lp)
{
	*this = *this - lp;
	return *this;
}

LPolynom LPolynom::operator*(const LPolynom& lp)
{
	LPolynom result, tmp;
	node *n1, *n2 = lp.first;
	while(n2) {
		tmp = *this;
		n1 = tmp.first;
		while(n1) {
			n1->item.s += n2->item.s;
			n1->item.r *= n2->item.r;
			n1 = n1->next;
		}
		result += tmp;
		n2 = n2->next;
	}
	return result;
}

LPolynom& LPolynom::operator*=(const LPolynom& lp)
{
	*this = *this * lp;
	return *this;
}

LPolynom LPolynom::operator/(const LPolynom& lp)
{
	return delproc(lp, true);
}

LPolynom& LPolynom::operator/=(const LPolynom& lp)
{
	*this = *this / lp;
	return *this;
}

LPolynom LPolynom::operator%(const LPolynom& lp)
{
	return delproc(lp, false);
}

LPolynom& LPolynom::operator%=(const LPolynom& lp)
{
	*this = *this % lp;
	return *this;
}

LPolynom LPolynom::differential()
{
	LPolynom result;
	node *n = first;
	while(n) {
		if(n->item.s - 1 >= 0)
			result += LPolynom(n->item.r * Ratio(n->item.s, 1), n->item.s - 1); 
		n = n->next;
	}
	return result;
}

LPolynom LPolynom::integral()
{
	LPolynom result;
	node *n = first;
	while(n) {
		result += LPolynom(n->item.r / Ratio(n->item.s + 1, 1), n->item.s + 1);
		n = n->next;
	}
	return result;
}

float LPolynom::evaluate(float val)
{
	/* last is always valid, because default constructor private */
	float result = last->item.r;
	node *n = last;
	while(n) {
		for(int i = 0; i < n->item.s - (n->prev ? n->prev->item.s : 0); i++)
			result *= val;
		result += (n->prev ? (float)n->prev->item.r : 0);
		n = n->prev;
	}
	return result;
}

std::ostream& operator<<(std::ostream& os, const LPolynom& lp)
{
	LPolynom::node* n = lp.last;
	while(n) {
		os << n->item.r;
		if(n->item.s)
			os << "x^" << n->item.s;
		n = n->prev;
	}
	return os;
}