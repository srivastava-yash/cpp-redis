#include "eval.h"
#include "cmd.h"
using namespace std;

string evalPing(Cmd* cmd) {
    if(cmd->getArgs().size() > 1) {
        return "Invalid number of arguments";
    }
    else if(cmd->getArgs().size() == 1) {
        return cmd->getArgs()[0];
    }

    return "Pong";
}

string evalGet(Cmd* cmd) {
    if(cmd->getArgs().size() != 1) {
        return "Invalid number of arguments";
    }

    string key = cmd->getArgs()[0];

    // create store
}