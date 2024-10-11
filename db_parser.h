#ifndef DBPARSER_H
#define DBPARSER_H
#include <iostream>
#include <string>
#include <map>
#include "datastore.h"
#include "product.h"
#include "user.h"
#include "product_parser.h"


class SectionParser {
public:
    virtual ~SectionParser() { }
 
    virtual bool parse(std::istream& is, DataStore& ds,
                       int& lineno, std::string& errorMsg) = 0;
    
    virtual void reportItemsRead(std::ostream& os) = 0;
};


class DBParser {
public:
    DBParser();
    ~DBParser();
  
    void addSectionParser(const std::string& sectionName,
                          SectionParser*         parser);
   
    bool parse(std::string db_filename, DataStore& ds);

private:
    enum PState { FIND_SECTION, IN_SECTION };
    int lineno_;
    std::string errorMsg_;
    bool error_;
    std::map<std::string, SectionParser*> parsers_;

};



class ProductSectionParser : public SectionParser
{
public:
    ProductSectionParser();
    ~ProductSectionParser();
    virtual bool parse(std::istream& is, DataStore& ds,
                       int& lineno, std::string& errorMsg);
    virtual void reportItemsRead(std::ostream& os);
    void addProductParser(ProductParser* p);
protected:
    Product* parseProduct(const std::string& category,
                          std::istream& is,
                          int& lineno,
                          std::string& errorMsg);
private:
    std::map<std::string, ProductParser*> prodParsers_;
    unsigned int numRead_ ;
};


class UserSectionParser : public SectionParser
{
public:
    UserSectionParser();
    ~UserSectionParser() {}
    virtual bool parse(std::istream& is, DataStore& ds,
                       int& lineno, std::string& errorMsg);
    virtual void reportItemsRead(std::ostream& os);
protected:
    User* parseUser(
        std::istream& is,
        DataStore& ds,
        std::string& errorMsg);
private:

    unsigned int numRead_ ;

};
#endif
