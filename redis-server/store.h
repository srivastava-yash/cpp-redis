#ifndef STORE_H
#define STORE_H
#include <chrono>
#include <string>
#include "redisObj.h"
using namespace std;

class Store {
    private: 
        unordered_map<string, RedisObj*> store;
        unordered_map<string,string> expiryObj;
    
    public: 
        RedisObj* getKeyValue(string);
        string getKeyExpiry(string);

        void setKey(string, RedisObj*);
        void setExpiry(string, string);
    
};

Store* init_store();


#endif