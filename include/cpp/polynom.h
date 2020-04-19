#ifndef _POLYNOM_CPP_H
#define _POLYNOM_CPP_H

#include <stdexcept>
#include <cpp/ratio.h>
#include <utility>

class APolynom
{
private:
	Ratio* arr;
	int s;
private:
	APolynom() { arr = NULL; s = -1; };
public:
	~APolynom() { delete[] arr; };	
	APolynom(const Ratio& v, int ss);
	APolynom(const std::initializer_list<Ratio>&);
	APolynom(const APolynom& ap);
	APolynom& operator=(const APolynom& ap);
	APolynom operator+(const APolynom& ap);
	APolynom& operator+=(const APolynom& ap);
	APolynom operator-(const APolynom& ap);
	APolynom& operator-=(const APolynom& ap);
	APolynom operator*(const APolynom& ap);
	APolynom& operator*=(const APolynom& ap);
	APolynom operator/(const APolynom& ap);
	APolynom& operator/=(const APolynom& ap);
	APolynom differential();
	APolynom integral();
	float evaluate(float val);
	friend std::ostream& operator<<(std::ostream&, const APolynom&);
};

class LPolynom
{
private:
	struct node {
		struct item {
			Ratio r;
			int s;
		};
		node* prev; 
		node* next;
		item item;
		node(node* p, node* n, const Ratio& r, int s) { prev = p; next = n; item.r = r; item.s = s; };
	};
private:
	node* first;
	node* last;
private:
	LPolynom plus_minus(const LPolynom& lp, const bool plus);
	void clear();
	LPolynom() { first = last = NULL; };
public:
	~LPolynom() { clear(); };	
	LPolynom(const Ratio& v, int ss);
	LPolynom(const std::initializer_list<std::pair<Ratio, int>>&);
	LPolynom(const LPolynom& lp);
	LPolynom& operator=(const LPolynom& lp);
	LPolynom operator+(const LPolynom& lp);
	LPolynom& operator+=(const LPolynom& lp);
	LPolynom operator-(const LPolynom& lp);
	LPolynom& operator-=(const LPolynom& lp);
	LPolynom operator*(const LPolynom& lp);
	LPolynom& operator*=(const LPolynom& lp);
	LPolynom operator/(const LPolynom& lp);
	LPolynom& operator/=(const LPolynom& lp);
	LPolynom differential();
	LPolynom integral();
	float evaluate(float val);
	friend std::ostream& operator<<(std::ostream&, const LPolynom&);
};

#endif /* _POLYNOM_CPP_H */