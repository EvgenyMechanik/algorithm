#ifndef _RATIO_H
#define _RATIO_H

#include <iostream>

class Ratio
{
private:
	int q;
	int d;
private:
	int nod(int b, int l);
	void evaluate();
public:
	Ratio() { q = 0; d = 1; };
	Ratio(int qq, int dd);
	Ratio operator+(const Ratio&);
	Ratio& operator+=(const Ratio&);
	Ratio operator-(const Ratio&);
	Ratio& operator-=(const Ratio&);
	Ratio operator*(const Ratio&);
	Ratio& operator*=(const Ratio&);
	Ratio operator/(const Ratio&);
	Ratio& operator/=(const Ratio&); 
	Ratio operator-();
	inline int getQ() const { return q; };
	inline int getD() const { return d; };
	inline operator float() const { return (float)q / d; };
	friend std::ostream& operator<<(std::ostream&, const Ratio&);
};

#endif /* _RATIO_H */