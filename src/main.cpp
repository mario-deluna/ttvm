/**
 * TTVM
 *
 * A stupid simple stack vm to learn how stuff works.
 */
#include <iostream>
#include <string>

#include "Log.h"
#include "Opcodes.h"
#include "VM.h"

/**
 * .....
 */
int main(int argc, char *argv[])
{
    if (argv[1])
    {
        if (strcmp(argv[1], "compile") == 0) {
            printf("compile");
        } else if (strcmp(argv[1], "exec") == 0) {
            printf("execute");
        }
        //printf("%s", argv[1]);
    }
    return 0;
    int i[] = {
        TTVMI_CI32, 0x54,
        TTVMI_PRINT,
        TTVMI_CI32, 0x54,
        TTVMI_PRINT,
        TTVMI_CI32, 0x0A,
        TTVMI_PRINT,
        TTVMI_CI32, 1,
        TTVMI_CI32, 1,
        TTVMI_ADD_I32,
        TTVMI_DUP,
        TTVMI_PRINTI,
        TTVMI_CI32, 0x0A,
        TTVMI_PRINT,
        TTVMI_JUMP, 11,
        TTVMI_HALT
    };
    
    Program *program = new Program(i, 0);
    TTVM *vm = new TTVM(program);
    
    vm->execute();
    
    delete vm;
    delete program;
    
    printf("DONE\n");
    
    return 0;
}
