//
//  QueueSpaceRouter.cpp
//  PISIDBMQ
//
//  Created by Asoby ‎‎ on 29.09.2022.
//

#include "QueueSpaceRouter.hpp"

QueueSpaceRouter::QueueSpaceRouter() {};

void QueueSpaceRouter::AcknowledgeSpace(QueueSpace* _s){
    qSpaces.push_back(_s);
    
    // I don't know why, but qSpaceIndex returns size of 1 when empty
    // this does the trick though
    SpaceIndex _i(_s->getName(), (long)qSpaces.size()-1);
    // mLogger(1).INFO("qSpaces size: " + std::to_string(qSpaces.size()));
    qSpaceIndex.push_back(_i);
}

void QueueSpaceRouter::RemoveQSpace(QueueSpace* _s){
    std::string s = _s->getName();
    for(SpaceIndex qs : qSpaceIndex){
        if(qs._spaceName == s){
            qSpaces.erase(std::next(qSpaces.begin(), qs._spaceIndex));
            qSpaceIndex.erase(std::next(qSpaceIndex.begin(), qs._spaceIndex));
        }
    }
}

void QueueSpaceRouter::RemoveQSpace(std::string _n){
    long _index = GetQSpaceIndex(_n);
    if(_index != -1){
        qSpaces.erase(std::next(qSpaces.begin(), _index));
        qSpaceIndex.erase(std::next(qSpaceIndex.begin(), _index));
    }
}

QueueSpace* QueueSpaceRouter::FindQSpace(std::string _name){
    long _index = GetQSpaceIndex(_name);
    if(_index != -1){
        return qSpaces[_index];
    }
    return nullptr;
}

std::string QueueSpaceRouter::RouteMessage(qMessage message){
    mLogger(1).INFO("Received message: " + message.ToString());
    mLogger(1).INFO("Target route: "  + message.getSpace() + "/" + message.getQueue());
    long _index = GetQSpaceIndex(message.getSpace());
    QueueSpace * qs;
    mLogger(1).INFO("Found QueueSpace " + message.getSpace() + " at index " + std::to_string(_index));
    if(_index != -1){
        mLogger(1).INFO("Found target space");
        
        qs = qSpaces[_index];
        
        long qid = qs->checkQueueExists(message.getQueue());
        if(qid == -1){
            mLogger(1).ERROR("No Queue with name " + message.getQueue() + " exists in QueueSpace " + message.getSpace());
            return "No Queue with name " + message.getQueue() + " exists in QueueSpace " + message.getSpace();
        }

        long qState = qs->AcceptMessage(message, message.getQueue());
        
        mLogger(1).INFO("Added message to queue " + message.getQueue());
        mLogger(1).INFO("QUEUE " + qs->GetQueueLoc(message.getQueue())->getName()+ " INFO: " + std::to_string(qState));
        
        size_t qLoad = qs->GetQueueLoc(message.getQueue())->getMessageCount();
        mLogger(1).INFO(message.getQueue() + " | Line 73 | Current message count: " + std::to_string(qLoad));
        return "Added message; current queue load: " + std::to_string(qLoad);
    }
    mLogger(1).ERROR("The target space and queue don't exist");
    return "";
}
std::string QueueSpaceRouter::RouteMessages(std::vector<qMessage> messages){
    for(qMessage m : messages){
        try{
            std::string err = RouteMessage(m);
            if(err != "") throw(err);
        }
        catch(std::string s){
            mLogger(1).ERROR(s);
        }
    }
    return "OK";
}

long QueueSpaceRouter::GetQSpaceIndex(std::string _n){
    for(SpaceIndex qs : qSpaceIndex){
        if(qs._spaceName == _n){
            return qs._spaceIndex;
        }
    }
    return -1;
}
