#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"
#include "book.h"
#include "clothing.h"
#include "movie.h"
using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

void printCart(const std::deque<Product*>& cart) {
    int idx = 1;
    for (const auto& product : cart) {
        std::cout << "Item " << idx << std::endl; 
        if (product) {
            std::cout << product->displayString() << std::endl;
        } else {
            std::cout << "Null product pointer" << std::endl;
        }
        idx++;
    }
}

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
                ds.setResults(hits); //
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
                ds.setResults(hits); //
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            } else if (cmd == "ADD") {
                string username;
                size_t hit_result_index;
                if(ss >> username) {
                    // if username is valid
                    username = convToLower(username);
                    vector<User *> users = ds.getUsers();
                    bool userFound = false;
                    for (size_t i = 0; i < users.size(); i ++) {
                        if (users[i]->getName() == username) {
                            userFound = true;
                        }
                    }
                    if (!userFound) {
                        cout << "Invalid request" << endl;
                        continue;
                    }
                       
                } else {
                    cout << "Invalid request" << endl;
                    continue;

                }
                if (ss >> hit_result_index) {
                    if (hit_result_index < 1 || hit_result_index > hits.size()) {
                        cout << "Invalid request" << endl;
                        continue;
                    }

                } else {
                    cout << "Invalid request" << endl;
                    continue;
                }
                std::deque<Product *> &cart = ds.getCarts()[username];
                Product *p = ds.getResults()[hit_result_index-1];
                cart.push_back(p);
                // printCart(cart);

            } else if (cmd == "VIEWCART") {
                string username;
                if(ss >> username) {
                    // if username is valid
                    username = convToLower(username);
                    vector<User *> users = ds.getUsers();
                    bool userFound = false;
                    for (size_t i = 0; i < users.size(); i ++) {
                        if (users[i]->getName() == username) {
                            userFound = true;
                        }
                    }
                    if (!userFound) {
                        cout << "Invalid username" << endl;
                        continue;
                    }
                    std::deque<Product *> &cart = ds.getCarts()[username];
                    printCart(cart);
                       
                } else {
                    cout << "Invalid request" << endl;
                    continue;

                }
            } else if (cmd == "BUYCART") {
                string username;
                User *user;
                if (ss >> username)
                {
                    // if username is valid
                    vector<User *> users = ds.getUsers();
                    
                    bool userFound = false;
                    for (size_t i = 0; i < users.size(); i++)
                    {
                        if (users[i]->getName() == username)
                        {
                            userFound = true;
                            user = users[i];
                        }
                    }
                    if (!userFound)
                    {
                        cout << "Invalid username" << endl;
                        continue;
                    }
                    // username is valid
                    std::deque<Product *> cart = ds.getCarts()[username];
                    double balance = user->getBalance();
                    std::deque<Product *> copy = cart;
                    std::deque<Product *> unableToBuy;
                    while (!cart.empty()) {

                        Product *curr = cart.front();
                        double price = curr->getPrice();
                        cart.pop_front();
                        if (balance > price && curr->getQty() >= 1) {
                            user->deductAmount(price);
                            curr->subtractQty(1);
                            
                        } else {
                            unableToBuy.push_back(curr);
                        }
                        balance = user->getBalance();

                    }
                    ds.getCarts()[username] = unableToBuy;

                } else
                {
                    cout << "Invalid request" << endl;
                    continue;
                }
                
            }

            else {
                cout << "Unknown command" << endl;
            }
        }

    }
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}


