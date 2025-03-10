CXX=g++
CXXFLAGS=-g -Wall -std=c++11
# Uncomment for parser DEBUG
#DEFS=-DDEBUG

OBJS=amazon.o user.o db_parser.o product.o product_parser.o util.o mydatastore.o clothing.o book.o movie.o
# OBJ = util.o util_test.o

# util_test: $(OBJ)
# 	$(CXX) $(CXXFLAGS) -o $@ $^
all: amazon

amazon: $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $(OBJS)

amazon.o: amazon.cpp db_parser.h datastore.h mydatastore.h product_parser.h 
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c amazon.cpp
user.o: user.cpp user.h 
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c user.cpp
db_parser.o: db_parser.cpp db_parser.h product.h product_parser.h user.h datastore.h  mydatastore.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c db_parser.cpp
product.o: product.cpp product.h 
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c product.cpp
product_parser.o: product_parser.cpp product_parser.h product.h 
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c product_parser.cpp
util.o: util.cpp util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c util.cpp
movie.o: movie.cpp movie.h util.h product.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c movie.cpp
book.o: book.cpp book.h util.h product.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c book.cpp
clothing.o: clothing.cpp clothing.h util.h product.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c clothing.cpp

# product_test: product_test.o book.o product.o util.o db_parser.o
# 	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $^
# product_test.o: product_test.cpp book.h product.h
# 	$(CXX) $(CXXFLAGS) -c product_test.cpp

# mydatastore_test: mydatastore_test.o user.o db_parser.o product.o product_parser.o util.o mydatastore.o clothing.o book.o movie.o
# 	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $^
# mydatastore_test.o: mydatastore_test.cpp db_parser.h datastore.h mydatastore.h product_parser.h 
# 	$(CXX) $(CXXFLAGS) -c mydatastore_test.cpp



clean:
	rm -f *.o amazon
