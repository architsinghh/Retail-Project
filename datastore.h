#ifndef DATASTORE_H
#define DATASTORE_H
#include <string>
#include <set>
#include <vector>
#include "product.h"
#include "user.h"




class DataStore {
public:
    virtual ~DataStore() { }

    
    virtual void addProduct(Product* p) = 0;

  
    virtual void addUser(User* u) = 0;


    virtual std::vector<Product*> search(std::vector<std::string>& terms, int type) = 0;

    
    virtual void dump(std::ostream& ofile) = 0;


};

#endif
