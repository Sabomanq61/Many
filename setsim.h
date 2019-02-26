#pragma once
#include "boolvector.h"

class setsim :public boolvector
{
	int power;
public:
	setsim();
	setsim(char *);
	setsim(const setsim &);
	setsim(const  boolvector &);
	~setsim();
	/*объединение*/
	setsim operator+(const setsim&);
	setsim& operator+=(const setsim&);
	setsim operator*(const setsim&);
	setsim& operator*=(const setsim&);
	setsim operator-(const setsim&);
	setsim& operator-=(const setsim&);
	setsim additional();
	void add(char);
	void del(char);
	void clear();
	setsim& operator=(const setsim&);
	/*Ввод вывод*/
	void enter();
	void print();
	friend istream& operator>>(istream&, setsim&);
	friend ostream& operator<<(ostream&, setsim&);
};



