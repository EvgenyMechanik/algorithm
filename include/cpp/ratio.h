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
	inline int getQ() const { return q; };
	inline int getD() const { return d; };
	friend std::ostream& operator<<(std::ostream&, const Ratio&);
};

#endif /* _RATIO_H */