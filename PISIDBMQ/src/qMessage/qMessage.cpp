//
//  qMessage.cpp
//  PISIDBMQ
//
//  Created by Asoby ‎‎ on 29.09.2022.
//

#include "qMessage.hpp"

qMessage::qMessage(mHeaderBase header, std::string _key, std::string _value, std::string _route, time_t _timestamp){
    key = _key;
    value = _value;
    route = _route;
    timestamp = _timestamp;
    
}

std::string qMessage::getSpace(){
    return route.substr(0, route.find("/"));
}

std::string qMessage::getQueue(){
    return route.substr(route.find("/")+1, route.length());
}
