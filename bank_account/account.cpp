#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit):
    name_(owner), is_credit_(has_credit) {
    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

void Account::set_credit_limit(int amount) {
    if (is_credit_) {
        credit_ = amount;
    }
    else {
        std::cout << "Cannot set credit limit: the account has no credit card" << std::endl;
    }
}

void Account::save_money(int amount) {
    money_ += amount;

}


void Account::take_money(int amount) {
    if (amount <= money_ + credit_) {
        money_ -= amount;
        std::cout << amount << " euros taken: new balance of " << get_iban() << " is " << money_ << " euros" << std::endl;
    }
    else {
        std::cout << "Cannot take money: balance underflow" << std::endl;
    }
}

void Account::transfer_to(Account& tranfer_account, int amount) {
    take_money(amount);

    if (money_ + credit_ >= amount) {
        tranfer_account.save_money(amount);
    }

    else {
        std::cout << "Transfer from " << get_iban() << " failed" << std::endl;
    }
}

std::string Account::get_name() const {
    return name_;
}

std::string Account::get_iban() const {
    return iban_;
}

void Account::print() const {
    std::cout << Account::get_name() << " : " << Account::get_iban() << " : " << money_ << " euros" << std::endl;
}
