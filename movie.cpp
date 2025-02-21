#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"
#include "product.h"
using namespace std;

Movie::Movie(const std::string name, double price, int qty, const std::string genre, const std::string rating) :
Product("movie", name, price, qty),
genre_(genre),
rating_(rating) {


}
std::set<std::string> Movie::keywords() const {
    
    // return parseStringToWords(getName());
    std::set<std::string> res = parseStringToWords(getName());
    std::set<std::string> genre =  parseStringToWords(genre_);
    res.insert(genre.begin(), genre.end());
    return res;
}

std::string Movie::displayString() const {
    std::stringstream os;
        os << getName() << "\n"
           << "Genre: " << genre_ << " Rating: " << rating_ << "\n"
           << std::fixed << std::setprecision(2) << getPrice() 
           << " " << getQty() << " left.";
    
        return os.str();
}
// when to do :
void Movie::dump(std::ostream& os) const {
    Product::dump(os);
    os << genre_ << "\n" << rating_<< std::endl;
    // category-specific-info product_category

}

Movie::~Movie() {
    
}