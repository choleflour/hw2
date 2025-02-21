#include <string>
#include <set>
#include <vector>
#include <map>
#include <deque>
#include "product.h"
#include "user.h"
#include "mydatastore.h"
#include "util.h"

MyDataStore::MyDataStore() {
    
    
}
MyDataStore::~MyDataStore() {
    for (size_t i = 0; i < products_.size(); i ++) {
        delete products_[i];
    }
    for (size_t i = 0; i < users_.size(); i ++) {
        delete users_[i];
    }


}
void MyDataStore::addProduct(Product* p) {
    products_.push_back(p);

}
void MyDataStore::addUser(User* u) {
    users_.push_back(u);

}
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    std::vector<Product*> result;
    std::set<std::string> termSet(terms.begin(), terms.end());
    // for (std::set<std::string>::iterator it = termSet.begin(); it != termSet.end(); ++it) {
    //     std::cout << *it << std::endl;
    // }
    if (type == 0) {
        for (size_t i = 0; i < products_.size(); i++) {
            // chg to const
            
            if (setIntersection(termSet, products_[i]->keywords())==termSet) {
                result.push_back(products_[i]);
            }
        }

    } else if (type == 1) { // or
        for (size_t i = 0; i < products_.size(); i++) {
            std::set<std::string> key = products_[i]->keywords();

            
            std::set<std::string> inSet = setIntersection(termSet, key);
            if (!inSet.empty()) {
                result.push_back(products_[i]);
            }
        }

    }
    return result;

}
void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>" << std::endl;
    for (size_t i = 0; i < products_.size(); i++) {
        products_[i]->dump(ofile);
    }
    ofile << "</products>\n<users>" << std::endl;

    for (size_t i = 0; i < users_.size(); i++) {
        users_[i]->dump(ofile);
    }
    ofile << "</users>" << std::endl;

}

std::vector<User *> MyDataStore::getUsers() {
    return users_;
}
std::vector<Product *> MyDataStore::getProducts() {
    return products_;
}

std::vector<Product *> MyDataStore::getResults() {
    return results_;
}

std::map<std::string, std::deque<Product *>>& MyDataStore::getCarts() {
    return carts_;
}
void MyDataStore::setResults(std::vector<Product*> hits) {
    results_ = hits;

}