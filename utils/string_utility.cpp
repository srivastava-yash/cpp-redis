#include "string_utility.h"
using namespace std;


/*
    function to split a string on spaces
    params:
        str: string
    returns:
        vector<string>
*/
vector<string> split_string(string str) {
    vector<string> strArr;
    stringstream ss(str);
    std::string word;
    while (getline(ss, word, ' ')) {
        strArr.push_back(word);
    }

    return strArr;
}

string str_toupper(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}