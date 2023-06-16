#include "cmd.h"
using namespace std;

Cmd::Cmd(string cmd, vector<string> args) {
    this->cmd = cmd;
    this->args = args;
}

string Cmd::getCmd() {
    return this->cmd;
}

vector<string> Cmd::getArgs() {
    return this->args;
}