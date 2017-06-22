#ifndef STRFUNC
#define STRFUNC
#include <sstream>
#include <string>


template <typename Source, typename Target>
Target convert(Source src){
    stringstream ss;
    ss << src;
    Target tgt;
    ss >> tgt;
    return tgt;

}
#endif // STRFUNC

