#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "book.h"
#include "product.h"
#include <string>
using namespace std;
int main() {
    string name = "hello";
    string isbn = "1234567";
    Product * book = new Book(name, 19.00 ,3, isbn, name);
    book->displayString();
    delete book;
    return 0;
}