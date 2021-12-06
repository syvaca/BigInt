#include "bigint.h"
#include <iostream>
#include <string>
#include <climits>
#include <cmath>
#include <vector>
using namespace std;

//******************************************************************
//START OF THE CONSTRUCTORS SECTION
//******************************************************************

/*
// Create a default BigInt with base 10.
// This function is complete. You do not have to add anything.
*/
BigInt::BigInt(){
  base = 10;
  isPositive = true;
}

/*
// Create a BigInt with a specified base.
// This function is complete. You do not have to add anything.
*/
BigInt::BigInt(int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    base = setbase;
    isPositive = true;
}

/*
// Destructure. You do not have to add anything.
// This function is complete
*/
BigInt::~BigInt(){}

/*
//  Create a BigInt from int (base 10).
//  - Convert the int (base 10) input into a specified base (setbase).
//  - Don't forget to set the base accordingly
//  For example:
//     BigInt k(6,2) <- int 6 base 10 to BigInt base 2
//          - Result:  BigInt k with value 110 (base 2)
//     BigInt k(154,16) <- 154 base 10 to BigInt base 16
//          - Result: BigInt k with value 9A (base 16)
*/
BigInt::BigInt(int input,int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    /************* You complete *************/
  base = setbase;
  isPositive = true;
  int temp = input;
  
  if(temp < 0) {
    isPositive = false;
    temp *= -1;
  }
  
  if(temp == 0) {
    vec.push_back(0);
  }
  
  while (temp != 0) {
    vec.push_back(temp%base);
    temp = temp/base;
  }
}

/*
//  Create a BigInt from string.
//  Don't forget to set the base accordingly
//  The input string will contain
//      - numbers (0-9) and/or 
//      - uppercase letters (A-Z) [A=10, B=11, ... , Z=35]
//  The input string may contain
//      - a negative sign ('-') to signify that the number is negative.
//  Note: char '0' = int 48 (see ASCII table)
//  Note: char 'A' = int 65
*/
BigInt::BigInt(const string &s, int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    /************* You complete *************/
  
  int len = s.length();
  int end = 0;
  base = setbase;
  isPositive = true;
  
  if(len == 0) {
    vec.push_back(0);
    return;
  }
  
  if(s[0] == '-') {
    isPositive = false;
    end++;
  }
  
  for(int i = len -1; i >=end; i--) {
    if(s[i] <= 57) {
      int dig = (int)(s[i]) - 48;
      vec.push_back(dig);
    }
    
    else {
       int dig = (int)(s[i]) - 55;
       vec.push_back(dig);
    }
  } 
}

/*
//  Create a BigInt from another BigInt.
//  This is a copy constructor.
//  Simply call the assignment operator (=) below.
*/
BigInt::BigInt(const BigInt &b){

    /************* You complete *************/
  
  *this = b;
}
  

/*
//  Assignment operator. (i.e., BigInt a = b;)
//  Overriding a's data with BigInt b's data
//       - vec
//       - isPositive
//       - base
*/
BigInt & BigInt::operator = (const BigInt &b){

    /************* You complete *************/

  base = b.base;
  vec = b.vec;
  isPositive = b.isPositive;

    return *this;
}


//******************************************************************
//END OF THE CONSTRUCTORS SECTION
//******************************************************************

//******************************************************************
//START OF THE DISPLAYS SECTION
//******************************************************************

/*
// Convert to string and return the string
// Display it in its corresponding base
//  Note: char '0' = int 48 (see the ASCII table)
//  Note: char 'A' = int 65
*/
string BigInt::to_string(){

    /************* You complete *************/

  int size = vec.size();
  
  string output = "";
  
  if(!isPositive) {
    output += '-';
  }
  
  for(int i = size-1; i >=0; i--) {
    if(vec[i]>=10 && vec[i]<=36) {
      output += (char)(vec[i] +55);
    }
    else {
      output += (char)(vec[i]+48);
    }
  }

  return output;
   
}

