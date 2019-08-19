//
//  builtins.hpp
//  language
//
//  Created by Daniel Rehman on 1905175.
//  Copyright © 2019 Daniel Rehman. All rights reserved.
//

#ifndef builtins_hpp
#define builtins_hpp

#include "nodes.hpp"
#include <vector>

extern expression failure;

extern expression type_type;
extern expression unit_type;
extern expression none_type;
extern expression any_type;
extern expression infered_type;

extern expression application_type;
extern expression abstraction_type;

extern expression compiletime_type;
extern expression runtime_type;

extern expression immutable_type;
extern expression mutable_type;

extern expression define_abstraction;
extern expression undefine_abstraction;
extern expression disclose_abstraction;

extern expression all_signature;

extern std::vector<expression> builtins;



#endif /* builtins_hpp */
