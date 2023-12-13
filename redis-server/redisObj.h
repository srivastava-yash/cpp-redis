#ifndef REDISOBJ_H
#define REDISOBJ_H

#include <string>
using namespace std;

class RedisObj {
    private:
        string value;
        string lastAccessedAt;
    
    public:
        RedisObj(string, string);
        string getValue();
        string getLastAccessedAt();
};

#endif