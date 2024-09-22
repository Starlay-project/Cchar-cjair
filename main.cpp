 #include <iostream>
#include <string>
#include <vector>
#include<sstream>
#include<fstream>
#include <cctype>
#include"compiler.cpp"
using namespace std;
enum tokentype {
    keyword,
    identifier,
    number,
    function,
    operator_token,
    newline,
    programeType,
     Accessner,
    EFO2
};

struct token {
    tokentype type;
    std::string value;
};

std::vector<token> lexer(const std::string& v2) {
    std::vector<token> tokens;
    int cursor = 0;

    while (cursor < v2.length()) {
        char in = v2[cursor];

        if (isspace(in)) {
            cursor++;
            continue;
        }

        if (isalpha(in)) {
            std::string word;
            while (isalpha(in) && cursor < v2.length()) {
                word += in;
                cursor++;
                if (cursor < v2.length()) {
                    in = v2[cursor];
                }
            }

            if (word == "return" || word == "gobul"||word == "let"||word == "Gobul"||word == "printnl") {
                tokens.push_back({keyword, word});
            } else if (word == "fn") {
                tokens.push_back({function, word});
            }  else if(word == ".gobul"){
                  tokens.push_back({keyword, word});
            }
            else if(word == "Stp"){
                string stp = "Static";
                tokens.push_back({programeType,stp});
            }
            else {
                tokens.push_back({identifier, word});
            }
            continue;
        }

        if (isdigit(in)) {
            std::string num;
            while (isdigit(in) && cursor < v2.length()) {
                num += in;
                cursor++;
                if (cursor < v2.length()) {
                    in = v2[cursor];
                }
            }
            tokens.push_back({number, num});
            continue;
        }

        if (in == '+' || in == '-' || in == '*' || in == '/' || in == '=' || in == '<' || in == '>'||in == '{'||in =='}'
        ||in == '('||in == ')') {
            std::string op(1, in);
            cursor++;
            
            tokens.push_back({operator_token, op});
            continue;
        }
        string v= ";";
         if(in == ';'){
                 
                 tokens.push_back({newline, v});
            }
            if( in == '.'){
                v.clear();
                v = '.';
                tokens.push_back({Accessner, v});
            }
         
        

        cursor++;
    }

    return tokens;
}
void compiler(string &v){
     std::vector<token> tokens = lexer(v);

    for (const auto& tok : tokens) {
        std::cout << "Type: " << (tok.type == keyword ? "keyword" :tok.type == newline?"newline":tok.type == Accessner?"accessner": tok.type == identifier ? "identifier" :tok.type == programeType?"programmeType": tok.type == number ? "number" : tok.type == function ? "function"  :  "operator") << ", Value: " << tok.value << std::endl;
    }
}
// get_Tokens(vector<token> tokens = lexer(v));

int main(int argc,char* argv[]) {
if(argc !=2){
        cerr << " Error C3789 common: CRITICAL SYSTEM FAILURE! Buffer Overflow Detected! "
              << "Hello, I think I see some segmentation faults and memory leaks in compiling. "
              << "To avoid catastrophic failure, do not proceed with <./"
              << "exe ./file char file>. Immediate action required!!"<<endl;
        
        return EXIT_FAILURE;
    }
    string content;
        {
        fstream input(argv[1],ios::in);
        stringstream src;
        src << input.rdbuf();
        content = src.str();
        }
        compiler(content);
    return 0;
}
    //std::string code = "return gobul myVar 123 sin + - * / = < >";
