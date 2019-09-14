//
//  llvm_parser.cpp
//  language
//
//  Created by Daniel Rehman on 1909146.
//  Copyright © 2019 Daniel Rehman. All rights reserved.
//

#include "llvm_parser.hpp"

std::string random_string() {
    static int num = 0;
    std::stringstream stream;
    stream << std::hex << rand();
    return std::string(stream.str()) + std::to_string(num++);
}

bool parse_llvm_string_as_instruction(std::string given, llvm::Function*& original, state& state, llvm::SMDiagnostic& errors) {
    
    ///TODO: this deletes the symbol table already inserted for the given function... 
    /// we need to update it to the new symbol table.
    /// ... maybe we should just not import the llvm symbol table, (or, ie, have 
    /// a function update() which takes a llvm sybol tbale.
    
    ///important note about this function:     
    /// it leaves artifacts in the function after use, which must be removed: 
    /// any occurence of a unreachable statement which is directly preceeded by 
    /// a llvm.do_nothing() call, should be removed before execution of the function.  
    
    std::string body = "";
    original->print(llvm::raw_string_ostream(body) << "");    
    body.pop_back(); // delete the newline
    body.pop_back(); // delete the close brace
    body += given + "\n" "call void @llvm.donothing()" "\n" "unreachable" "\n" "}" "\n";
    
    const std::string current_name = original->getName();
    original->setName("_anonymous_" + random_string());
    llvm::MemoryBufferRef reference(body, "<llvm-string>");
    llvm::ModuleSummaryIndex my_index(true);
    if (llvm::parseAssemblyInto(reference, state.data.module, &my_index, errors)) {        
        original->setName(current_name);
        return false;
    } else {
        original->getBasicBlockList().clear();
        original = state.data.module->getFunction(current_name);
        return true;
    }
}

bool parse_llvm_string_as_function(std::string given, state& state, llvm::SMDiagnostic& errors) {
    llvm::MemoryBufferRef reference(given, "<llvm-string>");
    llvm::ModuleSummaryIndex my_index(true);
    return !llvm::parseAssemblyInto(reference, state.data.module, &my_index, errors);        
}

llvm::Type* parse_llvm_string_as_type(std::string given, state& state, llvm::SMDiagnostic& errors) {
    return llvm::parseType(given, errors, *state.data.module);
}

void print_llvm_parse_error(const llvm::SMDiagnostic &errors, state &state) {
    std::cout << "llvm: ";      // TODO: make this have color!            
    errors.print(state.data.file.name.c_str(), llvm::errs());
}

expression parse_llvm_string(expression given, llvm::Function*& function, std::string llvm_string, nat& pointer, state& state, flags flags) {
    llvm::SMDiagnostic instruction_errors, function_errors, type_errors;
    
    if (not flags.is_parsing_type 
        and (parse_llvm_string_as_function(llvm_string, state, function_errors) 
             or parse_llvm_string_as_instruction(llvm_string, function, state, instruction_errors))) { 
            return expression {{{given.symbols[pointer++].llvm}}, intrin::unit};
            
        } else if (auto llvm_type = parse_llvm_string_as_type(llvm_string, state, type_errors)) {
            expression solution {{{given.symbols[pointer++].llvm}}, intrin::unit};
            solution.llvm_type = llvm_type;            
            return solution;
            
        } else {
            print_llvm_parse_error(function_errors, state);
            print_llvm_parse_error(instruction_errors, state);        
            print_llvm_parse_error(type_errors, state); 
            return failure;
        }
}

// might be useful, for when we are given .ll files? that sounds cool.
void interpret_file_as_llvm_string(const struct file &file, state &state) { // test, by allowing some llvm random string to be parsed into the file:
    llvm::SMDiagnostic errors;
    if (parse_llvm_string_as_function(file.text, state, errors)) {
        std::cout << "success.\n";
        
    } else {
        std::cout << "failure.\n";
        errors.print("llvm string program:", llvm::errs());
        abort();
    }
}
