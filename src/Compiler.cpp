//
//  Compiler.cpp
//  ttvm
//
//  Created by Mario Döring on 21.06.18.
//

#include "Compiler.h"

#include <iterator>
#include <iostream>
#include <string>
#include <regex>
#include <list>
#include <map>

#include "Lexer.hpp"

enum {
    TOKEN_LABEL = 0,
    TOKEN_INSTRUCTION = 1,
    TOKEN_HEX = 2,
    TOKEN_INT = 3,
};

bool InstructionTextCompiler::compile()
{
    Lexer lexer({
        {TOKEN_LABEL, "@[a-zA-z0-9]+", },
        {TOKEN_INSTRUCTION, "\\.[A-z0-9_]+"},
        {TOKEN_HEX, "0x[0-9A-Z]+"},
        {TOKEN_INT, "[+-]?[0-9]+"},
    });
    
    TokenCollection tokens = lexer.tokenize(_text);
    
    
    
//    // define list of patterns
//    std::map<std::string,std::string> patterns {
//        {"@[a-zA-z0-9]+", "LABEL"},
//        {"\\.[A-z0-9_]+", "INSTRUCTION"},
//        {"0x[0-9A-Z]+", "HEX"},
//        {"[+-]?[0-9]+", "INT"},
//    };
//
//    // storage for results
//    std::map<size_t, std::pair<std::string,std::string>> matches;
//
//    for (auto pat = patterns.begin(); pat != patterns.end(); ++pat)
//    {
//        std::regex r(pat->first);
//        auto words_begin = std::sregex_iterator(_text.begin(), _text.end(), r);
//        auto words_end   = std::sregex_iterator();
//
//        for (auto it = words_begin; it != words_end; ++it) {
//            matches[it->position()] = make_pair(it->str(), pat->second);
//        }
//    }
//
//    for (auto match = matches.begin(); match != matches.end(); ++match) {
//        LOG(match->second.first << " " << match->second.second);
//    }
    
    return true;
}
