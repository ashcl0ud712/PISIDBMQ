//
//  QueueSpace.hpp
//  PISIDBMQ
//
//  Created by Asoby ‎‎ on 28.09.2022.
//

#ifndef QueueSpace_hpp
#define QueueSpace_hpp

#include <stdio.h>
#include "../mQueue/mQueue.hpp"
struct QueueElement{
    std::string name;
    long pos;
    QueueElement(std::string _n, long _p): name(_n), pos(_p) {};
};

class QueueSpace{
    // this is a small hack to boost iterations through qList:
    // queue positions are kept in qIndex, along with queue names
    // which allows for wasting basically zero time finding the queue we need
    std::vector<QueueElement> qIndex;
    std::vector<mQueue> qList;
    std::string name;
    
public:
    QueueSpace(std::string name): name(name) {};
    
    std::string getName();
    // create a queue
    void AddQueue(std::string qName);
    
    //check if queue exists by name
    long checkQueueExists(std::string qName);
    
    //check current message count
    long checkQueueLoad(std::string qName);
    
    //rip queue
    void DeleteQueue(std::string qName);
    
    //get queue location
    mQueue* GetQueueLoc(std::string qName);
    
    //smarter AddMessage
    long AcceptMessage(mMessage message, std::string qName);
    long AcceptMessage(mMessage message, std::string qName, bool important);
    ~QueueSpace();
};
#endif /* QueueSpace_hpp */
