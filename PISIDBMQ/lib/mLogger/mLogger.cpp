//
//  mLogger.cpp
//  PISIDBMQ
//
//  Created by Asoby ‎‎ on 28.09.2022.
//

#include "mLogger.hpp"

/*
 will need to refactor this logger
 */

mLogger::mLogger(){

}

mLogger::mLogger(int level): level(level) {};

bool mLogger::levelSelector(int _level){
    return level <= _level;
}

std::string mLogger::Debug(std::string message){
    if(levelSelector(levelMap.debug)){
        time_t t = time(NULL);
        std::cout << t << " | DEBUG | " << message << "\n";
    }
    return message;
}

std::string mLogger::INFO(std::string message){
    if(levelSelector(levelMap.info)){
        time_t t = time(NULL);
        std::cout << t << " | INFO | " << message << "\n";
    }
    return message;
}

std::string mLogger::WARNING(std::string message){
    if(levelSelector(levelMap.warning)){
        time_t t = time(NULL);
        std::cout << t << " | WARNING | " << message << "\n";
    }
    return message;
}

std::string mLogger::ERROR(std::string message){
    if(levelSelector(levelMap.error)){
        time_t t = time(NULL);
        std::cout << t << " | ERROR | " << message << "\n";
    }
    return message;
}

std::string mLogger::CRITICAL(std::string message){
    if(levelSelector(levelMap.critical)){
        time_t t = time(NULL);
        std::cout << t << " | CRITICAL | " << message << "\n";
    }
    return message;
}
