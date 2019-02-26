#pragma once
#include <iostream>
using namespace std;
typedef unsigned char byte;

class boolvector
{
public:
	boolvector(char *str, int size = -1);
	boolvector(int len = 0);
	boolvector(const boolvector &);
	~boolvector();

	boolvector& operator=(const boolvector&);
	boolvector operator&(const boolvector&);
	boolvector& operator&=(const boolvector&);
	boolvector operator|(const boolvector&);
	boolvector& operator|=(const boolvector&);
	boolvector operator^(const boolvector&);
	boolvector& operator^=(const boolvector&);
	boolvector operator~();
	boolvector operator<<(int);
	boolvector operator>>(int);
	boolvector& operator<<=(int);
	boolvector& operator>>=(int);
	int operator[](int);
	/*Ввод вывод*/
	void printBv();
	friend istream& operator>>(istream &r, boolvector &t)
	{
		char buf[80];
		cout << "Enter the vector" << endl;
		gets_s(buf);
		boolvector temp(buf);
		t = buf;
		return r;
	}
	friend ostream& operator<<(ostream &r, boolvector &t)
	{
		byte mask = 1;
		if (t.len_bv % 8 == 0)
			mask <<= 7;
		else
			mask <<= (t.len_bv % 8 - 1);

		for (int i = 0; i < t.len_mas; i++, mask = 1 << 7)
		{
			for (; mask; mask >>= 1)
			{
				if (t.bv[i] & mask)
					r << '1';
				else
					r << '0';
			}
		}
		r << endl;
		return r;
	}
	/*Установка в 1 или 0*/
	void set0(int);
	void set1(int);
	void all0();
	void all1();
	void set0from(int, int);
	void set1from(int, int);
	void invert(int);
	void invertFrom(int, int);
	int size();
	int size_bv();
	int weight();
private:
	int len_bv, len_mas;
	byte *bv;
};

