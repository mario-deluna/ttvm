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
#include <memory>

#include "Lexer.hpp"
#include "Log.h"

struct TokenCollectionReturn
{
    bool success;
    TokenCollection tokens;
    
    TokenCollectionReturn(bool success, TokenCollection tokens) :
        success(success), tokens(tokens)
    {}
};

struct TokenArgument
{
    TokenCollection tokens;
    
    TokenArgument(TokenCollection tokens) :
        tokens(tokens)
    {}
};

struct TokenMacro
{
    typedef std::vector<TokenArgument> TokenArguments;
    
    TokenArguments arguments;
    TokenCollection tokens;
    
    TokenMacro(TokenArguments arguments, TokenCollection tokens) :
        arguments(arguments), tokens(tokens)
    {}
};

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
    Token token_at(int index);
    int find_next_token_index(int type);
    
    // labels
    std::unordered_map<std::string, int> _label_map;
    
    // macros
    std::map<std::string, TokenMacro> _macros;
    bool parse_macro_definition(Token token);
    bool parse_macro_call(Token token);
    bool is_at_macro_definition(Token token);
    TokenCollectionReturn parse_scope();
    
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
