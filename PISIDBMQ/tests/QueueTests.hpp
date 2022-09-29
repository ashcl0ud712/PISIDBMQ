#include "../src/QueueSpace/QueueSpace.hpp"
#include "../src/QueueSpaceRouter/QueueSpaceRouter.hpp"
#include <thread>

std::string genMessageKey(int n)
{
    char alphabet[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                          'h', 'i', 'j', 'k', 'l', 'm', 'n',
                          'o', 'p', 'q', 'r', 's', 't', 'u',
                          'v', 'w', 'x', 'y', 'z' };
 
    std::string res = "";
    for (int i = 0; i < n; i++)
        res = res + alphabet[rand() % 26];
     
    return res;
}

void CreateQueueTest(){
    mLogger Log(1);
    Log.INFO("Trying to create a queue with state=1 (down)");
    std::string route = "/PATH/TEST_ROUTE";
    std::string name = "TEST_QUEUE_NAME";
    mQueue queue(route, name, 1);
    Log.INFO("Created a queue: QUEUE_NAME: " + name);
    
    Log.INFO("Creating a message to insert into queue " + name + ", current state: down");
    mMessage message(mHeaderBase("headerName", "headerValue"), "messageKey", "messageValue");
    Log.INFO("Created message: '" + message.ToString() + "'");
    
    Log.INFO("Inserting message to queue " + name);
    
    if(queue.AddMessage(message) == 1){
        Log.INFO("Queue is down - OK");
        Log.INFO("Trying to add message to an empty queue");
    }
    else{
        Log.ERROR("Something wrong");
    }
    
    Log.INFO("Setting queue state to UP (2)");
    queue.setState(2);
    
    Log.INFO("Current state: " + std::to_string(queue.getState()));
    Log.INFO("Inserting message to queue " + name);
    
    int r = queue.AddMessage(message);
    if(r == 2){
        Log.INFO("OK");
    }
    else Log.ERROR("Not OK");
    
}

void QueueSpam(){
    mLogger Log(1);
    Log.INFO("Trying to create a queue with state=2 (up)");
    std::string route = "/PATH/TEST_ROUTE";
    std::string name = "TEST_QUEUE_NAME";
    mQueue queue(route, name, 2);
    Log.INFO("Created a queue: QUEUE_NAME: " + name);
    
    for(int i=0; i<1005; i++){
        Log.INFO("Creating a message to insert into queue " + name + ", current state: down");
        mMessage message(mHeaderBase("headerName", "headerValue"), "messageKey", "messageValue"+std::to_string(i));
        Log.INFO("Created message: '" + message.ToString() + "'");
        
        Log.INFO("Inserting message to queue " + name);
        
        int r = queue.AddMessage(message);
        if(r == 2){
            Log.INFO("OK");
        }
        else Log.ERROR("Not OK");
    }


}

void QueueSpaceTest(std::string space){
    mLogger Log(1);
    Log.INFO("Creating a QueueSpace");
    QueueSpace qs(space);
    Log.INFO("Adding a test queue to QueueSpace");
    qs.AddQueue("TEST_QUEUE");
    Log.INFO("Added queue: " + std::to_string(qs.checkQueueExists("TEST_QUEUE")));
    
    Log.INFO("Adding another test queue to QueueSpace");
    qs.AddQueue("TEST_QUEUE1");
    Log.INFO("Added queue: " + std::to_string(qs.checkQueueExists("TEST_QUEUE1")));
    
    Log.INFO("Adding a test queue to QueueSpace");
    qs.AddQueue("TEST_QUEUE");
    Log.INFO("Added queue: " + std::to_string(qs.checkQueueExists("TEST_QUEUE")));
    
    Log.INFO("Writing a message to TEST_QUEUE");
    
    Log.INFO("Creating a message to insert into queue TEST_QUEUE");
    mMessage message(mHeaderBase("headerName", "headerValue"), "messageKey", "messageValue");
    Log.INFO("Created message: '" + message.ToString() + "'");
    
    qs.GetQueueLoc("TEST_QUEUE")->AddMessage(message);
    Log.INFO("Current queue load: " +  std::to_string(qs.GetQueueLoc("TEST_QUEUE")->getMessageCount()));
    
    Log.INFO("Creating a message to insert into queue TEST_QUEUE");
    mMessage message1(mHeaderBase("headerName", "headerValue"), "messageKey", "messageValue");
    Log.INFO("Created message: '" + message1.ToString() + "'");
    Log.INFO("\n------\nCHECKING IF THIS SHIT WORKS\n");
    
    for(int i=0;i<1000001;i++){
        std::cout << qs.AcceptMessage(message1, "TEST_QUEUE");
        Log.INFO("SPACE: " + space + " | Current queue load: " +  std::to_string(qs.GetQueueLoc("TEST_QUEUE")->getMessageCount()));
    }
    Log.INFO("Current queue state: " + std::to_string(qs.GetQueueLoc("TEST_QUEUE")->getState()));
}

