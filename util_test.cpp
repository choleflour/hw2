#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"
#include <string>
using namespace std;
int main() {
    // set<string> s1 = {"A", "B", "E"};
    // set<string> s2 = {"A", "B", "C", "D"};
    set<string> result = parseStringToWords("J");
    for (set<string>::iterator it = result.begin(); it != result.end(); ++it) {
        cout << *it << endl;
    }
    return 0;
}