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
        std::cout << time(0) << " | DEBUG | " << message << std::endl;
    }
    return message;
}

std::string mLogger::INFO(std::string message){
    if(levelSelector(levelMap.info)){
        std::cout << time(0) << " | INFO | " << message << std::endl;
    }
    return message;
}

std::string mLogger::WARNING(std::string message){
    if(levelSelector(levelMap.warning)){
        std::cout << time(0) << " | WARNING | " << message << std::endl;
    }
    return message;
}

std::string mLogger::ERROR(std::string message){
    if(levelSelector(levelMap.error)){
        std::cout << time(0) << " | ERROR | " << message << std::endl;
    }
    return message;
}

std::string mLogger::CRITICAL(std::string message){
    if(levelSelector(levelMap.critical)){
        std::cout << time(0) << " | CRITICAL | " << message << std::endl;
    }
    return message;
}
