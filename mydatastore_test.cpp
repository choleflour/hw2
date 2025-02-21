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
int main(int argc, char* argv[])
{
    MyDataStore ds;
    std::vector<std::string> terms({"horror", "drama"});
    
    std::vector<Product*> hits = ds.search(terms, 1);
    ds.setResults(hits);
    for (size_t i = 0; i < ds.results_.size(); i ++) {
        ds.results_[i]->dump(std::cout);
    }


return 0;
}