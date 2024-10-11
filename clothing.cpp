#include <sstream>
#include <iomanip>
#include "clothing.h"
#include <iostream>
using namespace std;

//uses product constructor and initializes size and brand variables
Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const string size, const string brand) : Product(category, name, price, qty),
    size_(size),
    brand_(brand)
{

}

//uses parseStringToWords function to get keywords
set<string> Clothing::keywords() const{
    set<string> keywordSet;
    //uses parse string function and set union to get keywords, and combine them into one set
    keywordSet = parseStringToWords(brand_);
    set<string> temp1 = parseStringToWords(name_);
    keywordSet = setUnion(keywordSet, temp1);
    set<string> temp2 = parseStringToWords(size_);

    return keywordSet;
    
}

//displays the details of the book object
string Clothing::displayString() const{
    string output;
    ostringstream oss;
    oss << fixed << setprecision(2) << getPrice();
    output = getName() + "\nSize: " + size_ + " Brand: " + brand_ + "\n" + oss.str() + " " + to_string(getQty()) + " left.";
    return output;
}

void Clothing::dump(std::ostream& os) const{
    Product::dump(os);
    os << size_ << "\n" << brand_ << endl;
}
