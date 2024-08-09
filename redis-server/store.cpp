#include "store.h"
using namespace std;


uint64_t Store::getKeyExpiry(string key) {
    return this->expiryObj[key];
}

RedisObj* Store::getKeyValue(string key) {
    return this->store[key];
}

void Store::setKey(string key, RedisObj* obj) {
    this->store[key] = obj;
}

void Store::setExpiry(string key, int64_t expDurationMs) {
    this->expiryObj[key] = static_cast<uint64_t>(chrono::duration_cast<chrono::milliseconds>(
                        chrono::system_clock::now().time_since_epoch()).count())
                   + static_cast<uint64_t>(expDurationMs);
}

Store* init_store() {
    Store* store = new Store();
    return store;
}
