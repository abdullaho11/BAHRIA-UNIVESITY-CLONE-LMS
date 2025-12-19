#include "lms.h"

using namespace std;

string nowdate() {
    time_t t = time(nullptr);
    tm* tm_ptr = localtime(&t);
    char buf[64];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm_ptr);
    return string(buf);
}
