#include <cpp/polynom.h>

APolynom::APolynom(Ratio v, int ss)
{		
	s = ss;
	arr = new Ratio[s + 1];
	if(!arr)
		throw std::runtime_error("Failed to allocate memory");		
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
		for(int j = 0; j <= s; j++)
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
	APolynom result(Ratio(0, 1), 0), y(Ratio(0, 1), 0), x = *this;
	while(x.s >= ap.s) {
		y = APolynom(x.arr[x.s] / ap.arr[ap.s], x.s - ap.s);
		result += y;
		y *= ap;
		x -= y;
	}
	return result;	
}

APolynom& APolynom::operator/=(const APolynom& ap)
{
	*this = *this / ap;
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
	os << ap.arr[0]; 
	return os;
}