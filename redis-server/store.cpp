#include "store.h"
using namespace std;


string Store::getKeyExpiry(string key) {
    return this->expiryObj[key];
}

RedisObj* Store::getKeyValue(string key) {
    return this->store[key];
}

void Store::setKey(string key, RedisObj* obj) {
    this->store[key] = obj;
}

void Store::setExpiry(string key, string expiry) {
    this->expiryObj[key] = expiry;
}

Store* init_store() {
    Store* store = new Store();
    return store;
}