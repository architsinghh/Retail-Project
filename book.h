#include <iostream>
#include <string>
#include "util.h"
#include "product.h"

class Book : public Product{
    public:
        Book(const std::string category, const std::string name, double price, int qty, const std::string authorName, const std::string ISBN);
        std::set<std::string> keywords() const;
        std::string displayString() const;
        void dump(std::ostream& os) const;
      



    protected:
        std::string authorName_;
        std::string ISBN_;
};

