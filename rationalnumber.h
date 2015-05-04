#include <iostream>
#include <string>

class RationalNumber{
 private:
  long long int num;
  long long int den;

  RationalNumber( int num, int dem );
  
  long long int get_num();
  long long int get_den();
  std::string get_string();
  int length();
  void simplify();
  void add_rat( RationalNumber toadd );
  void sub_rat( RationalNumber tosub );
  void mul_rat( RationalNumber tomul );
  void div_rat( RationalNumber todiv );
}

RationalNumber::RationalNumber( int num, int dem ){
  this->num = (long) num;
  this->den = (long) dem;
}

long long int RationalNumber::get_num(){
  return this->num;
}

long long int RationalNumber::get_den(){
  return this->den;
}

std::string RationalNumber::get_string(){
  if ( this.get_den() == 1 ){
    return string( this.get_num() );
  }

  std::string ret = "";
  ret += this->num;
  ret += '/';
  ret += this->den;
  return ret;
}

int RationalNumber::length(){
  return ( this.get_string() ).size();
}

void RationalNumber::simplify(){
  int div = 2;
  long long int num = this->num;
  long long int den = this->den;

  long long int smaller = ( num < den ) ? num : den;

  while( div < smaller ){
    if ( num % div == 0 && den % div == 0 ){
      num /= div;
      den /= div;
      div--;
    }
    div++;
  }

  this->num = num;
  this->den = den;
}

void RationalNumber::add_rat( RationalNumber toadd ){
  (this->num) *= toadd.get_den();
  (this->den) *= toadd.get_den();

  long long int toaddnum = toadd.get_num() * this.get_den();
  (this->num) += toaddnum;

  this.simplify();
}

void RationalNumber::sub_rat( RationalNumber tosub ){
  RationalNumber negtosub = RationalNumber( -1*tosub.getnum(), tosub.getden() );
  this.add_rat( negtosub );
}

void RationalNumber::mul_rat( RationalNumber tomul ){
  (this->num) *= tomul.getnum();
  (this->den) *= tomul.getden();
  this.simplify();
}

void RationalNumber::div_rat( RationalNumber todiv ){
  (this->num) *= todiv.getden();
  (this->den) *= tomul.getnum();
  this.simplify();
}
