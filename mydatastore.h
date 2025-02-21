#include <string>
#include <set>
#include <vector>
#include <map>
#include <deque>
#include "product.h"
#include "user.h"
#include "datastore.h"
class MyDataStore: public DataStore {
    public:
    ~MyDataStore();
    MyDataStore();
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    std::vector<User *> getUsers();
    std::vector<Product *> getProducts();
    std::map<std::string, std::deque<Product *>>& getCarts();
    std::vector<Product*> getResults();
    void setResults(std::vector<Product*> hits);
    protected:
    std::vector<Product *> products_;
    std::vector<User *> users_;
    std::map<std::string, std::deque<Product *>> carts_;
    std::vector<Product*> results_;


};