//
//  Compiler.cpp
//  ttvm
//
//  Created by Mario Döring on 21.06.18.
//

#include "Compiler.h"
#include "Opcodes.h"

#define PROGRAM_MAIN_LABEL "@main"

enum {
    TOKEN_LABEL = 0,
    TOKEN_INSTRUCTION = 1,
    TOKEN_HEX = 2,
    TOKEN_INT = 3,
    
    TOKEN_OPEN = 100,
    TOKEN_CLOSE = 101,
    TOKEN_COMMA = 102,
    
    TOKEN_MACRO = 205,
    TOKEN_MACRO_END = 204,
    TOKEN_VARIABLE = 250,
    
    TOKEN_COMMENT = 500,
    
    TOKEN_UNKNOWN = 1000,
};

void InstructionTextCompiler::add_instruction(int instruction)
{
    _instructions.push_back(instruction);
    _instruction_p++;
}

bool InstructionTextCompiler::has_program_pointer(const std::string label)
{
    return _label_map.find(label) != _label_map.end();
}

int InstructionTextCompiler::get_program_pointer(const std::string label)
{
    return _label_map[label];
}

int InstructionTextCompiler::get_program_main_pointer()
{
    return get_program_pointer(PROGRAM_MAIN_LABEL);
}

bool InstructionTextCompiler::compile()
{
    _macros.clear();
    _label_map.clear();
    _instructions.clear();
    _instruction_p = 0;
    _token_itp = 0;
    
    Lexer lexer({
        {TOKEN_LABEL, "^@[a-zA-z0-9]+", },
        {TOKEN_INSTRUCTION, "^\\.[A-z0-9_]+"},
        {TOKEN_HEX, "^0x[0-9A-Z]+"},
        {TOKEN_INT, "^[+-]?[0-9]+"},
        {TOKEN_OPEN, "^\\("},
        {TOKEN_CLOSE, "^\\)"},
        {TOKEN_COMMA, "^\\,"},
        {TOKEN_MACRO_END, "^#end"},
        {TOKEN_MACRO, "^#[a-zA-z0-9]+"},
        {TOKEN_VARIABLE, "^\\$[a-zA-z0-9]+"},
        {TOKEN_COMMENT, "^\\/\\/.*"},
        {TOKEN_UNKNOWN, "^.*"},
    });
    
    _tokens = lexer.tokenize(_text);
    
    std::vector<std::string> label_strings;
    
    while(_token_itp < _tokens.size())
    {
        auto token = _tokens[_token_itp];
        
        switch (token.type) {
            case TOKEN_INSTRUCTION:
                if (token.content == ".CINT") {
                    add_instruction(TTVMI_CINT);
                } else if (token.content == ".PRINT") {
                    add_instruction(TTVMI_PRINT);
                } else if (token.content == ".PRINTI") {
                    add_instruction(TTVMI_PRINTI);
                } else if (token.content == ".HALT") {
                    add_instruction(TTVMI_HALT);
                } else if (token.content == ".JUMP") {
                    add_instruction(TTVMI_JUMP);
                } else if (token.content == ".DUP") {
                    add_instruction(TTVMI_DUP);
                } else if (token.content == ".USLEEP") {
                    add_instruction(TTVMI_USLEEP);
                } else if (token.content == ".ADD_INT") {
                    add_instruction(TTVMI_ADD_INT);
                } else if (token.content == ".STORE") {
                    add_instruction(TTVMI_STORE);
                } else if (token.content == ".LOAD") {
                    add_instruction(TTVMI_LOAD);
                } else {
                    _last_error = "Invalid instruction given '" + token.content + "' at line " + std::to_string(token.line + 1);
                    return false;
                }
                break;
            case TOKEN_HEX:
                add_instruction(std::stoul(token.content, nullptr, 16));
                break;
            case TOKEN_INT:
                add_instruction(std::stoi(token.content));
                break;
            case TOKEN_LABEL:
                // if the last instruction is a jump this label is the location we want to jump to
                // because we want to be able to jump to future labels we store the vector index to the label
                // strings and have to reitarate over them at the end.
                if (_instruction_p != 0 && _instructions.back() == TTVMI_JUMP) {
                    label_strings.push_back(std::string(token.content));
                    add_instruction(label_strings.size() - 1);
                } else {
                    // otherwise this label marks a instruction pointer
                    _label_map[token.content] = _instruction_p;
                }
                
                break;
            case TOKEN_MACRO:
                
                if (!parse_macro(token)) {
                    _last_error = "Macro '" + token.content + "' failed at line " + std::to_string(token.line + 1) + " error: " + _last_error;
                    return false;
                }
                
                break;
            
            case TOKEN_COMMENT:
                // its a comment ..
                break;
            default:
                _last_error = "Syntax error invalid token '" + token.content + "' at line " + std::to_string(token.line + 1);
                return false;
                break;
        }
        
        _token_itp++;
    }
    
    // insert the correct pointer positions at all jump instructions
    int last_inst = -1;
    for (auto &instruction : _instructions)
    {
        if (last_inst == TTVMI_JUMP) {
            if (!has_program_pointer(label_strings[instruction])) {
                _last_error = "Could not resolve instruction pointer label '" + label_strings[instruction] + "'.";
                return false;
            }
            
            instruction = get_program_pointer(label_strings[instruction]);
        }
            
        last_inst = instruction;
    }
    
    // do we have a main pointer? if not we failed
    if (!has_program_pointer(PROGRAM_MAIN_LABEL)) {
        _last_error = "The program seems not to have a main entry point.";
        return false;
    }
    
    return true;
}

bool InstructionTextCompiler::parse_macro(Token token)
{
    auto name = token.content;
    
    // new macro definition?
    if (_macros.find(name) == _macros.end())
    {
        int i = _token_itp;
        int endpos = -1;
        
        TokenCollection macro_tokens;
        
        while(i < _tokens.size() || endpos > -1)
        {
            macro_tokens.push_back(_tokens[i]);
            
            if (_tokens[i].type == TOKEN_MACRO_END) {
                endpos = i; break;
            }
            
            i++;
        }
        
        // no end node?
        if (endpos == -1) {
            _last_error = "Did you forgot to close a macro definition? Because we can't find the end.";
            return false;
        }
        
        // remove the macro tokens from the main set
        _tokens.erase(_tokens.begin(), _tokens.end());
        //_tokens.erase(_tokens.begin() + _token_itp, _tokens.begin() + _token_itp + macro_tokens.size());
        
    }
    // macro call
    else
    {
        
    }
    
    return true;
}
