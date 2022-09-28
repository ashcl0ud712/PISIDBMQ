//
//  main.cpp
//  PISIDBMQ
//
//  Created by Asoby ‎‎ on 28.09.2022.
//

#include <iostream>
#include "tests/QueueTests.hpp"
int main(int argc, const char * argv[]) {
    QueueMultiThreadTest();
    QueueSpam();
    return 0;
}
