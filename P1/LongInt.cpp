#include "LongInt.h"

using namespace std;

bool isCarry(const int x1,const int x2){
	return ((x1+x2)>=10);
}

LongInt::LongInt()
{;}



LongInt operator+(LongInt lhs,LongInt rhs){
	
	LongInt result;
	int carry=0;
	int digit=0;
	while ((!lhs.st.isEmpty()) && (!rhs.st.isEmpty())){

		if (isCarry(lhs.st.top()+rhs.st.top(),carry)){
			digit = (lhs.st.topAndPop() + rhs.st.topAndPop() + carry) % 10;
			result.st.push(digit);
			carry = 1;
		}

		else{
				result.st.push(lhs.st.topAndPop() + rhs.st.topAndPop() + carry);
				carry = 0;
			}
  	}

  	
    
    // if one stack is finished
  	if (lhs.st.isEmpty()){
  			while (!rhs.st.isEmpty()){
  				if (isCarry(rhs.st.top(),carry)){
  					result.st.push((rhs.st.topAndPop()+carry)%10);
  					carry =1;
  				}

  				else{

  					result.st.push(rhs.st.topAndPop() + carry);
  					carry = 0;
  				}
  			}

  	}

  	else if (rhs.st.isEmpty()){
  		while (!lhs.st.isEmpty()){
  				if (isCarry(lhs.st.top(),carry)){
  					result.st.push((lhs.st.topAndPop()+carry)%10);
  					carry =1;
  				}

  				else{

  					result.st.push(lhs.st.topAndPop() + carry);
  					carry = 0;
  				}
  		}
  	}

  	if (lhs.st.isEmpty() && rhs.st.isEmpty()){

  		if (carry == 1)
  			result.st.push(carry);

  	}

  	return result;
 }


istream& operator>>(istream& is, LongInt& l){
	char digitc;
	while (is.get(digitc) && digitc != '\n'){
		
		int digit = digitc - '0';
		l.st.push(digit);	

	}
	
	return is;
}

ostream& operator<<(ostream& os, LongInt l){
	StackLi<int> s = l.st;
	while (!s.isEmpty()){
		os<<s.topAndPop();
	}
	return os;
}