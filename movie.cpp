#include <sstream>
#include <iomanip>
#include "movie.h"
#include <iostream>
using namespace std;

//uses product constructor and initializes the genre and rating
Movie::Movie(const std::string category, const std::string name, double price, int qty, const string genre, const string rating) : Product(category, name, price, qty),
    genre_(genre),
    rating_(rating)
{

}

//uses parseStringToWords function to get keywords
set<string> Movie::keywords() const{
    set<string> keywordSet;

    keywordSet.insert(rating_);
    //uses parse string function and set union to get keywords, and combine them into one set
    set<string> temp1 = parseStringToWords(name_);
    keywordSet = setUnion(keywordSet, temp1);
    set<string> temp2 = parseStringToWords(genre_);
    keywordSet = setUnion(keywordSet, temp2);
    return keywordSet;
    
}

//displays the details of the movie object
string Movie::displayString() const{
    string output;
    ostringstream oss;
    oss << fixed << setprecision(2) << getPrice();
    output = getName() + "\nGenre: " + genre_ + " Rating: " + rating_ + "\n" + oss.str() + " " + to_string(getQty()) + " left.";
    return output;
}

//dumps movie data into ostream
void Movie::dump(std::ostream& os) const{
    Product::dump(os);
    os << genre_ << "\n" << rating_ << endl;
}




