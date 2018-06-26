//
//  VM.cpp
//  ttvm
//
//  Created by Mario Döring on 20.06.18.
//

#include "VM.h"
#include "Opcodes.h"
#include "Log.h"

#include <unistd.h>

#define TTVMPUSH(v) _stack[++_stack_pointer] = v
#define TTVMCURR _stack[_stack_pointer]
#define TTVMPOP _stack[_stack_pointer--]
#define TTVMNINST _instructions[_instruction_pointer++]

void TTVM::execute()
{
    int i1, i2, i3, i4, i5, i6, i7, i8;
    
    do
    {
        switch (TTVMNINST)
        {
            /**
             * Exit the execution
             */
            case TTVMI_HALT: return;
            
            /**
             * Print
             */
            case TTVMI_PRINT:
                printf("%c", TTVMPOP);
            break;
                
            /**
             * Print int
             */
            case TTVMI_PRINTI:
                printf("%d", TTVMPOP);
            break;
                
            /**
             * Jumping
             */
            case TTVMI_JUMP:
                i1 = TTVMNINST;
                _instruction_pointer = i1;
            break;
                
            /**
             * Duplicate
             */
            case TTVMI_DUP:
                i1 = TTVMCURR;
                TTVMPUSH(i1);
            break;
                
            /**
             * Sleep
             */
            case TTVMI_USLEEP:
                usleep(TTVMPOP);
            break;
                
            /**
             * Push a constant int 32
             */
            case TTVMI_CINT:
                TTVMPUSH(TTVMNINST);
            break;
                
            /**
             * Add two ints 32
             */
            case TTVMI_ADD_INT:
                i1 = TTVMPOP;
                i2 = TTVMPOP;
                TTVMPUSH(i1 + i2);
            break;
                
            /**
             * Die
             */
            default: ERR("BAD OPCODE – EXIT") return;
        }
        
    } while(1);
}