/*
//  Convert BigInt to integer base 10 and return that int
//    If BigInt >= INT_MAX, return INT_MAX.
//    If BigInt =< INT_MIN, return INT_MIN.
//  Note: 1. INT_MAX and INT_MIN are already defined for you
//           in the 'climits' library.
//        2. INT_MAX = 2147483647, INT_MIN = -2147483648
//           therefore, INT_MIN does not equal to (-INT_MAX)
*/
int BigInt::to_int() const{

    /************* You complete *************/
  
  int result = 0;
  int power = 0;
  
  for(int i=0; i <= (int)vec.size()-1; i++) {
    if(isPositive) {
      result += (vec[i]*pow(base,power));
    }
    
    else if(!isPositive) {
      result -= (vec[i]*pow(base,power));
      
      if(result <= INT_MIN) {
        result = INT_MIN;
      }
    }
    power++;
  }
  
  if(result <= INT_MIN) {
     return INT_MAX;
  }
  
  return result;
}



//******************************************************************
//END OF THE DISPLAYS SECTION
//******************************************************************

//******************************************************************
//START OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************

/*
//  Compare a and b.
//     If a = b, return 0.
//     If a < b, return -1.
//     If a > b, return 1.
//  See the HINT below
*/
int BigInt::compare(const BigInt &b) const{
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/

    //HINT:
    //1. do NOT call the to_int() or to_string() function
    //2. do NOT convert bigInt to other datatypes first (e.g., long long, int)
    
    //First let's compare the signs
    //    - if the signs aren't the same,
    //              how do you know which one is larger?
  
  if(isPositive != b.isPositive) {
    if(b.isPositive) {
      return -1;
    }
    else {
      return 1;
    }
  }

    //If they have the same sign, let's compare their vec sizes 
    //    - what if both are positive, but a's vec is larger (a or b is larger?)
    //    - other cases?
    
  int sizea = vec.size();
  int sizeb = b.vec.size();
  
  if(sizea != sizeb) {
    
    if(!isPositive) {
      if(sizea < sizeb) {
      return 1;
      }
      else {
        return -1;
      }
    }
   
    else{
      if(sizea > sizeb) {
        return 1;
      }
      else {
        return -1;
      }
    }
  }
  
    //If they have the same vec size, let's compare their digits one by one
    // Starting from the most-significant digits. --> in what vector position?
    // Remember that the BigInt vectors are in reverse order!
    //    - what if both are positive, but the digit of a is greater than that of b (a or b is larger?)
    //    - other cases?
  
  int vala;
  int valb;
  int same = 0;
  
  for(int i = sizeb - 1; i >=0; i--) {
    vala = vec[i];
    valb = b.vec[i];
    
    if(vala != valb) {
      if(!isPositive) {
        
        if(vala < valb) {
          return 1;
        }
        else {
          return -1;
        }
      }
      
      else {
        if(vala > valb) {
          return 1;
        }
        else {
          return -1;
        }
      }
    }
    
    else {
      same++;
    }
  }
  
  //If ALL digits are the same, then they MUST be equal!!
  if(same == sizeb) {
    return 0;
  } 
  
  return 0;
}


//Call the compare function above to check if a == b
bool operator == (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
  
  int compare = a.compare(b);
  
  if(compare == 0) {
    return true;
  }
  
  else {
    return false;
  } 
  
}

//Call the compare function above to check if a != b
bool operator != (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/

  int compare = a.compare(b);
  
  if(compare != 0) {
    return true;
  }
  
  else {
    return false;
  }
}

//Call the compare function above to check if a <= b
bool operator <= (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/

  int compare = a.compare(b);
  
  if(compare == 1) {
    return false;
  }
  
  else {
    return true;
  }
  
}

//Call the compare function above to check if a >= b
bool operator >= (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/

  int compare = a.compare(b);
  
  
  if(compare == -1) {
    return false;
  }
  
  else {
    return true;
  }
  
  
}

//Call the compare function above to check if a > b
bool operator > (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
  
  int compare = a.compare(b);
  
  if(compare == 1) {
    return true;
  }
  
  else {
    return false;
  }
  
}

//Call the compare function above to check if a < b
bool operator < (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
  
  int compare = a.compare(b);
  
  if(compare == -1) {
    return true;
  }
  
  else {
    return false;
  }
  
}

//******************************************************************
//END OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************

//******************************************************************
//START OF THE ARITHMETIC OPERATORS SECTION
//******************************************************************

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call += operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/ 
BigInt operator + (const  BigInt &a, const BigInt & b){

  /************* You complete *************/
  
  BigInt c = b;
  c += a;
  return c;

}

