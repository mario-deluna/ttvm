/**
 * TTVM
 *
 * A stupid simple stack vm to learn how stuff works.
 */
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

#include "Log.h"
#include "Opcodes.h"
#include "Compiler.h"
#include "VM.h"

void compile(const std::string &filename, const std::string &output)
{
    // read the file into memory
    std::ifstream input_stream(filename);
    
    // error?
    if (!input_stream) { ERR("Could not read file: " + filename); return; }
    
    // read the buffer into the string stream
    std::stringstream file_string_stream;
    file_string_stream << input_stream.rdbuf();
    
    // close the streams
    input_stream.close();
    
    // make a string out of it
    std::string input = file_string_stream.str();
    
    // check the file name to determine
    // what type of file we want to compile
    std::string fileext = filename.substr(filename.size() - 3);
    
    // TT Instruction file
    if (fileext == "tti")
    {
        InstructionTextCompiler compiler = InstructionTextCompiler(input);
        
        compiler.compile();
        
        int *i = compiler.get_instructions().data();
    }
    // hmmmm
    else
    {
        ERR("Unknown file given, double check the file extension.");
    }
}

void execute()
{
    int i[] = {
        TTVMI_CINT, 0x54,
        TTVMI_PRINT,
        TTVMI_CINT, 0x54,
        TTVMI_PRINT,
        TTVMI_CINT, 0x0A,
        TTVMI_PRINT,
        TTVMI_CINT, 1,
        TTVMI_CINT, 1,
        TTVMI_ADD_INT,
        TTVMI_DUP,
        TTVMI_PRINTI,
        TTVMI_CINT, 0x0A,
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
}

/**
 * .....
 */
int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        if (strcmp(argv[1], "compile") == 0)
        {
            if (argc < 3) {
                ERR("Not enough arguments: ttvm compile <input> <output>"); return 0;
            }
            
            std::string filename(argv[2]);
            std::string output(argv[3]);
            
            compile(filename, output);
            
        } else if (strcmp(argv[1], "exec") == 0) {
            execute();
        } else {
            ERR("Invalid method.");
        }
    } else {
        ERR("No argument given! You can run: 'ttvm compile' or 'ttvm exec'");
    }
    
    return 0;
}
