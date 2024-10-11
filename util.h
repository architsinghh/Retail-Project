#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>



//finds the products of the two sets which both have
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
    typename std::set<T>::iterator it;
    std::set<T> compiledSet;
    //iterates through set1 and checks if product is in set2
    for(it = s1.begin(); it != s1.end(); it++){
        if(s2.find(*it) != s2.end()){
            compiledSet.insert(*it);
        }
    }
    return compiledSet;



}
//finds the products of the two sets which either set has
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{

    std::set<T> compiledSet;
    //iterates through both products and adds all values to the set
    typename std::set<T>::iterator it;
    for(it = s1.begin(); it != s1.end(); it++){
        compiledSet.insert(*it);
    }
    for(it = s2.begin(); it != s2.end(); it++){
        compiledSet.insert(*it);
    }
    
    return compiledSet; 


}



std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
