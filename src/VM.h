//
//  VM.hpp
//  ttvm
//
//  Created by Mario Döring on 20.06.18.
//

#ifndef VM_hpp
#define VM_hpp

#include "Program.h"
#include "Display.hpp"

#define TTVM_STACK_SIZE 512
#define TTVM_MEMORY_SIZE 16384

class TTVM
{
    int *_instructions;
    unsigned int _instruction_pointer;
    
    int *_stack;
    int _stack_pointer;
    
    int *_memory;
    
    Display *display;
    
public:
    inline TTVM(Program *program)
    {
        _instructions = program->instructions;
        _instruction_pointer = program->entry_point;
        _stack = new int[TTVM_STACK_SIZE];
        _stack_pointer = -1;
        _memory = new int[TTVM_MEMORY_SIZE];
    }

    inline ~TTVM()
    {
        delete[] _stack;
    }
    
    void execute();
    void execute_with_display();
};

#endif /* VM_hpp */
