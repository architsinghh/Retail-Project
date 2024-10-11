#include "mydatastore.h"

using namespace std;

MyDataStore::MyDataStore(){}

//deallocates memory by looping through products set and mappedUsers map
MyDataStore::~MyDataStore(){
    for(set<Product*>::iterator it = products.begin(); it != products.end(); it++){
        delete (*it);
    }
    for(map<std::string, User*>::iterator it = mappedUsers.begin(); it != mappedUsers.end(); it++){
        delete (*it).second;
    }
}

//adds product to products set and mappedProducts map
void MyDataStore::addProduct(Product* p){
    //gets keywords and matches them with associated products
    set<string> keywordSet = p->keywords();
    set<string>::iterator it = keywordSet.begin();
    //populates the map of products
    while(it != keywordSet.end()){
        mappedProducts[convToLower(*it)].insert(p);
        it++;
    }
    products.insert(p);

}

//adds user to users set and maps the user's name with the user object
void MyDataStore::addUser(User* u){
    users.insert(u);
    mappedUsers[u->getName()] = u;
}   

//searches through given terms and finds the matching products to the terms
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
    //returns empty vector if there are no terms given
    if(terms.size() == 0){
        return { };
    }
    //initializes set to the first term to get loop started
    set<Product*> set1 = mappedProducts[terms[0]];
    //loops through terms and either finds the intersection or union products of all terms
    for(int i = 1; i < terms.size(); i++){
        //checks if term is associated with any product
        if(mappedProducts.find(terms[i]) != mappedProducts.end()){
            if(type == 0){
                set1 = setIntersection(set1, mappedProducts[terms[i]]);
            }else{
                set1 = setUnion(set1, mappedProducts[terms[i]]);
            }
        }
    }
    //converts set to vector and returns
    vector<Product*> answerVector;
    for(set<Product*>::iterator it = set1.begin(); it != set1.end(); it++){
        answerVector.push_back(*it);
    }
    return answerVector;
}

//dumps the data into the new database
void MyDataStore::dump(std::ostream& ofile){
    ofile << "<products>" << endl;
    //iterates through products set to dump product information
    for(set<Product*>::iterator it = products.begin(); it != products.end(); it++){
        (*it)->dump(ofile);
    }
    ofile << "</products>" << endl;
    ofile << "<users>" << endl;
    //iterates through products set to dump user information
    for(set<User*>::iterator it = users.begin(); it != users.end(); it++){
        (*it)->dump(ofile);
    }
    ofile << "</users>" << endl;
}

//replaces the new cart with the old cart
void MyDataStore::replaceCart(std::string user, vector<Product*> newCart){
    cart[user] = newCart;
}

//returns the user object
User* MyDataStore::getUser(std::string username){
    return mappedUsers[username];
}

//returns cart of the user
vector<Product*> MyDataStore::getCart(std::string username){
    return cart[username];
}

//adds to the cart of the user
void MyDataStore::addToCart(std::string username, Product* currProduct){
    //checks if user is in the database and adds product to their cart if they are
    if(mappedUsers.find(username) == mappedUsers.end()){
        cout << "Invalid request" << endl;
    }else{
        cart[username].push_back(currProduct);
    }
}

//checks if the user exists
bool MyDataStore::findUser(std::string username){
    if(mappedUsers.find(username) == mappedUsers.end()){
        return false;
    }
    return true;
}

//displays information of the user's cart
void MyDataStore::viewCart(std::string username){
    //checks if the user is in the database
    if(mappedUsers.find(username) == mappedUsers.end()){
        cout << "Invalid username" << endl;
    }else{
        //loops through user's cart and displays cart product information
        for(int i = 1; i < cart[username].size() + 1; i++){
            cout << "Item " << i << endl;
            cout << cart[username][i - 1]->displayString() << endl; 
            cout << endl;
        }
    }
}

//buys the cart of the user if there is enough quantity of product and enough user balance
void MyDataStore::buyCart(std::string username){
    //checks if user is in database
    if(mappedUsers.find(username) == mappedUsers.end()){
        cout << "Invalid username" << endl;
    }else{
        //initializes current and new cart
        vector<Product*> currUserCart = getCart(username);
        vector<Product*> updatedCart;
        User* buyingUser = getUser(username);
        //loops through current cart to determine if the product can be purchased
        for(int i = 0; i < currUserCart.size(); i++){
            if(currUserCart[i]->getQty() > 0 && buyingUser->getBalance() > currUserCart[i]->getPrice()){
                //deducts amount from user's balance
                buyingUser->deductAmount(currUserCart[i]->getPrice());
                currUserCart[i]->subtractQty(1);
            }else{
                //checks if there is enough product quantity
                if(currUserCart[i]->getQty() > 0){
                    updatedCart.push_back(currUserCart[i]);
                }
            }
        }
        //sets old cart to new
        cart[username] = updatedCart;
    }
    
}