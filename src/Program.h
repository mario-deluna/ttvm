//
//  Program.hpp
//  ttvm
//
//  Created by Mario Döring on 20.06.18.
//

#ifndef Program_hpp
#define Program_hpp

struct Program
{
    int* instructions;
    unsigned int entry_point;
    
    inline Program(int *instructions, unsigned int entry_point) :
        instructions(instructions),
        entry_point(entry_point)
    {}
};

#endif /* Program_hpp */
