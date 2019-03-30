//
//  parser.hpp
//  language
//
//  Created by Daniel Rehman on 1901126.
//  Copyright © 2019 Daniel Rehman. All rights reserved.
//

#ifndef parser_hpp
#define parser_hpp

#include "nodes.hpp"
#include "preprocessor.hpp"

#include "llvm/IR/LLVMContext.h"

#include <string>

translation_unit parse(struct preprocessed_file text, llvm::LLVMContext& context);

#endif /* parser_hpp */
