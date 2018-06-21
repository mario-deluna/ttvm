//
//  Opcode.hpp
//  ttvm
//
//  Created by Mario Döring on 20.06.18.
//

#ifndef Opcode_hpp
#define Opcode_hpp

enum {
    TTVMI_HALT = 0,         // exit
    TTVMI_PRINT = 1,        // print the ascii char
    TTVMI_PRINTI = 2,       // print the int
    TTVMI_JUMP = 3,         // Jump around
    TTVMI_DUP = 4,          // duplicate
    
    TTVMI_CI32 = 10,        // set int 32
    
    TTVMI_ADD_I32 = 20       // add to numbers
};

#endif /* Opcode_hpp */
