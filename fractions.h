#ifndef FRACTIONS
#define FRACTIONS

#include <cmath>
#include <iostream>
#include "numfunc.h"
using namespace std;


class Fraction{
    bool proper = true;
    long numer=0;
    long denom=1.;

public:
    Fraction(){};
    Fraction(long numerator, long denominator):

        numer(numerator),
        denom(denominator){
        if(denom == 0)
            throw;
    };

    friend ostream& operator<< (ostream& out, Fraction f){

        if(f.proper && f.numer>f.denom){
            if(abs(f.denom)==1)
                return out << "<" << f.numer << ">";
            long intpart = f.numer/f.denom;
            long _num = f.numer - (intpart*f.denom);
            if(_num == 0)
                return out << "<" << intpart << ">";

            return out << "<" << intpart << "'" << _num << "/" << f.denom << ">";
        }
        if(f.numer == 0) return out << "<" << 0 << ">";
        return out << "<" << f.numer << "/" << f.denom << ">";


    }

    friend istream& operator>> (istream& in, Fraction& f){
        char ch;
        in >> ch;
        if(ch!='<') {
            in.putback(ch);
            in.clear(ios_base::failbit);
        return in;
        }
        long a,b;
        in >> a;
        if(!in) return in;

        in >> ch;
        if(ch != '/'){
            in.putback(ch);
            in.clear(ios_base::failbit);
            return in;
        }
            in >> b;
            if(!in) return in;

            in >> ch;
            if(ch!='>') {
                in.putback(ch);
                in.clear(ios_base::failbit);
                return in;
            }
       f.numer = a;
       f.denom = b;
       return in;
    }

    void is_proper(bool p=true){
        proper = p;
    }

    void reduce(){
        long _gcd = gcd(numer, denom);
        while(_gcd>1){
            numer /= _gcd;
            denom /= _gcd;
            _gcd = gcd(numer, denom);
        }
    }

    friend Fraction operator+ (Fraction lval, Fraction rval){

        long comdenom = lcm(lval.denom, rval.denom);
        long comnumer = (lval.numer*(comdenom/lval.denom))+(rval.numer*(comdenom/rval.denom));

        Fraction result(comnumer, comdenom);
        result.reduce();
        return result;
    }

    friend Fraction operator- (Fraction lval, Fraction rval){

        long comdenom = lcm(lval.denom, rval.denom);
        long comnumer = (lval.numer*(comdenom/lval.denom))-(rval.numer*(comdenom/rval.denom));

        Fraction result(comnumer, comdenom);
        result.reduce();
        return result;
    }


    friend Fraction operator* (Fraction lval, Fraction rval){

        long comnumer = lval.numer * rval.numer;
        long comdenom = lval.denom * rval.denom;
        Fraction result(comnumer, comdenom);
        result.reduce();
        return result;
    }

};




#endif // FRACTIONS




