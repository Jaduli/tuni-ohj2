#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <string>

class Account
{
public:
    // Constructor
    Account(const std::string& owner, bool has_credit = false);

    // More methods
    void print() const;
    void set_credit_limit(int amount);
    void save_money(int amount);
    void take_money(int amount);
    void transfer_to(Account& tranfer_account, int amount);

private:
    // Generates IBAN (based on running_number_ below).
    // Allows no more than 99 accounts.
    void generate_iban();

    // Used for generating IBAN.
    // Static keyword means that the value of running_number_ is the same for
    // all Account objects.
    // In other words, running_number_ is a class-wide attribute, there is
    // no own copies of it for each object of the class.
    static int running_number_;

    // More attributes/methods
    std::string name_;
    std::string iban_;
    bool is_credit_;
    int credit_ = 0;
    int money_ = 0;

    std::string get_name() const;
    std::string get_iban() const;
    int get_saldo() const;
};

#endif // ACCOUNT_HH
