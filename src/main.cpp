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

void execute(const std::string &filename)
{
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    
    if (!file.is_open()) {
        ERR("Could not open executable file: " << filename);
    }
    
    file.seekg(0, std::ios::end);
    auto length = file.tellg();
    file.seekg(0);
    
    std::vector<int> instructions(length / sizeof(int), 0);
    file.read(reinterpret_cast<char*>(instructions.data()), instructions.size() * sizeof(int));
    
    // the first instruction is the entry point / main function
    int entry_point = instructions[0];
    instructions.erase(instructions.begin(), instructions.begin() + 1);
    
    // create the program and execute it
    Program *program = new Program(instructions.data(), entry_point);
    TTVM *vm = new TTVM(program);
    
    vm->execute_with_display();
    
    delete vm;
    delete program;
    
    printf("DONE\n");
}

void compile(const std::string &filename, const std::string &output, const bool run = false)
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
        
        if (!compiler.compile()) {
            ERR("Could not compile the program: " << compiler.get_last_error()); return;
        }
        
        std::ofstream fout;
        fout.open(output, std::ios::binary | std::ios::out);
        
        std::vector<int> inst = compiler.get_instructions();
        
        // write the entry point
        int entry_point = compiler.get_program_main_pointer();
        fout.write(reinterpret_cast<const char *>(&entry_point), sizeof(entry_point));
        
        // write the instructions
        fout.write(reinterpret_cast<const char *>(&inst[0]), inst.size() * sizeof(int));
        fout.close();
    }
    // hmmmm
    else
    {
        ERR("Unknown file given, double check the file extension.");
    }
    
    // run afterwards
    if (run) execute(output);
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
            
            compile(filename, output, true);
            
        } else if (strcmp(argv[1], "exec") == 0) {
            
            std::string filename(argv[2]);
            
            execute(filename);
        } else {
            ERR("Invalid method.");
        }
    } else {
        ERR("No argument given! You can run: 'ttvm compile' or 'ttvm exec'");
    }
    
    return 0;
}
