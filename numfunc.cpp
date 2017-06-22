#include <sstream>
#include <string>
#include <iomanip>
#include "numfunc.h"
#include "lexer.h"

double truncate(double n){
    stringstream ss;
    ss << fixed << n;
    string s = ss.str();
    for(auto &c: s)
        if(c == '.')
            c = ' ';
    stringstream ss2(s);
    double d;
    ss2 >> d;
    return d;
}

double divide(double lval, double rval, bool zdiv){
    if(rval == 0){
        if(zdiv)
            return INFINITY;
        else throw Error("Zero division is not allowed.");
    }

    return lval / rval;
}

double modulo(double lval, double rval, bool zdiv){
    if(lval < rval)
        return lval;
    else if(lval == rval)
        return 0;
    else{
        if(rval == 0){
            if(zdiv)
                return INFINITY;
            else
                throw Error("Zero division is not allowed.");
        }

        double division = long(lval/rval);
        return lval - (division*rval);
    }
}

bool is_prime(double n){
    if(n < 2.) return false;

    if(n == 2. || n==3. || n==5. || n==7.)
        return true;

    if( modulo(n, 2.) != 0 &&
        modulo(n, 3.) != 0 &&
        modulo(n, 5.) != 0 &&
        modulo(n, 7.) != 0 )
            return true;

    return false;
}


vector<long> divs(long num){
    vector<long>res;
    for(long j=1; j<num/2+1; j++)
        if(num%j==0){
            if(j<0) j *= -1;
            res.push_back(j);
        }
    return res;
}

long gcd(long left, long right){
    if(left==0 || right == 0) return 0;
    long mx = max(left, right);
    long mn = min(left, right);
    long res = mx%mn;
    while(res!=0){
        mx = mn;
        mn = res;
        res = mx%mn;
    }
    return mn;
}

long lcm(long left, long right){
    return abs(left * right)/gcd(left, right);
}

