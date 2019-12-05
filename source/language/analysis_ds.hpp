#ifndef analysis_ds_hpp
#define analysis_ds_hpp

#include "arguments.hpp"
#include "nodes.hpp"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"

using llvm_modules = std::vector<std::unique_ptr<llvm::Module>>;
using llvm_module = std::unique_ptr<llvm::Module>;

struct program_data {
    file file;
    llvm::Module* module;
    llvm::IRBuilder<>& builder;
};

struct symbol_table;

struct state {
    symbol_table& stack;
    program_data& data;
};

struct resolved_expression_list;

struct resolved_expression {
    nat index = 0;
    std::vector<resolved_expression_list> args = {};
    bool error = false;
    llvm::Type* llvm_type = nullptr;
    expression signature = {};
    llvm::Value* constant = {};
};

struct resolved_expression_list {    
    std::vector<resolved_expression> list = {};
    bool error = false;
};

#endif /* analysis_ds_hpp */
