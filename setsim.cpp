#include "pch.h"
#include "setsim.h"


setsim::setsim() :boolvector(256)
{
	power = 0;
}
setsim::setsim(char *s) : boolvector(256)
{
	for (int i = 0; s[i]; i++)
		set1(int(s[i]));
	power = weight();
}
setsim::setsim(const setsim &t) :boolvector(t)
{
	power = t.power;
}
setsim::setsim(const boolvector &t) : boolvector(t)
{
	power = this->weight();
}

setsim::~setsim()
{

}
setsim setsim::operator+(const setsim &t)
{
	setsim temp((*this) | t);

	return temp;
}
setsim& setsim::operator+=(const setsim &t)
{
	*this = *this | t;
	return *this;
}

setsim setsim::operator*(const setsim &t)
{
	setsim temp((*this)&t);
	return temp;
}
setsim& setsim::operator*=(const setsim &t)
{
	*this = *this & t;
	return *this;
}

setsim setsim::operator-(const setsim &t)
{
	setsim temp;

	temp = *this &(*this&t).operator~();

	return temp;
}
setsim& setsim::operator-=(const setsim &t)
{
	*this = *this - t;
	return *this;
}

setsim setsim::additional()
{
	setsim temp;
	temp = this->operator~();
	return temp;
}

void setsim::add(char t)
{
	if (operator[](int(t)) == 0)
	{
		set1(int(t));
		power++;
	}
}

void setsim::del(char t)
{
	if (operator[](int(t)) == 1)
	{
		set0(int(t));
		power--;
	}
}

void setsim::clear()
{
	power = 0;
	all0();
}

setsim& setsim::operator=(const setsim &t)
{
	if (this != &t)
	{
		power = t.power;
		boolvector::operator=(t);
	}
	return *this;
}


void setsim::enter()
{
	all0();
	char buf[100];
	cout << "enter your set" << endl;
	gets_s(buf);
	for (int i = 0; buf[i]; i++)
		set1(int(buf[i]));
	power = weight();
}

void setsim::print()
{
	cout << "power = " << power << endl;

	for (int i = 0; i < 256; i++)
	{
		if (operator[](i) == 1)
			cout << char(i) << ' ';
	}
	cout << endl;
}

istream & operator>>(istream& r, setsim &t)
{
	char buf[100];

	cout << "enter your set" << endl;

	r >> buf;
	t.all0();
	for (int i = 0; buf[i]; i++)
		t.set1(int(buf[i]));
	t.power = t.weight();

	return r;
}

ostream& operator<<(ostream &r, setsim &t)
{
	for (int i = 0; i < 256; i++)
	{
		if (t[i] == 1)
			r << char(i) << ' ';
	}
	r << endl;
	r << "Power of set = " << t.power << endl;
	return r;
}
