#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"
#include "product.h"
using namespace std;

Clothing::Clothing(const std::string name, double price, int qty, const std::string size, const std::string brand) :
Product("clothing", name, price, qty),
size_(size),
brand_(brand) {


}
std::set<std::string> Clothing::keywords() const {
    
    // return parseStringToWords(getName());
    std::set<std::string> res = parseStringToWords(getName());
    std::set<std::string> brand =  parseStringToWords(brand_);
    res.insert(brand.begin(), brand.end());
    return res;
}

std::string Clothing::displayString() const {
    std::stringstream os;
        os << getName() << "\n"
           << "Size: " << size_ << " Brand: " << brand_ << "\n"
           << std::fixed << std::setprecision(2) << getPrice() 
           << " " << getQty() << " left.";
    
        return os.str();
}

void Clothing::dump(std::ostream& os) const {
    Product::dump(os);
    os << size_ << "\n" << brand_ << std::endl;
}

Clothing::~Clothing() {
    
}