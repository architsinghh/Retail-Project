#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}


std::set<std::string> parseStringToWords(string rawWords)
{
    cout<< rawWords << endl;
    string trimmedString = trim(rawWords);
    convToLower(trimmedString);
    string wordsWithPunc = "";
    int count = 0;
    
    set<string> keywords;
    //loops through the word and inserts keywords into keywords set
    for(int i = 0; i <= trimmedString.length(); i++){
        //checks if we have encountered a punctuation or space
        if(i == trimmedString.length() || trimmedString[i] == ' ' || ispunct(trimmedString[i])){
            cout << rawWords << " " << i << endl;
            //checks if the word we have is 2 characters or more
            if(count >= 2){
                keywords.insert(trim(wordsWithPunc));
                wordsWithPunc = "";
                count = 0;
            }
            //resets current word and count if word is lower than two characters
            else{
                wordsWithPunc = "";
                count = 0;
            }
        }
        //adds to word if there is no punctuation
        else if(!ispunct(trimmedString[i])){
            wordsWithPunc += trimmedString[i];
            count++;
        }
    }
    return keywords;
}



// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
