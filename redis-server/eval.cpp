#include "eval.h"
using namespace std;

string evalPing(Cmd* cmd, Store* store) {
    if(cmd->getArgs().size() > 1) {
        return "Invalid number of arguments";
    }
    else if(cmd->getArgs().size() == 1) {
        return cmd->getArgs()[0];
    }

    return "Pong";
}

string evalGet(Cmd* cmd, Store* store) {
    if(cmd->getArgs().size() != 1) {
        return "Invalid number of arguments";
    }

    string key = cmd->getArgs()[0];

    RedisObj* obj = store->getKeyValue(key);
    return obj->getValue();
}

int evalSet(Cmd* cmd, Store* store) {
    if(cmd->getArgs().size() < 2) {
        return -1;
    }

    string key = cmd->getArgs()[0];
    string value = cmd->getArgs()[1];

    RedisObj* obj = new RedisObj(value, "now"); //change now to timestamp
    store->setKey(key, obj);

    return 1;
}