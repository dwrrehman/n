//
//  codegen.hpp
//  language
//
//  Created by Daniel Rehman on 1903085.
//  Copyright © 2019 Daniel Rehman. All rights reserved.
//

#ifndef codegen_hpp
#define codegen_hpp

#include "analysis.hpp"

#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"

std::unique_ptr<llvm::Module> generate(struct action_tree tree, std::string filename, llvm::LLVMContext &context);

#endif /* codegen_hpp */
