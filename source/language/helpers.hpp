//
//  helpers.hpp
//  language
//
//  Created by Daniel Rehman on 1908213.
//  Copyright © 2019 Daniel Rehman. All rights reserved.
//

#ifndef helpers_hpp
#define helpers_hpp

#include "analysis_ds.hpp"
#include "parser.hpp"
#include "llvm/IR/LLVMContext.h"
#include "llvm/AsmParser/Parser.h"
#include "llvm/IR/ModuleSummaryIndex.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/IR/ValueSymbolTable.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Function.h"

#include <cstdlib>
#include <iostream>
#include <sstream>

////////////////// CSR comparison functions ///////////////////////////

bool subexpression(const symbol& s);
bool identifier(const symbol& s);
bool llvm_string(const symbol& s);

bool are_equal_identifiers(const symbol &first, const symbol &second);
bool symbols_match(symbol first, symbol second);
bool expressions_match(expression first, expression second);

////////////////////////////////// LLVM IR builder helpers ////////////////////////////////

void append_return_0_statement(llvm::IRBuilder<> &builder, llvm::LLVMContext &context); 
void call_donothing(llvm::IRBuilder<> &builder, const std::unique_ptr<llvm::Module> &module);
llvm::Function* create_main(llvm::IRBuilder<>& builder, llvm::LLVMContext& context, const std::unique_ptr<llvm::Module>& module);


/////////////////////////////////////// CSR SUITE ///////////////////////////////////////////

resolved_expression_list resolve_expression_list(expression_list given, llvm::Function*& function,state& state, flags flags); // interface function:
resolved_expression resolve_expression(expression given, llvm::Function*& function, state& state, flags flags);
resolved_expression resolve(expression given, llvm::Function*& function,nat& index, const nat depth, const nat max_depth, state& state, flags flags);

#endif /* helpers_hpp */
