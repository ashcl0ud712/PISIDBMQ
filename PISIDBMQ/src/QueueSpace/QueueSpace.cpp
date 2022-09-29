//
//  QueueSpace.cpp
//  PISIDBMQ
//
//  Created by Asoby ‎‎ on 28.09.2022.
//

#include "QueueSpace.hpp"

std::string QueueSpace::getName(){
    return name;
}

QueueSpace::~QueueSpace(){
    mLogger().WARNING("Dropping Queue space " + name);
}


//Use this to create a new queue in the space
void QueueSpace::AddQueue(std::string qName){
    if (checkQueueExists(qName)==-1){
        long currentIndex = qIndex.size();
        qIndex.push_back(QueueElement(qName, currentIndex));
        qList.push_back(mQueue(name+"/"+qName, qName, 2));
        mLogger(1).WARNING("QueueSpace " + name + " | Created a queue: " + qName);
    }
}

// if queue exists, return its position in qList
long QueueSpace::checkQueueExists(std::string qName){
    for(QueueElement q: qIndex){
        if(q.name == qName) return q.pos;
    }
    return -1;
}

// indirectly access queue message count
long QueueSpace::checkQueueLoad(std::string qName){
    return qList[checkQueueExists(qName)].getMessageCount();
}

// get pointed to a queue
mQueue* QueueSpace::GetQueueLoc(std::string qName){
    if(checkQueueExists(qName)!=-1){
        return &qList[checkQueueExists(qName)];
    }
    else return nullptr;
}

// rip queue
void QueueSpace::DeleteQueue(std::string qName){
    for(QueueElement q : qIndex){
        if(q.name == qName){
            qList.erase(std::next(qList.begin(), q.pos));
            qIndex.erase(std::next(qIndex.begin(), q.pos));
        }
    }
}

// this also can be used to insert a message into the queue. It's
// actually preferable to use this over AddMessage() via pointers
// and more developer-friendly
long QueueSpace::AcceptMessage(mMessage message, std::string qName){
    long pos = checkQueueExists(qName);
    
    // does the queue exist and is message valid?
    if(pos != -1 && message.isValid()){
        std::string r = qList[pos].AddMessage(message);
        return qList[pos].getState();
    }
    else return -1;
}

long QueueSpace::AcceptMessage(mMessage message, std::string qName, bool important){
    return -1;
}

long QueueSpace::GetQueueCount(){
    return qList.size();
}
