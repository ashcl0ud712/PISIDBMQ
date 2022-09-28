#include "../src/QueueSpace/QueueSpace.hpp"
#include <thread>

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
    
    if(!queue.AddMessage(message).empty()){
        Log.INFO("Queue is down - OK");
        Log.INFO(queue.AddMessage(message));
    }
    else{
        Log.ERROR("Something wrong");
    }
    
    Log.INFO("Setting queue state to UP (2)");
    queue.setState(2);
    
    Log.INFO("Current state: " + std::to_string(queue.getState()));
    Log.INFO("Inserting message to queue " + name);
    
    std::string r = queue.AddMessage(message);
    if(r.empty()){
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
        
        std::string r = queue.AddMessage(message);
        if(r.empty()){
            Log.INFO("OK");
        }
        else Log.ERROR("Not OK: " + r);
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

