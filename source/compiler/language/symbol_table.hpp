//
//  symbol_table.hpp
//  language
//
//  Created by Daniel Rehman on 1908191.
//  Copyright © 2019 Daniel Rehman. All rights reserved.
//

#ifndef symbol_table_hpp
#define symbol_table_hpp

#include "arguments.hpp"
#include "nodes.hpp"
#include "llvm/IR/ValueSymbolTable.h"
#include "llvm/IR/IRBuilder.h"
#include <iostream>


using nat = size_t;

struct stack_frame {
    llvm::ValueSymbolTable llvm;
    std::vector<nat> indicies = {};   // index into master.   
};

struct signature_entry {
    expression signature = {};
    abstraction_definition definition = {};
    std::vector<nat> parents = {}; // index into master.
}; 

class symbol_table {
public:    
    std::vector<struct signature_entry> master = {};
    std::vector<struct stack_frame> frames = {};
    std::vector<nat> blacklist = {}; // index into master.
    
    void push(llvm::ValueSymbolTable llvm) {frames.push_back({llvm, {}});}    
    void pop() {frames.pop_back();}
    
    
    
    void update() {
        /// job:
        /*
         for each stackframe, 
         
         for each llsymbol in that sf's LLST, 
         
         if that llsymbol is not in our indexed stackframe, 
         (which we will determine by indexing each stackframe index into the master, 
         and checking if the symbol stringified versions match...                           TODO:  we need to code a fucntion which takes a typical llvm function signture, such as:       void @f(i32 %x, i32 %y)     and convert it into a n3zqx2l signtaure,     in this case:        (f ((x) `i32`)  ((y) `i32`)) () (_type)   
         )
         then we will create a new entry in master, (push_back(something)), 
         and then fill its data with what we know to be the key and value of the thing we found from searching the LLST.
         
         
         */
        
        for (auto frame : frames) {
            for (auto i = frame.llvm.begin(); i != frame.llvm.end(); i++) { 
                auto key = i->getKey();
                auto value = i->getValue();
                
            }
        }
    }
    
    
    std::vector<nat>& top() {
        update();
        return frames.back().indicies;        
    }
    
    
    expression& lookup(nat index) {
        update();
        return master[index].signature;        
    }
    
    
    
    
    
    void define(expression signature, abstraction_definition definition, 
                nat stack_frame_index, std::vector<nat> parents = {} ) {
        
        /// if in blacklist, 
        /// remove from blacklist.
        
        frames[frames.size() - 1 - stack_frame_index].indicies.push_back(master.size()); 
        master.push_back({signature, definition, parents});
    }
    
    void undefine(nat signature_index, nat stack_frame_index) {
        blacklist.push_back(signature_index);
        //frames[frames.size() - 1 - stack_frame_index].indicies.push_back(master.size());  // TODO: make this into a    "remove_if(erase(signature_index));"
        
    }
    
    void disclose(nat desired_signature, expression new_signature, 
                  nat source_abstraction, nat destination_frame) {
        
    }
    
    symbol_table(llvm::Module* module, struct file file, std::vector<expression> builtins) {
        push(module->getValueSymbolTable());
        
        master.push_back({}); // the null entry. a type of 0 means it has no type.
        
        for (auto signature : builtins) {
            master.push_back({signature, {}, {}});
        }
        
    }
    
    void print_stack() {
        std::cout << "\n\n---------------- printing MASTER stack -------------------\n\n";
        for (int i = 0; i < frames.size(); i++) {
            std::cout << "----- FRAME # " << i << " -------------------\n";
            for (int j = 0; j < frames[i].indicies.size(); j++) {
                
                std::cout << "#" << j << " : " << expression_to_string(master[frames[i].indicies[j]].signature) << "   :    [ "; 
                
                for (auto h : master[frames[i].indicies[j]].parents) {
                    std::cout << h << " ";
                } std::cout << "]\n";
            }
            std::cout << "---------------------------------------------\n\n";
        }
        std::cout << "\n\n-----------------------------------------------------------\n\n";
    }
    
    
    
    static void print_symtable(llvm::ValueSymbolTable& table) {
        std::cout << "----------------printing symbol table: -----------------\n";
        for (auto i = table.begin(); i != table.end(); i++) {
            std::cout << "key: \"" << i->getKey().str() << "\"\n";
            std::cout << "value: [[[\n\n";
            i->getValue()->print(llvm::outs());
            std::cout << "]]]\n\n"; 
            
            std::cout << "here is the result of instead using .first and .second: \n";
            std::cout << "first: \"" << i->first().str() << "\"\n";
            std::cout << "second: [[[\n\n";
            i->second->print(llvm::outs());
            std::cout << "]]] \n\n";
        }
        std::cout << "---------------------------------------------\n";
    }
    
    
    
};


#endif /* symbol_table_hpp */
