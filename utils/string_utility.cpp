#include <string_utility.h>


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