#include "pch.h"
#include "boolvector.h"

boolvector::boolvector(char *str, int size)
{
	if (strlen(str)) {

		if (size == -1)
		{
			len_bv = strlen(str);
		}
		else {
			len_bv = size;
		}
		if (len_bv)
		{
			len_mas = (len_bv - 1) / 8 + 1;

			bv = new byte[len_mas];
			all0();

			byte mask = 1;
			int i = strlen(str) - 1;
			for (int i1 = len_bv, i2 = len_mas - 1; i1 > 0 && i >= 0; i1--, i--, mask <<= 1)
			{
				if (!mask)
				{
					mask = 1;
					i2--;
				}
				if (str[i] == '1')
					bv[i2] |= mask;
			}
		}
	}
	else
	{
		len_bv = 0;
		len_mas = 0;
		bv = nullptr;
	}
}


boolvector::boolvector(int len)
{
	if (len > 0)
	{
		len_bv = len;
		len_mas = (len_bv - 1) / 8 + 1;
		bv = new byte[len_mas];
		all0();
	}
	else {
		len_bv = 0;
		len_mas = 0;
		bv = nullptr;
	}
}

boolvector::boolvector(const boolvector &t)
{
	if (t.bv)
	{
		len_bv = t.len_bv;
		len_mas = t.len_mas;
		bv = new byte[len_mas];

		for (int i = 0; i < len_mas; i++)
			bv[i] = t.bv[i];
	}
	else
	{
		len_bv = len_mas = 0;
		bv = nullptr;
	}
}

boolvector::~boolvector()
{
	delete[]bv;
}

boolvector& boolvector::operator=(const boolvector &t)
{
	if (this != &t)
	{
		if (bv)
			delete[]bv;
		len_bv = t.len_bv;
		len_mas = t.len_mas;
		bv = new byte[len_mas];

		for (int i = 0; i < len_mas; i++)
			bv[i] = t.bv[i];
	}
	return *this;
}

boolvector boolvector::operator&(const boolvector &t)
{

	int length;

	if (len_bv > t.len_bv)
		length = t.len_bv;
	else
		length = len_bv;

	boolvector temp(length);

	for (int i1 = len_mas - 1, i2 = t.len_mas - 1, i = temp.len_mas - 1; i1 >= 0 && i2 >= 0; i1--, i2--, i--)
	{
		temp.bv[i] = bv[i1] & t.bv[i2];
	}

	return temp;
}

boolvector& boolvector::operator&=(const boolvector &t)
{
	*this = *this &t;
	return *this;
}

boolvector boolvector::operator|(const boolvector &t)
{
	int length;
	if (len_bv > t.len_bv) {
		length = len_bv;
	}
	else
	{
		length = t.len_bv;
	}
	boolvector temp(length);
	int i, i1, i2;

	for (i = t.len_mas - 1, i1 = len_mas - 1, i2 = temp.len_mas - 1; i >= 0 && i1 >= 0; i--, i1--, i2--)
	{
		temp.bv[i2] = bv[i1] | t.bv[i];
	}

	for (; i >= 0 && i2 >= 0; i--, i2--)
		temp.bv[i2] = t.bv[i];
	for (; i1 >= 0 && i2 >= 0; i1--, i2--)
		temp.bv[i2] = bv[i1];

	return temp;
}

boolvector& boolvector::operator|=(const boolvector &t)
{
	*this = *this | t;
	return *this;
}

boolvector boolvector::operator^(const boolvector &t)
{
	int length;

	if (len_bv > t.len_bv) {
		length = t.len_bv;
	}
	else
	{
		length = len_bv;
	}

	boolvector temp(length);
	int i1, i2, i3;
	for (i1 = temp.len_mas - 1, i2 = len_mas - 1, i3 = t.len_mas - 1; i2 >= 0 && i3 >= 0; i1--, i2--, i3--) {
		temp.bv[i1] = bv[i2] ^ t.bv[i3];
	}
	return temp;
}

boolvector& boolvector::operator^=(const boolvector &t)
{
	*this = *this ^t;
	return *this;
}

boolvector boolvector::operator~()
{
	boolvector temp(*this);
	temp.invertFrom(0, len_bv);
	return temp;
}

