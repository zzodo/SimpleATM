#include "card.h"

namespace SimpleATM {
    std::string Card::GetCardBank() const {
        return bank_;
    }

    std::string Card::GetCardName() const {
        return name_;
    }

    uint64_t Card::GetCardNumber() const {
        return number_;
    }

    bool Card::operator==(const Card &other) const {
        if (bank_ == other.bank_ && name_ == other.name_ && number_ == other.number_ && exp_date_ == other.exp_date_)
            return true;
        return false;
    }
}