/*
//==================
// MEMBER function
//==================
//  Addition assignment operator.
//    i.e., a += b
*/
const BigInt & BigInt::operator += (const BigInt &b){
    if(base != b.base){
     
        throw DiffBaseException();
    }
    /************* You complete *************/
  
  int carry = 0;
  int sum = 0;
  BigInt bvec = b;
  BigInt avec = *this;
 
  
  //zero
  if(b.to_int() == 0) {
    return *this;
  }
  if(to_int() == 0) {
    *this = bvec;
    return *this;
  }
  
  //different signs
  if(isPositive == true && b.isPositive == false) {
    bvec.isPositive = true;
    *this -= bvec;
    return *this;
  }
  
  if(isPositive == false && b.isPositive == true) {
    avec.isPositive = true;
    bvec -= avec;
    *this = bvec;
    return *this;
  }
  
  //add
  
  unsigned int size  = max(vec.size(), b.vec.size());
  int val;
  int valb;
  
  for(int unsigned i = 0; i <size; i++) {
    if(isPositive == b.isPositive) {
      if(i < vec.size()) {
        val= vec[i];
      }
      else {
        val = 0;
      }
    
    
      if(i < b.vec.size()) {
        valb = b.vec[i];
      }
      else {
        valb = 0;
      }
    
      sum = val + valb + carry;
      carry = sum / base;
      sum = sum % base;

     
      if(i < vec.size()) {
       vec[i] = sum;
     }
     else {
       vec.push_back(sum);
     }

 
    }

  }
  
  //add carry to end of both same sign addition
  if(isPositive == b.isPositive) {
    if(carry != 0) {
       vec.push_back(carry);
    } 
  }
    
 

    return *this;
  
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call -= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator - (const  BigInt &a, const BigInt & b){

  /************* You complete *************/
  
  BigInt c(a);
  c -= b;
  return c;  

}

/*
//==================
// MEMBER function
//==================
//  Subtraction assignment operator.
//    i.e., a -= b
//  Note: Think of base cases (e.g., subtract by itself)
*/
const BigInt & BigInt::operator -= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/
  
  int difference = 0;
  int borrow = 0;
  BigInt bvec = b;
  BigInt avec = *this;
  
  
  //if same vectors
  if(vec == b.vec) {
    if(isPositive == b.isPositive) {
      BigInt zero;
      zero.base = b.base;
      zero.vec.push_back(0);
      *this = zero;
      return *this;
    }
    if(isPositive == true and b.isPositive == false) {
      bvec.isPositive = true;
      *this += bvec;
      return *this;
    }
    if(isPositive == false and b.isPositive == true) {
      bvec.isPositive = false;
      *this += bvec;
      return *this;
    }
  }
  
  
 //different signs
  if(isPositive == true && b.isPositive == false) {
    bvec.isPositive = true;
    *this += bvec;
    return *this;
  }
  
  if(isPositive == false && b.isPositive == true) {
    avec.isPositive = true;
    bvec += avec;
    bvec.isPositive = false;
    *this = bvec;
    return *this;
  }
   
    
  //subtract
  if((isPositive && (*this) < b)) {
    avec = b - *this;
    *this = avec;
    isPositive = false;
    return *this;
  }
  
  if((!isPositive && (*this) > b)) {
    avec = b - *this;
    *this = avec;
    isPositive = true;
    return *this;
  }
    
  unsigned int size  = max(vec.size(), b.vec.size());
  int val;
  int valb;
  
  for(unsigned int i = 0; i < size; i++) {
    
    if(i < vec.size()) {
      val = vec[i];
    }
    else {
      val = 0;
    }
    
    if(i < b.vec.size()) {
      valb = b.vec[i];
    }
    else {
      valb = 0;
    }
    
    difference = val - valb - borrow;
    borrow = 0;
    if(difference < 0) {
      difference += base;
      borrow++;
    }
    
    if(i < vec.size()) {
       vec[i] = difference;
     }
     else {
       vec.push_back(difference);
     }
  }
  
  
  //remove all leading zeros
  for(int i = vec.size()-1; i >= 0; i--) {
    if(vec[i] == 0) {
      vec.pop_back();
  }
    else {
      break;
    }
  }
  
  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call *= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator * (const  BigInt &a, const BigInt & b){

    /************* You complete *************/

  BigInt c(b);
  c *= a;
  return c;

}

/*
//==================
// MEMBER function
//==================
//  Multiplication assignment operator.
//    i.e., a *= b
//  Implement Long Multiplication
//  Note: What are the base cases?? (e.g., multiply by 0)
*/
const BigInt & BigInt::operator *= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/

  //zero
  if(b.to_int() == 0) {
    *this = b;
    return *this;
  }
  if(to_int() == 0) {
    for(unsigned int i = 0; i < vec.size(); i++){
    }
    return *this;
  }
  
  //one
  if(b.to_int() == 1) {
    return *this;
  }
  if(to_int() == 1) {
    *this = b;
    return *this;
  }
  
  
  //is result negative
  bool neg = isPositive == b.isPositive;

  int carry = 0;
  vector<int> result;
  int product;
  
  int maxdig = max(vec.size(), b.vec.size());
  maxdig *= 2;
  
  for(int i = 0; i < maxdig; i++) {
    result.push_back(0);
  }
  
  for(unsigned int i = 0; i <vec.size(); i++) {
    
    for(unsigned int k =0; k<b.vec.size(); k++) {
      product = vec[i]*b.vec[k] + carry;
      carry = product/base;
  
      
      if(product >= base) {
        product = product%base;   
      } 

      result[k+i] += product;
      
      if(k == b.vec.size()-1) {
        if(carry != 0) {
          result[k+i+1] += carry;
          carry = 0;
        }
      }
    }
  } 
  
  //single digits in each vector index
  for(unsigned int i = 0; i < result.size(); i++) {
    if(result[i] >= base) {
      int temp = result[i];
      result[i] %= base;
      result[i+1] += temp/base;
    }
  }
  
  
  //remove all leading zeros
  for(int i = result.size()-1; i >= 0; i--) {
    if(result[i] == 0) {
      result.pop_back();
  }
    else {
      break;
    }
  }
    
    
  vec = result;
  this->isPositive = neg;
  
  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call /= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator / (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
   
  BigInt c = a;
  c /= b;
  
  return c;
}


/*
//==================
// MEMBER function
//==================
//  Division assignment operator.
//    - Call 'divisionMain' to get the quotient;
*/
const BigInt & BigInt::operator /= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();
    }
    /************* You complete *************/
    
  BigInt q;
  BigInt r;
  
  q.base = base;
  r.base = base;
    
  divisionMain(b, q, r);
  *this = q;
 
  return *this;
  
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call %= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator % (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
  
  BigInt c = a;
  c %= b;
  return c;

}

