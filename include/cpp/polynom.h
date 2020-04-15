#ifndef _POLYNOM_H
#define _POLYNOM_H

#include <stdexcept>
#include <ratio.h>

class APolynom
{
private:
	Ratio* arr;
	int s;
public:
	~APolynom() { delete[] arr; };	
	APolynom(Ratio v, int ss);
	APolynom(Ratio* va, int ss);
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

#endif /* _POLYNOM_H