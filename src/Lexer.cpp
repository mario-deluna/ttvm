//
//  Lexer.cpp
//  ttvm
//
//  Created by Mario Döring on 21.06.18.
//

#include "Lexer.hpp"

#include <regex>

// this lexer does not care a little bit about performance
TokenCollection Lexer::tokenize(const std::string &code)
{
    TokenCollection tokens;
    
    unsigned int length = code.length();
    unsigned int p = 0;
    unsigned int l = 0;
    
    while (p < length)
    {
        std::string remaining = code.substr(p);
        unsigned int ip = p;
        
        // linebreak?
        if (remaining[0] == '\n') {
            l++; p++; continue;
        }
        
        // space?
        if (remaining[0] == ' ') {
            p++; continue;
        }
        
        // tap?
        if (remaining[0] == '\t') {
            p++; continue;
        }
        
        for (auto const& type : _token_types)
        {
            std::regex pattern(type.second);
            std::smatch match;
            
            if (std::regex_search(remaining, match, pattern) && match.size() > 0) {
                tokens.push_back(Token(type.first, match.str(0), l));
                p += match.str(0).length();
                break;
            }
        }
        
        if (ip == p) {
            p++;
        }
    }
    
    return tokens;
}
