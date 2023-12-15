#ifndef EVAL_H
#define EVAL_H
#include "cmd.h"
#include "store.h"

using namespace std;

string evalPing(Cmd*, Store*);

string evalGet(Cmd*, Store*);

int evalSet(Cmd*, Store*);

#endif