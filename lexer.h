#ifndef LEXER
#define LEXER
#include <string>
#include <iostream>
#include <sstream>
#include <deque>

using namespace std;
class token{

public:

    char kind = '?';
    double value = 0;
    string text = "...";
    string dbg_info = "from_stream";
    token(){}
    token(char knd): kind(knd) {}
    token(double val): kind('n'), value(val) {}
    token(char knd, const string& txt): kind(knd), text(txt) {}
    friend ostream& operator<< (ostream&, token);
    operator bool() {return (*this).kind != '?';}
    string as_string();

};

class token_stream{
    istream* pointer = nullptr;
    token buffer = token();
    bool full = false;
    deque<token> peekbuff;
    bool peeked = false;

public:

    token_stream(istream& src): pointer(&src) {}
    void set_source(istream& src) {pointer = &src;}
    istream& in(){return *pointer;}
    void putback(token);
    token buffs()const;
    token get();
    token peek();
    token next();
    void cleanup_mess();
};

class Error{
    string message;
    string str;
    token tok;
public:
    void put_token(const token& t){tok = t;}
    token get_tok()const {return tok;}
    enum class Type {common_error, lexeme_error, name_error, primary_error, function_error} type;
    Error(const string& msg, Type _type = Type::common_error): message(msg), type(_type){}
    string what()const {return message;}

};


template <typename T>
void assert(T expect, T got){
    if(expect != got){
        stringstream ss;
        ss << "'" << expect << "' expected, but got: '" << got << "'.";
        throw Error(ss.str());
    }
}





#endif // LEXER