/*
//==================
// MEMBER function
//==================
//  Modulus assignment operator.
//    - Call 'divisionMain' to get the remainder;
//    - Note: remainder takes the sign of the dividend.
*/
const BigInt & BigInt::operator %= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();//divide by zero.
    }
    /************* You complete *************/

  BigInt q;
  BigInt r;
  
  q.base = base;
  r.base = base;
    
  divisionMain(b, q, r);
  *this = r;
  return *this;
  
}

/*
//  Main function for the Division (/=) and Modulus (%=) operators.
//     - Compute (q)uotient and (r)emainder
//     - Implement Long Division
//  Note: 1. This should behave like integer division
//        2. What are the base cases?? (e.g., div by itself)
*/
void BigInt::divisionMain(const BigInt &b, BigInt &quotient, BigInt &remainder){

    /************* You complete *************/

  
//1
  BigInt divisor(b);               
  BigInt dividend(*this); 
  bool sign = isPositive == b.isPositive;
  bool startsign = isPositive;
  dividend.isPositive = true;
  divisor.isPositive = true;

  
  //divide by one
  if(divisor.to_int() == 1) {
    quotient = dividend;
    quotient.isPositive = sign;
    remainder.vec.push_back(0);
    remainder.isPositive = true;
    return;
  }
  
  //divide by itself
  if(divisor == dividend) {
    quotient.vec.push_back(1);
    quotient.isPositive = sign;
    remainder.vec.push_back(0);
    remainder.isPositive = true;
    return;
  }
  
  //divide by a bigger number
  if(dividend < divisor) {
    quotient.vec.push_back(0);
    quotient.isPositive = true;
    remainder = *this;
    return;
  }
  
  
  
  quotient.vec.clear();
  remainder.vec.clear();
  
  
  //find dividend sequence
  //3
  int pos = vec.size()-1; 
  BigInt dividend_seq(vec[pos], base);
  
  while(dividend_seq < divisor) {
    pos--;
    dividend_seq.vec.insert(dividend_seq.vec.begin(), vec[pos]);
  }
  while(pos >= 0) { //9
    
    //4
    int times = 0;
    while(dividend_seq >= divisor) {
      dividend_seq -= divisor;
      times++;
    }
    
    
    //5
    //construct quotient
     quotient.vec.insert(quotient.vec.begin(),times);
  
     
    //6
    if(dividend_seq.vec.size() == 1 and dividend_seq.vec[0]== 0) {
      dividend_seq.vec.clear();
    }
  
    //7   
    if(pos > 0) {
      dividend_seq.vec.insert(dividend_seq.vec.begin(), vec[pos-1]);
    }
   
    //8
    pos--;
    
  }

 
  quotient.isPositive = sign;
  
  //dividend_seq EMPTY?
  if(dividend_seq.vec.empty()) {
      remainder.vec.push_back(0);
      remainder.isPositive = true;
  }
  else {
    remainder.vec = dividend_seq.vec;
    remainder.isPositive = startsign;
  }

 
  return;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call the 'exponentiation' function on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt pow(const  BigInt &a, const BigInt & b){

    /************* You complete *************/
  
  
  BigInt c(a);
  c.exponentiation(b);
  return c;

}

/*
//==================
// MEMBER function
//==================
//  Exponentiation assignment function.
//     - i.e., a.exponentiation(b);
// Note: 1. implement Exponentiation by Squaring (see the writeup)
//       2. b should be treated as BigInt, not int or other data type.
*/
const BigInt & BigInt::exponentiation(const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }
    /************* You complete *************/

  BigInt acopy(*this);
  BigInt oddcopy;
  BigInt bcopy(b);
  
  BigInt zero(0,base);
  BigInt one(1,base);
  BigInt two(2,base);
  
  oddcopy = one;
  oddcopy.base = base;
  
  //b = 0
  if(bcopy == zero) {
    isPositive = true;
    *this = one;
    return *this;
  }
  
  //b = 1
  if(bcopy == one) {
    return *this;
  }
  
  
  while(bcopy != one) {
    if(bcopy%two == zero) {
      acopy *= acopy;
    }
    
    else if(bcopy%two == one) {
      oddcopy *= acopy;
      acopy *= acopy;
    }
    
    bcopy/= two;
    bcopy.base = b.base;
    
  }
  acopy *= oddcopy; //this line is not working
  *this = acopy;
  return *this;
    
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of <a href=""></a>
// 2. Call the 'modulusExp' function on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt modPow(const BigInt &a, const BigInt &b, const BigInt &m){

    /************* You complete *************/
  
  
  BigInt c(a);
  c.modulusExp(b, m);
  return c;

}
 

