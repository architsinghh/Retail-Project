#include <sstream>
#include <iomanip>
#include "book.h"
#include <iostream>
using namespace std;

//uses product constructor and initializes authonrname and isbn
Book::Book(const std::string category, const std::string name, double price, int qty, const string authorName, const string ISBN) : Product(category, name, price, qty),
    authorName_(authorName),
    ISBN_(ISBN)
{

}

//gets keywords of the book
set<string> Book::keywords() const{
    set<string> keywordSet;
    keywordSet.insert(ISBN_);
    //uses parseStringToWords function and setUnion function to combine the keywords
    set<string> temp1 = parseStringToWords(name_);
    keywordSet = setUnion(keywordSet, temp1);
    set<string> temp2 = parseStringToWords(authorName_);
    keywordSet = setUnion(keywordSet, temp2);
    return keywordSet;
    
}

//displays the details of the book object
string Book::displayString() const{
    string output;
    ostringstream oss;
    oss << fixed << setprecision(2) << getPrice();
    output = getName() + "\nAuthor: " + authorName_ + " ISBN: " + ISBN_ + "\n" + oss.str() + " " + to_string(getQty()) + " left.";
    return output;
}
 

//dumps data into ostream
void Book::dump(std::ostream& os) const{
    Product::dump(os);
    os << ISBN_ << "\n" << authorName_ << endl;
}




