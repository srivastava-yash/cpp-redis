#ifndef STORE_H
#define STORE_H
#include <chrono>
#include <string>
#include "redisObj.h"
using namespace std;

class Store {
    private:
        unordered_map<string, RedisObj*> store;
        unordered_map<string,uint64_t> expiryObj;

    public:
        RedisObj* getKeyValue(string);
        uint64_t getKeyExpiry(string);

        void setKey(string, RedisObj*);
        void setExpiry(string, int64_t);

};

Store* init_store();


#endif
