//
//  Compiler.cpp
//  ttvm
//
//  Created by Mario Döring on 21.06.18.
//

#include "Compiler.h"
#include "Opcodes.h"
#include "Lexer.hpp"

#define PROGRAM_MAIN_LABEL "@main"

enum {
    TOKEN_LABEL = 0,
    TOKEN_INSTRUCTION = 1,
    TOKEN_HEX = 2,
    TOKEN_INT = 3,
    
    TOKEN_COMMENT = 500,
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
    _label_map.clear();
    _instructions.clear();
    _instruction_p = 0;
    
    Lexer lexer({
        {TOKEN_LABEL, "^@[a-zA-z0-9]+", },
        {TOKEN_INSTRUCTION, "^\\.[A-z0-9_]+"},
        {TOKEN_HEX, "^0x[0-9A-Z]+"},
        {TOKEN_INT, "^[+-]?[0-9]+"},
        {TOKEN_COMMENT, "^\\/\\/.*"}
    });
    
    TokenCollection tokens = lexer.tokenize(_text);
    
    std::vector<std::string> label_strings;
    
    for (auto &token : tokens)
    {
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
                
            case TOKEN_COMMENT:
                // its a comment ..
                break;
            default:
                _last_error = "Syntax error invalid token '" + token.content + "' at line " + std::to_string(token.line + 1);
                return false;
                break;
        }
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
