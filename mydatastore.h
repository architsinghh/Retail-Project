#include "datastore.h"
#include "util.h"
#include <map>
#include <vector>
#include <iostream>

class MyDataStore: public DataStore{
    public:
        void addProduct(Product* p);
        void addUser(User* u);
        std::vector<Product*> search(std::vector<std::string>& terms, int type);
        void dump(std::ostream& ofile);
        void addToCart(std::string username, Product*);
        void viewCart(std::string username);
        void buyCart(std::string username);
        bool findUser(std::string username);
        std::vector<Product*> getCart(std::string username);
        void replaceCart(std::string user, std::vector<Product*> newCart);
        User* getUser(std::string username);
        MyDataStore();
        ~MyDataStore();
    private:
        std::set<Product*> products; 
        std::set<User*> users;
        std::map<std::string, std::set<Product*>> mappedProducts;
        std::map<std::string, User*> mappedUsers;
        std::map<std::string, std::vector<Product*>> cart;
};  

