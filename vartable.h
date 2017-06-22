#ifndef VARTABLE
#define VARTABLE
#include <string>
#include <map>
#include <vector>
#include <functional>
#include "fractions.h"
#include "numfunc.h"
using namespace std;

void set_constants();



class vartable{
    enum class vtype {none=0, integer, real, vector, boolean};
    string name;
    void* address;
    vtype vartype = vtype::none;

};

#endif // VARTABLE

