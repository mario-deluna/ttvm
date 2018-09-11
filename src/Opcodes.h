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
    TTVMI_USLEEP = 5,       // sleep for microseconds
    
    TTVMI_CINT = 10,        // set int 32
    
    TTVMI_ADD_INT = 20,     // add to numbers
    
    TTVMI_STORE = 30,        // store something in memory
    TTVMI_LOAD = 31,          // load something in memory
    
    TTVM_DISP_PX = 50,       // display set pixel
};

#endif /* Opcode_hpp */
