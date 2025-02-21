#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <vector>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{

std::set<std::string> keywords;

// trim split words and put it into a set 
std::vector<std::string> punct({"'", "\"", ".", "?", "!", ":", ";", ",", " "});
size_t start = 0;
size_t curr = 0;

while (curr < rawWords.length()) {
    std::vector<std::string>::iterator it = std::find(punct.begin(), punct.end(), std::string(1, rawWords[curr]));
    if (it != punct.end()) {
        // curr is the punct
        if (curr - start > 1) {
            keywords.insert(convToLower(rawWords.substr(start, curr-start)));
        }
        start = curr + 1;
    }
    curr ++;
    // start with idx 0, iteratre until you find first punct, take punct - idx and add to keyword, update start to curr + 1, and curr = curr + 1
}

if (curr - start > 1) {
    keywords.insert(convToLower(rawWords.substr(start, curr)));
}

return keywords;


}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    // s.erase(s.begin(), 
	//     std::find_if(s.begin(), 
	// 		 s.end(), 
	// 		 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    // s.erase(
	//     std::find_if(s.rbegin(), 
	// 		 s.rend(), 
	// 		 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	//     s.end());
    return s;
}

// // trim from both ends
std::string &trim(std::string &s) {
//     return ltrim(rtrim(s));
    return s;
}
