//
//  mQueue.hpp
//  PISIDBMQ
//
//  Created by Asoby ‎‎ on 28.09.2022.
//

#ifndef mQueue_hpp
#define mQueue_hpp

#include <stdio.h>
#include "../../lib/tools/tools.hpp"
#include "../../lib/mLogger/mLogger.hpp"
#include "../mHeaderBase/mHeaderBase.hpp"
#include "../mMessage/mMessage.hpp"

struct _QUEUE_STATE{
    int down = 1;
    int up = 2;
    int crashed = 3;
};

class mQueue{
    
    // hardcoded for now
    int MAX_MESSAGE_COUNT = 1000000;
    
    int id;
    
    //full queue route
    std::string route;
    
    //queue name (same as in the route)
    std::string name;
    
    //queue state from _QUEUE_STATE
    int state;
    
    //instance of _QUEUE_STATE because well
    _QUEUE_STATE states;
    
    //current message offset (count of read messages)
    int currentOffset=0;
    
    //messages themselves
    std::vector<mMessage> messages;
    
public:
    mQueue(std::string route, std::string name, int state):
        route(route),
        name(name),
    state(state) {};
    
    // states from _QUEUE_STATE
    int getState();
    
    // update state
    void setState(int state);
    
    // get full route to queue
    std::string getRoute();
    
    // don't use this
    void setRoute();

    std::string getName();
    void setName();
    long getMessageCount();
    
    // better use QueueSpace.AcceptMessage
    std::string AddMessage(mMessage message);
    
    // get the 0th message
    mMessage GetMessage();
    
    //mark message as read
    std::string ReadMessage();
    void EmptyQueue();
    
    ~mQueue();
};

#endif /* mQueue_hpp */
