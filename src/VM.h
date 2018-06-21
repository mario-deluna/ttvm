//
//  VM.hpp
//  ttvm
//
//  Created by Mario Döring on 20.06.18.
//

#ifndef VM_hpp
#define VM_hpp

#include "Program.h"

#define TTVM_STACK_SIZE 500

class TTVM
{
    int *_instructions;
    unsigned int _instruction_pointer;
    
    int *_stack;
    int _stack_pointer;
    
public:
    inline TTVM(Program *program)
    {
        _instructions = program->instructions;
        _instruction_pointer = program->entry_point;
        _stack = new int[TTVM_STACK_SIZE];
        _stack_pointer = -1;
    }

    inline ~TTVM()
    {
        delete[] _stack;
    }
    
    void execute();
};

#endif /* VM_hpp */
