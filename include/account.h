#ifndef SIMPLEATM_ACCOUNT_H
#define SIMPLEATM_ACCOUNT_H

#include <unordered_set>
#include <string>
#include <memory>

namespace SimpleATM {
    class Account {
    public:
        Account() = default;
        explicit Account(std::string bank, std::string name, std::string number, int balance = 0) :
            bank_(bank), name_(name), number_(std::stoll(number)), balance_(balance) {};

        std::string GetAccountName() const;
        std::string GetAccountNumber() const;
        std::string GetAccountBank() const;
        int GetBalance();
        int Deposit(int dollars);
        int Withdraw(int dollars);

        bool operator==(const Account& other) const;
        struct HashFunction {
            size_t operator()(const std::shared_ptr<Account> account) const{
                return std::hash<uint64_t>()(account->number_);
            }
        };
    private:
        std::string bank_;
        std::string name_; // username
        uint64_t number_; // account number
        int balance_;
    };
}

#endif //SIMPLEATM_ACCOUNT_H
