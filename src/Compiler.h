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

#include "Log.h"

class InstructionTextCompiler
{
    const std::string _text;
    
    std::vector<int> _instructions;
    
public:
    inline InstructionTextCompiler(const std::string &text) : _text(text) {}
    
    bool compile();
    
    inline std::vector<int> get_instructions() {
        return _instructions;
    }
};

#endif /* Compiler_hpp */
