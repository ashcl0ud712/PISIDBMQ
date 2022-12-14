//
//  mQueue.cpp
//  PISIDBMQ
//
//  Created by Asoby ‎‎ on 28.09.2022.
//

#include "mQueue.hpp"

void mQueue::setState(int _state){ state = _state; }

int mQueue::getState(){ return state; }

std::string mQueue::getStateName(){
    switch(state){
        case 1: return "down";
        case 2: return "up";
        case 3: return "crashed";
    }
    return "";
}

int mQueue::AddMessage(mMessage message){
    try{
        // check if queue is up and ready
        if(messages.size() < MAX_MESSAGE_COUNT){
            if(state == states.up){
                messages.push_back(message);
                return state;
            }
            else{
                throw(state);
            }
        }
        else{
            state = 3;
            return state;
        }
    }
    catch(int state){
        mLogger(1).ERROR(message.Key() + " | " + name + " | QUEUE_LOG | Invalid queue state: " + std::to_string(state));
        return state;
    }

    return NULL;
}

mMessage mQueue::GetMessage(){
    // get first message in the queue
    try{
        mMessage m = messages.front();
        return m;
    }
    catch(...){
        return mMessage();
    }
}
std::string mQueue::ReadMessage(){
    try{
        //check oif queue is up and ready
        if(state == states.up || state == states.crashed){
            // set offset to a message, marking it as read
            messages.front().SetOffset(currentOffset);
            currentOffset++;
            return "OK";
        }
        else{
            throw(state);
        }
    }
    catch(int state){
        return "Invalid queue state: " + std::to_string(state);
    }
    return NULL;
}

mQueue::~mQueue(){
    mLogger(1).WARNING(name + " | QUEUE_LOG | Cleared queue");
    route = "";
    name = "";
    state = NULL;
    messages.empty();
}

void mQueue::EmptyQueue(){
    messages.empty();
    mLogger(1).WARNING(name + " | QUEUE_LOG | Cleared queue");
}

long mQueue::getMessageCount(){
    return messages.size();
}

std::string mQueue::getRoute(){
    return route;
}

std::string mQueue::getName(){
    return name;
}
