//
//  mLogger.hpp
//  PISIDBMQ
//
//  Created by Asoby ‎‎ on 28.09.2022.
//

#ifndef mLogger_hpp
#define mLogger_hpp

#include <stdio.h>
#include "../tools/tools.hpp"
#include <time.h>
struct _levelMap{
    int debug = 1;
    int info = 2;
    int warning = 3;
    int error = 4;
    int critical = 5;
};

class mLogger{
    _levelMap levelMap;
    int level;
    int accepted[5] = {1, 2, 3, 4, 5};
public:
    mLogger();
    mLogger(int);
    bool levelSelector(int level);
    
    std::string Debug(std::string message);
    std::string INFO(std::string message);
    std::string WARNING(std::string message);
    std::string ERROR(std::string message);
    std::string CRITICAL(std::string message);
};
#endif /* mLogger_hpp */
