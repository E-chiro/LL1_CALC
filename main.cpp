#include "parser.h"
using namespace std;

extern token_stream  ts;
int main(int argc, char** argv){
    set_constants();



    try{
        cout << "> ";
        calculate();

    }catch(Error& e){
        cerr << e.what() << endl;
    }

   return 0;
}
