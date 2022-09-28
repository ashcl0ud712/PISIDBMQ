//
//  mHeaderBase.hpp
//  PISIDBMQ
//
//  Created by Asoby ‎‎ on 28.09.2022.
//

#ifndef mHeaderBase_hpp
#define mHeaderBase_hpp

#include <stdio.h>
#include "../../lib/tools/tools.hpp"
#include "../../lib/mLogger/mLogger.hpp"

class mHeaderBase{
    std::string _name;
    std::string _value;
    
public:
    mHeaderBase(std::string name, std::string value): _name(name), _value(value) {};
    std::string getName(){ return _name; }
    std::string getValue(){ return _value; }
    std::string String(){ return _name + " = " + _value; }
};
#endif /* mHeaderBase_hpp */
