#include <cpp/ratio.h>
#include <stdexcept>

int Ratio::nod(int b, int l)
{
	if(b % l == 0)
		return l;
	return nod(l, b % l);
}

void Ratio::evaluate()
{
	int n, qq = (q > 0 ? q : -q), dd = (d > 0 ? d : -d);
	if(!q)
		return;
	n = (qq > dd ? nod(qq, dd) : nod(dd, qq));
	q /= n;
	d /= n;
	if(d < 0) {
		q = -q;
		d = -d;
	} 
}

Ratio::Ratio(int qq, int dd)
{
	q = qq;
	d = dd;
	if(!d)
		throw std::runtime_error("Ratio divisor set to zero");
	evaluate();
} 

Ratio Ratio::operator+(const Ratio& x)
{
	Ratio result;
	result.q = q * x.d + x.q * d;
	result.d = d * x.d;
	result.evaluate();
	return result; 
}

Ratio& Ratio::operator+=(const Ratio& x)
{
	q = q * x.d + x.q *d;
	d *= x.d;
	evaluate();
	return *this; 
}

Ratio Ratio::operator-(const Ratio& x)
{
	Ratio result;
	result.q = q * x.d - x.q * d;
	result.d = d * x.d;
	result.evaluate();
	return result; 
}

Ratio& Ratio::operator-=(const Ratio& x)
{
	q = q * x.d - x.q *d;
	d *= x.d;
	evaluate();
	return *this; 
}


Ratio Ratio::operator*(const Ratio& x)
{
	Ratio result = *this;
	result.q *= x.q;
	result.d *= x.d;
	result.evaluate();
	return result; 
}

Ratio& Ratio::operator*=(const Ratio& x)
{
	q *= x.q;
	d *= x.d;
	evaluate();
	return *this; 
}

Ratio Ratio::operator/(const Ratio& x)
{
	Ratio result = *this;
	result.q *= x.d;
	result.d *= x.q;
	result.evaluate();
	return result; 
}

Ratio& Ratio::operator/=(const Ratio& x)
{
	q *= x.d;
	d *= x.q;
	evaluate();
	return *this; 
}

std::ostream& operator<<(std::ostream& os, const Ratio& r)
{
	os << (r.q < 0 ? "-" : "+");
	os << (r.d !=1 ? "(" : "");
	os << (r.q < 0 ? -r.q : r.q);
	if(r.d != 1) 
		os << "/" << r.d << ")"; 
	return os;
}