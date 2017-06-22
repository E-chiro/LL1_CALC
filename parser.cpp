#include "parser.h"
#include <cmath>
#include <vector>
token_stream ts(cin);
extern map<string, double> vars;
extern void set_constants();

double primary(){
    token t = ts.get();

    switch (t.kind) {
    case 'n':
        return  t.value;

    case 'i':{
        string id = t.text;
        t = ts.get();
        if(t.kind == '('){
            double result = func(id);
            t = ts.get();
            assert(')', t.kind);
            return result;
        }
        else
            ts.putback(t);

        if(vars.find(id) == vars.end()){
            throw Error("Cant find var: " + id, Error::Type::name_error);
        }

        return vars[id];
    }


    case '+':
        return +primary();

    case '-':
        return -primary();

    case '(':{
        double expr = expression();
        t = ts.get();
        assert<char>(')', t.kind);
        return expr;
    }


    default:
        if(t.kind=='\n')
            ts.in().putback(t.kind);
        auto e = Error("Primary expected instead of: " + t.as_string(), Error::Type::primary_error);
        e.put_token(t);
        throw e;
    }

}


double term(){
    double lval = primary();
    token t = ts.get();

    while(true)
        switch(t.kind){
        case '*':{
            if(ts.peek().kind == '*'){
                ts.get();
                double pw = expression();
                lval = pow(lval, pw);
                t = ts.get();
                break;
            }

            lval *= primary();
            t = ts.get();
            break;
        }
        case '/':{
            bool  intdiv = false;
            t = ts.get();
            if(t.kind == '/')
                intdiv = true;
            else ts.putback(t);

            double rval = primary();
            if(intdiv)
                lval = truncate(divide(lval, rval));
            else
                lval = divide(lval, rval);
            t = ts.get();
            break;
        }

        case '%':{
            double rval = primary();
            lval = modulo(lval, rval);
            t = ts.get();
            break;
            }
        default:
            ts.putback(t);
            return lval;
        }
}


double expression(){
    double lval = term();

    token t = ts.get();

    while (true)
        switch (t.kind) {
        case '+':
            lval += term();
            t = ts.get();
            break;
       case '-':
            lval -= term();
            t = ts.get();
            break;
        default:
            ts.putback(t);
            return lval;
        }
}


double define(){

    token t = ts.get();
    if(t.kind != 'i') throw Error("Identifier expected.");
    string varname = t.text;

    t = ts.get();
    if(t.kind != '=')
        throw Error("'=' expected. Have: " + t.as_string());

    double expr;

    t =ts.get();

    if(t.kind == 'i'){
        ts.putback(t);
        expr = statement();
    }
    else {
        ts.putback(t);
        expr = expression();
    }

    vars[varname] = expr;
    return expr;
}

double statement(){
    token t = ts.get();

    string varname;
    switch(t.kind){
    case 'i':{

            if(ts.peek().kind == '='){
                ts.putback(t);
                return define();
            }

    }
    default:

        ts.putback(t);
        return expression();
    }
}

void calculate(){

    while(ts.in())
    try{

        token t = ts.get();
        while(t.kind == ';'){
           t = ts.get();
        }

        if(t.kind == 'q') return;

        if(t.kind == 'c'){

            if(t.text == "ls"){
                for(auto i: vars)
                    cout << "\t" << i.first << ": " << i.second << endl;
            }
            else throw Error("Unknnown command.", Error::Type::name_error);

            t = ts.get();
        }


         if(t.kind == '\n'){

             cout << "> ";
             calculate();
         }

         ts.putback(t);
         cout << "= " << statement() << endl;


    }
    catch(Error& e){

        switch(e.type) {
        case Error::Type::lexeme_error:
            cerr << "[LexemeError]: " << e.what() << endl;
            ts.cleanup_mess();
            break;

        case Error::Type::function_error:
            cerr << "[FunctionError]: " << e.what() << endl;
            break;

        case Error::Type::primary_error:
            cerr << "[PrimaryError]: " << e.what() << endl;
            break;

        case Error::Type::name_error:
            cerr << "[NameError]: " << e.what() << endl;
            break;


        case Error::Type::common_error:
            cerr << ":: CommonError :: " << e.what() << endl;
            break;
        }
    }

    catch(...){
        cerr << "[Unknown error].\n";
    }
}


double func(string funcname){

    double result;

    if(funcname == "sqrt"){

        result = sqrt(expression());
    }
    else
        throw Error("Unknown function name: " + funcname, Error::Type::function_error);

    return result;
}
