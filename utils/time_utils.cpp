#include "time_utils.h"
using namespace std;

uint64_t get_current_time() {
    return static_cast<uint64_t>(chrono::duration_cast<chrono::milliseconds>(
                        chrono::system_clock::now().time_since_epoch()).count());
}
