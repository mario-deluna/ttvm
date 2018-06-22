//
//  Compiler.cpp
//  ttvm
//
//  Created by Mario Döring on 21.06.18.
//

#include "Compiler.h"
#include "Opcodes.h"
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
        {TOKEN_LABEL, "^@[a-zA-z0-9]+", },
        {TOKEN_INSTRUCTION, "^\\.[A-z0-9_]+"},
        {TOKEN_HEX, "^0x[0-9A-Z]+"},
        {TOKEN_INT, "^[+-]?[0-9]+"},
    });
    
    TokenCollection tokens = lexer.tokenize(_text);
    
    for (auto &token : tokens)
    {
        switch (token.type) {
            case TOKEN_INSTRUCTION:
                if (token.content == ".CINT") {
                    _instructions.push_back(TTVMI_CINT);
                } else if (token.content == ".PRINT") {
                    _instructions.push_back(TTVMI_PRINT);
                } else if (token.content == ".HALT") {
                    _instructions.push_back(TTVMI_HALT);
                }
                break;
            case TOKEN_HEX:
                _instructions.push_back(std::stoul(token.content, nullptr, 16));
                break;
        }
    }
    
    return true;
}
