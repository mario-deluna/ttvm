//
//  Lexer.hpp
//  ttvm
//
//  Created by Mario Döring on 21.06.18.
//

#ifndef Lexer_hpp
#define Lexer_hpp

#include <string>
#include <map>
#include <vector>

#include "Log.h"

struct Token
{
    int type;
    std::string content;
    
    unsigned int line;
    
    inline Token(const int type, const std::string content, const unsigned int line) :
        type(type), content(content), line(line)
    {}
};

typedef std::vector<Token> TokenCollection;

class Lexer
{
    // a map of regular expression strings and their type assignment
    std::map<int, std::string> _token_types;
    
public:
    inline Lexer(std::map<int, std::string> token_types) :
        _token_types(token_types)
    {}
    
    TokenCollection tokenize(const std::string &code);
};

#endif /* Lexer_hpp */
