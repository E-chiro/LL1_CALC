#include "lexer.h"
#include "strfunc.h"





    ostream& operator<< (ostream& out, token t){
        out << '[';
        switch(t.kind){
        case 'n': out << "n:" << t.value; break;
        case 'i': out << "#" << t.text << ":" << t.value; break;
        case '\n': out << "\\n"; break;
        default:
            out << t.kind;
        }
        out << ']';
        if( ! t.dbg_info.empty())
            out << "<" << t.dbg_info << ">";
        return out;
    }

    string token::as_string(){
        stringstream ss;
        ss << *this;
        return ss.str();
    }


    token token_stream::buffs()const {
        if(full) return buffer;
        else if(peekbuff.size()>0)
            return peekbuff.front();
        else return token();
    }


    void token_stream::putback(token t){
        if(full) throw Error("Buffer overflow.");
        buffer = t;
        full = true;

    }

    token token_stream::get(){


        if(peeked){

            peeked = false;

        }

        if(full){
            full = false;
            buffer.dbg_info = "from buffer";
            return buffer;
        }

        if(peekbuff.size()>0){
            token t = peekbuff.front();
            peekbuff.pop_front();
            t.dbg_info = "from peekbuff";
            return t;
        }

        char ch;


        while(in().get(ch) && isspace(ch) && ch!='\n');

        switch(ch){
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '.':{
                if( isalpha( in().peek() ) ){
                    string s;
                    in() >> s;
                    return token('c',s);
                }

                in().putback(ch);
                double d;
                in() >> d;
                return token(d);
            }
        case '\0':
            return token('z');
        case ':':
        case ';': case '\n':
        case '+': case '-':
        case '*': case '/':
        case '%':
        case '(': case ')':
        case '<': case '>':
        case 'q': case '=':
        case 'c':
            return token(ch);

        default:{
            if(isalpha(ch) || ch == '_'){
                string s;
                s = ch;

                while(in().get(ch))
                    if(isalpha(ch) || ((ch == ' ' || ch=='\t') && in().peek() != ' '))
                        s += ch;
                    else {
                        in().putback(ch);
                        stringstream ss;
                        ss << s;
                        string out;
                        while(ss >> s)
                            if(s != " ")
                                out += s;
                        return token('i', out);
                    }
            }

            throw Error("Wrong lexeme: " + ch, Error::Type::lexeme_error);
        }

     }
  }

    token token_stream::peek(){

        token t = get();

        peeked = true;
        peekbuff.push_back(t);
        return t;
    }

    token token_stream::next(){
        if(full) return buffer;
        else if(peekbuff.size()>0)
            return peekbuff.front();
        else {
            buffer = get();
            return buffer;
        }
    }

    void token_stream::cleanup_mess(){

        full = false;
        peekbuff.clear();
        char ch;
        while(in().get(ch) && (ch!=';' && ch!='\n' ));
        in().putback(ch);

    }

