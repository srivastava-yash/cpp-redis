#include "redisObj.h"

RedisObj::RedisObj(string value, string lastAccessedAt) {
    this->value = value;
    this->lastAccessedAt = lastAccessedAt;
}

string RedisObj::getValue() {
    return this->value;
}

string RedisObj::getLastAccessedAt() {
    return this->lastAccessedAt;
}