/*
//==================
// MEMBER function
//==================
//  Modulus Exponentiation assignment function.
//     - i.e., a.modulusExp(b)
// Note: 1. implement Modulus Exponentiation (see the writeup)
//       2. b should be treated as BigInt, not int or other data type.
// Hint: same implementation as exponentiation, but take modulus 
//          after every call to the *= operator.
*/
const BigInt & BigInt::modulusExp(const BigInt &b, const BigInt &m){
    if(base != b.base || base != m.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }
    /************* You complete *************/

  
  BigInt acopy(*this);
  BigInt oddcopy;
  BigInt bcopy(b);
  
  BigInt zero(0,base);
  BigInt one(1,base);
  BigInt two(2,base);
  
  oddcopy = one;
  oddcopy.base = base;
  
  //b = 0
  if(bcopy == zero) {
    isPositive = true;
    *this = one;
    return *this;
  }
  
  //b = 1
  if(bcopy == one) {
    return *this;
  }
  
  
  while(bcopy != one) {
    if(bcopy%two == zero) {
      acopy *= acopy;
      acopy %= m;
      
    }
    else if(bcopy%two == one) {
      oddcopy *= acopy;
      acopy *= acopy;
      acopy %=m; 
    }
    
    bcopy/= two;
    bcopy.base = b.base;
    
  }
  
  acopy *= oddcopy;
  acopy %= m;
  *this = acopy;

  
    return *this;
}

//******************************************************************
//END OF THE ARITHMETIC OPERATORS SECTION
//******************************************************************
