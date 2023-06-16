#include <string>
using namespace std;

class Cmd {
    private:
        string cmd;
        vector<string> args;
    
    public:
        vector<string> getArgs();
        string getCmd();
        Cmd(string, vector<string>);
};