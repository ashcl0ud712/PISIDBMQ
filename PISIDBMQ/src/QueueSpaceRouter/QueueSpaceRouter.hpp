//
//  QueueSpaceRouter.hpp
//  PISIDBMQ
//
//  Created by Asoby ‎‎ on 29.09.2022.
//

#ifndef QueueSpaceRouter_hpp
#define QueueSpaceRouter_hpp

#include <stdio.h>
#include "../QueueSpace/QueueSpace.hpp"
#include "../qMessage/qMessage.hpp"

struct SpaceIndex{
    std::string _spaceName;
    // std::string _targetRoute;
    long _spaceIndex;
    
    SpaceIndex(std::string _n, long _i): _spaceName(_n), _spaceIndex(_i){};
};

class QueueSpaceRouter{
    std::vector<QueueSpace*> qSpaces;
    std::vector<SpaceIndex> qSpaceIndex;
    
public:
    QueueSpaceRouter();
    
    // Acknowledge a QueueSpace
    void AcknowledgeSpace(QueueSpace*);
    
    // Forget a QueueSpace
    void RemoveQSpace(QueueSpace*);
    
    // Forget a QueueSpace (search by name)
    void RemoveQSpace(std::string);
    
    // Get pointed to a QueueSpace
    QueueSpace* FindQSpace(std::string);
    
    // Route a single message
    std::string RouteMessage(qMessage);
    
    // Route a batch of messages
    std::string RouteMessages(std::vector<qMessage>);
    
    // Get queue index (internal, might be useful)
    long GetQSpaceIndex(std::string);
    
};


class LoadBalancer{
public:
    LoadBalancer();
    void ReRouteMessage(std::string, qMessage);
    
};

#endif /* QueueSpaceRouter_hpp */
