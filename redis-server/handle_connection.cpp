#include "handle_connection.h"
#include "../utils/string_utility.h"
#include "cmd.h"
#include <algorithm>
using namespace std;


pair<string, int> handle_connection(string input) {
    vector<string> inputArr = split_string(input);
    if(inputArr.size() < 1) {
        return make_pair("Invalid Cmd", -1);
    } else if (str_toupper(inputArr[0]) == "EXIT" || str_toupper(inputArr[0]) == "QUIT") {
        return make_pair("", 0);
    }

    vector<string> args;
    copy_if(inputArr.begin() + 1, inputArr.end(), back_inserter(args), true);

    Cmd* cmd = new Cmd(str_toupper(inputArr[0]), args);

    // complete eval functions

}
