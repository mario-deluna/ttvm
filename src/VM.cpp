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
#include <thread>


#define TTVMPUSH(v) _stack[++_stack_pointer] = v
#define TTVMCURR _stack[_stack_pointer]
#define TTVMPOP _stack[_stack_pointer--]
#define TTVMNINST _instructions[_instruction_pointer++]
#define CONTROL_SP assert(_stack_pointer >= 0)

void TTVM::execute_with_display()
{
    display = new Display();
    
    std::thread pthread(&TTVM::execute, this);
    
    display->start();
    
    // We come to this point when the user closes the window
    // kill the display
    delete display;
    
    // wait for the programm to finish
    pthread.join();
}

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
                CONTROL_SP;
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
             * Stores a value
             */
            case TTVMI_STORE:
                i1 = TTVMPOP; // value
                i2 = TTVMPOP; // address
                _memory[i2] = i1;
            break;
                
            /**
             * Loads a value
             */
            case TTVMI_LOAD:
                i1 = TTVMPOP; // address
                TTVMPUSH(_memory[i1]);
            break;
                
            /**
             * Die
             */
            default: ERR("BAD OPCODE – EXIT") return;
        }
        
    } while(1);
}
