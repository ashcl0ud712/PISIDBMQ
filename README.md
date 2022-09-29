#  PISIDBMQ

## Don't ask why it's named like that
### It's hilarious though

## Overview
PISIDBMQ is a message queue (MQ) implementation in C++. 

The basic structure of an instance is:

QueueSpaceRouter
└── QueueSpace
    ├── mQueue
    │   ├── mMessage
    │   └── mMessage
    └── mQueue
        └── mMessage
        
QueueSpaces are used to create mQueues, as well as to keep track of existing ones. To make things faster, basic information about mQueues is stored in the qIndex array, which is used for iterating through to find the index of an mQueue instead of iterating through the objects directly. When a new mQueue is created, it is also indexed.

QueueSpaces are managed by Routers, which route messages to spaces. The QueueSpaces themselves are meant to be autonomous and Routers only keep track of the memory locations of those QueueSpaces.

## Features

- Developer-friendly message constructors (check qMessage (queue message) and mMessage (minimal message) classes)
- Queue kill-switch:
    - MAX_MESSAGE_COUNT variable is checked every time before inserting a new message, preventing memory from overloading from useless requests
- Address anything
    - I'm trying to make this MQ as dev-friendly as possible here, so each important class provides pointer getters for objects stored in arrays
- Pretty large load potential
    - Tested up to a million messages in a couple different mQueues on Macbook Air M1 (16GB).


### TODO
- Refactor mLogger (it's a mess right now)
- Decide what to do with dead (crashed) queues
- Write some docs


