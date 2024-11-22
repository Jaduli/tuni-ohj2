#include "book.hh"
#include <string>
#include <iostream>

Book::Book(const std::string& author, const std::string& name):
    name_(name), author_(author) {

}

void Book::print() {
    std::cout << author_ << " : " << name_ << std::endl;

    if (loaned_ == false) {
        std::cout << "- available" << std::endl;
    }
    else {
        std::cout << "- loaned: ";
        loan_date_.print();

        std::cout << "- to be returned: ";
        return_date_.print();
    }
}

void Book::loan(Date& day) {
    if (loaned_ == false) {
        loan_date_ = day;
        return_date_ = day;
        return_date_.advance(28);
        loaned_ = true;
    }
    else {
        std::cout << "Already loaned: cannot be loaned" << std::endl;
    }
}

void Book::renew() {
    if (loaned_ == true) {
        return_date_.advance(28);
    }
    else {
        std::cout << "Not loaned: cannot be renewed" << std::endl;
    }
}

void Book::give_back() {
    if (loaned_ == true) {
        loaned_ = false;
    }
}
