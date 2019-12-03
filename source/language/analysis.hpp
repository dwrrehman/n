//
//  analysis.hpp
//  language
//
//  Created by Daniel Rehman on 1901314.
//  Copyright © 2019 Daniel Rehman. All rights reserved.
//

#ifndef analysis_hpp
#define analysis_hpp

#include "analysis_ds.hpp"

llvm_module analyze(expression_list unit, const file& file, llvm::LLVMContext& context);

#endif /* analysis_hpp */
