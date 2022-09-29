//
//  qMessage.hpp
//  PISIDBMQ
//
//  Created by Asoby ‎‎ on 29.09.2022.
//

#ifndef qMessage_hpp
#define qMessage_hpp

#include <stdio.h>
#include "../mMessage/mMessage.hpp"
class qMessage : public mMessage{
    std::string route;
    time_t timestamp;
    
public:
    qMessage(mHeaderBase header, std::string key, std::string value, std::string route, time_t timestamp);
    
    // get queue space
    std::string getSpace();
    
    // get queue
    std::string getQueue();
    
    // validate route
    bool validateRoute();
    
    void ParseStringToMessage(std::string message);
};
#endif /* qMessage_hpp */
