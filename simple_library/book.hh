#ifndef BOOK_HH
#define BOOK_HH
#include <string>
#include <date.hh>


class Book
{
public:
    Book(const std::string& author, const std::string& name);

    void print();
    void loan(Date& day);
    void renew();
    void give_back();


private:
    std::string name_;
    std::string author_;

    bool loaned_ = false;
    Date loan_date_;
    Date return_date_;
};

#endif // BOOK_HH