int boolvector::operator[](int index)
{
	if (index < len_bv && index >= 0)
	{
		int index_byte = len_mas - index / 8 - 1;
		if (bv[index_byte] & (1 << index % 8))
			return 1;
		return 0;
	}
	return -1;
}

boolvector boolvector::operator<<(int t)
{
	boolvector temp(*this);
	temp <<= t;

	return temp;
}

boolvector boolvector::operator>>(int t)
{
	boolvector temp(*this);
	temp >>= t;
	return temp;
}
boolvector& boolvector::operator<<=(int t)
{

	int j = len_bv - 1;
	for (int i = j - t; i >= 0; i--, j--)
		if (this->operator[](i))
			set1(j);
		else
			set0(j);
	set0from(0, t);

	return *this;

}

boolvector& boolvector::operator>>=(int t)
{
	int j = 0;
	for (int i = j + t; i < len_bv; i++, j++)
	{
		if (this->operator[](i))
			set1(j);
		else
			set0(j);
	}
	set0from(len_bv - t, t);

	return *this;
}

void boolvector::printBv()
{
	byte mask = 1;
	if (len_bv % 8 == 0)
		mask <<= 7;
	else
		mask <<= (len_bv % 8 - 1);

	for (int i = 0; i < len_mas; i++, mask = 1 << 7)
	{
		for (; mask; mask >>= 1)
		{
			if (bv[i] & mask)
				cout << '1';
			else
				cout << '0';
		}
	}
	cout << endl;
}

void boolvector::set1(int index)
{
	if (index < len_bv)
	{
		int index_byte = len_mas - index / 8 - 1;
		bv[index_byte] |= (1 << index % 8);
	}
}

void boolvector::set0(int index)
{
	if (index < len_bv)
	{
		int index_byte = len_mas - index / 8 - 1;
		bv[index_byte] &= ~(1 << index % 8);
	}
}

void boolvector::all0()
{
	for (int i = 0; i < len_mas; i++)
		bv[i] = 0;
}

void boolvector::all1()
{
	this->set1from(0, len_bv);
}
void boolvector::set0from(int index, int k)
{
	if (len_bv - index >= k) {
		byte mask = 1 << (index % 8);
		int index_byte = len_mas - index / 8 - 1;

		for (int i = 0; i < k; i++, mask <<= 1)
		{
			if (!mask)
			{
				mask = 1;
				index_byte--;
			}
			bv[index_byte] &= ~mask;
		}
	}
}
void boolvector::set1from(int index, int k)
{
	if (len_bv - index >= k) {
		byte mask = 1 << (index % 8);
		int index_byte = len_mas - index / 8 - 1;

		for (int i = 0; i < k; i++, mask <<= 1)
		{
			if (!mask)
			{
				mask = 1;
				index_byte--;
			}
			bv[index_byte] |= mask;
		}
	}
}

void boolvector::invert(int index)
{
	if (index >= 0 && index < len_bv)
	{
		int index_byte = len_mas - index / 8 - 1;

		if (bv[index_byte] & (1 << (index % 8)))
			bv[index_byte] &= ~(1 << index % 8);
		else
			bv[index_byte] |= (1 << index % 8);
	}
}

void boolvector::invertFrom(int index, int k)
{
	if (index >= 0 && index < len_bv)
	{
		if (k <= (len_bv - index)) {
			int index_byte = len_mas - index / 8 - 1;
			byte mask = 1 << (index % 8);
			for (int i = 0; i < k; i++, mask <<= 1)
			{
				if (!mask)
				{
					index_byte--;
					mask = 1;
				}
				if (bv[index_byte] & mask)
					bv[index_byte] &= ~mask;
				else
					bv[index_byte] |= mask;
			}
		}
	}
}

int boolvector::size()
{
	return this->len_bv;
}

int boolvector::size_bv()
{
	return this->len_mas;
}

int boolvector::weight()
{
	int res = 0;
	byte mask;
	for (int i = 0; i < len_mas; i++)
	{
		for (mask = 1; mask; mask <<= 1)
		{
			if (bv[i] & mask)
				res++;
		}
	}
	return res;
}
