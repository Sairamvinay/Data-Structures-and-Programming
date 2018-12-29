#ifndef LONGINT_H
#define LONGINT_H


#include <iostream>
#include <stdbool.h>
#include "StackLi.h"
#include <cstdlib>

using namespace std;

bool isCarry(const int x1,const int x2);
class LongInt{

public:
	StackLi<int> st;
	LongInt();
	friend istream& operator>>(istream&is, LongInt& l);
	friend ostream& operator<<(ostream&os, LongInt l);
	friend LongInt operator+(LongInt lhs,LongInt rhs);
	
};

#endif

