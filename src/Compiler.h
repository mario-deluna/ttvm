//
//  Compiler.hpp
//  ttvm
//
//  Created by Mario Döring on 21.06.18.
//

#ifndef Compiler_hpp
#define Compiler_hpp

#include <string>
#include <vector>
#include <unordered_map>

#include "Lexer.hpp"
#include "Log.h"

class InstructionTextCompiler
{
    const std::string _text;
    
    std::string _last_error = "";
    
    // instructions
    std::vector<int> _instructions;
    int _instruction_p = 0;
    
    // tokens
    TokenCollection _tokens;
    int _token_itp = 0;
    
    // labels
    std::unordered_map<std::string, int> _label_map;
    
    // macros
    std::unordered_map<std::string, TokenCollection> _macros;
    bool parse_macro(Token token);
    
    void add_instruction(const int instruction);
    
public:
    inline InstructionTextCompiler(const std::string &text) : _text(text) {}
    
    bool compile();
    
    int get_program_pointer(const std::string label);
    bool has_program_pointer(const std::string label);
    int get_program_main_pointer();
    
    inline std::vector<int> get_instructions() {
        return _instructions;
    }
    
    inline std::string get_last_error() {
        return _last_error;
    }
};

#endif /* Compiler_hpp */
