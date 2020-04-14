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
	APolynom(Ratio v, int ss)
	{		
		s = ss;
		arr = new Ratio[s + 1];
		if(!arr)
			throw std::runtime_error("Failed to allocate memory");		
		arr[s] = v;
	}
	APolynom(const APolynom& ap)
	{
		arr = NULL;
		*this = ap;
	}
	APolynom& operator=(const APolynom& ap)
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
	APolynom operator+(const APolynom& ap)
	{
		APolynom result(0, ap.s > s ? ap.s : s);
		for(int i = 0; i <= s; i++)
			result.arr[i] = arr[i];
		for(int i = 0; i <= ap.s; i++)
			result.arr[i] += ap.arr[i];
		return result;
	}
	APolynom operator-(const APolynom& ap)
	{
		APolynom result(0, ap.s > s ? ap.s : s);
		for(int i = 0; i <= s; i++)
			result.arr[i] = arr[i];
		for(int i = 0; i <= ap.s; i++)
			result.arr[i] -= ap.arr[i];
		return result;
	}
	APolynom operator*(const APolynom& ap)
	{
		APolynom result(0, ap.s + s);
		for(int i = 0; i <= s; i++)
			for(int j = 0; j <= s; j++)
				result[i + j] += arr[i] * ap.arr[j];
		return result;
	}
	APolynom operator/(const APolynom& ap)
	{
		APolynom result(0, 0), y(0, 0), x = *this;
		while(x.s >= ap.s) {
			y = APolynom(x.arr)
		}	
	}
	APolynom differential()
	{
		APolynom(0, s - 1);
		for(int i = s; i > 0; i--)
			result.arr[i - 1] = arr[i] * i;
		return result;
	}
	APolynom integral()
	{
		APolynom result(0, s + 1);
		for(int i = 0; i <= s; i++)
			result.arr[i + 1] = arr[i] / (i + 1);
		return result;
	}
	float evaluate(float val)
	{	
		float result = arr[s];
		for(int i = s - 1; i > 0; i--)
			result += result * val + arr[i - 1];
		return result;
	}
};

#endif /* _POLYNOM_H