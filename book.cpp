#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"
#include "product.h"
using namespace std;

Book::Book(const std::string name, double price, int qty, const std::string isbn, const std::string author) :
Product("book", name, price, qty),
isbn_(isbn),
author_(author) {


}
std::set<std::string> Book::keywords() const {
    std::set<std::string> res = parseStringToWords(getName());
    std::set<std::string> auth =  parseStringToWords(author_);
    std::set<std::string> isbn =  parseStringToWords(isbn_);
    res.insert(auth.begin(), auth.end());
    res.insert(isbn.begin(), isbn.end());
    return res;
}

std::string Book::displayString() const {
    std::stringstream os;
    os << getName() << "\n"
       << "Author: " << author_ << " ISBN: " << isbn_ << "\n"
       << std::fixed << std::setprecision(2) << getPrice() 
       << " " << getQty() << " left.";

    return os.str();
}

void Book::dump(std::ostream& os) const {
    Product::dump(os);
    os << isbn_ << "\n" << author_ << std::endl;
}

Book::~Book() {

}