void QueueMultiThreadTest(){
    // an extreme one but bravo
    // 4 million messages across 4 queues
    std::thread t1(&QueueSpaceTest, "Thread"+std::to_string(1));
    std::thread t2(&QueueSpaceTest, "Thread"+std::to_string(2));
    std::thread t3(&QueueSpaceTest, "Thread"+std::to_string(3));
    std::thread t4(&QueueSpaceTest, "Thread"+std::to_string(4));
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}

void QueueSpaceRouterTest(){
    std::string qNameTest = "test.queue_name";
    mLogger Log(1);
    Log.INFO("Test > Creating a new router");
    QueueSpaceRouter r;
    
    Log.INFO("Test > Creating a new space");
    QueueSpace s("TEST_QUEUE_SPACE");
    
    Log.INFO("Test > Creating a new queue");
    s.AddQueue(qNameTest);
    
    Log.INFO("Test > Adding TEST_QUEUE_SPACE to router's index");
    r.AcknowledgeSpace(&s);
    
    Log.INFO("Test > Creating a message");
    qMessage m(mHeaderBase("headerName", "headerValue"), "messageKey", "messageValue", "TEST_QUEUE_SPACE/" + qNameTest, time_t(0));
    Log.INFO("Test > Created message: " + m.ToString());
    
    Log.INFO("Test > Trying to route message to the queue");
    // r.RouteMessage(m);
    std::string rs = r.RouteMessage(m);
    
    rs = r.RouteMessage(m);
    
    qMessage n(mHeaderBase("headerName", "headerValue"), "messageKey", "messageValue", "TEST_QUEUE_SPACE/TEST_QUEUE_2", time_t(0));
    rs = r.RouteMessage(n);
    // std::cout << r.FindQSpace("TEST_QUEUE_SPACE")->checkQueueLoad("TEST_QUEUE_1");
    
}

void QueueSpaceSingleRouterTest(QueueSpaceRouter* router, std::string sName){
    mLogger Log(1);
    std::string qName = "TEST_QUEUE_"+sName;
    Log.INFO("TEST > Creating QueueSpace");
    QueueSpace* s = new QueueSpace(sName);
    s->AddQueue(qName);
    router->AcknowledgeSpace(s);
    for(int i=0; i<10100; i++){
        Log.INFO("TEST > Creating a message to insert into queue " + qName + ", current state: " + s->GetQueueLoc(qName)->getStateName());
        qMessage message(mHeaderBase("headerName", "headerValue"), genMessageKey(12), "messageValue"+std::to_string(i), sName + "/" + qName, time(0));
        
        Log.INFO("TEST > Created message: '" + message.ToString() + "'");
        
        Log.INFO("TEST > Inserting message to queue " + qName);
        
        std::string r = router->RouteMessage(message);
    }
    s->~QueueSpace();
    
}

void QueueSpaceRouterThreadedTest(){
    QueueSpaceRouter qs1;
    QueueSpaceRouter qs2;
    QueueSpaceRouter qs3;
    QueueSpaceRouter qs4;
    std::thread t1(&QueueSpaceSingleRouterTest, &qs1, "QueueSpace_1");
    std::thread t2(&QueueSpaceSingleRouterTest, &qs2, "QueueSpace_2");
    std::thread t3(&QueueSpaceSingleRouterTest, &qs3, "QueueSpace_3");
    std::thread t4(&QueueSpaceSingleRouterTest, &qs4, "QueueSpace_4");
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}
