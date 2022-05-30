#include "account.h"

namespace SimpleATM {
    std::string Account::GetAccountName() const {
        return name_;
    }

    std::string Account::GetAccountNumber() const {
        return std::to_string(number_);
    }

    std::string Account::GetAccountBank() const {
        return bank_;
    }

    int Account::GetBalance() {
        return balance_;
    }

    int Account::Deposit(const int dollars) {
       return balance_ += dollars;
    }

    int Account::Withdraw(const int dollars) {
        if (balance_ < dollars)
            return (balance_ - dollars);
        return balance_ -= dollars;
    }

    bool Account::operator==(const Account &other) const {
        if (bank_ == other.bank_ && name_ == other.name_ && number_ == other.number_)
            return true;
        return false;
    }
}
