//
//  mMessage.hpp
//  PISIDBMQ
//
//  Created by Asoby ‎‎ on 28.09.2022.
//

#ifndef mMessage_hpp
#define mMessage_hpp

#include <stdio.h>
#include "../../lib/tools/tools.hpp"
#include "../../lib/mLogger/mLogger.hpp"
#include "../mHeaderBase/mHeaderBase.hpp"
class mMessage{
    int _offset;
    std::vector<mHeaderBase> Headers;
    std::string key;
    std::string value;
    
public:
    mMessage(mHeaderBase header, std::string _key, std::string _value):
        key(_key),
        value(_value){
        Headers.push_back(header);
        }
    mMessage() {}

    bool isValid(){
        if(key.empty() && value.empty()){
            return false;
        }
        else return true;
    }
    std::string Value(){ return value; }
    std::string Key() { return key; }
    void AddHeader(mHeaderBase header) { Headers.push_back(header); }
    std::string ToString(){
        std::string sheader = "";
        for(mHeaderBase h : Headers){
            std::string s = h.getName();
            s+="="+h.getValue();
            s+=";\n";
            sheader+=s;
        }
        return sheader + value;
    }
    
    void SetOffset(int offset){ offset = _offset; }
};
#endif /* mMessage_hpp */
