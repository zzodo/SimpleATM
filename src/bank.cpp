#include "bank.h"

namespace SimpleATM {
    bool Bank::AddNewAccount(std::shared_ptr<Account> account) {
        if (name_ != account->GetAccountBank()) {
            std::cout << "Invalid account registration. Bank should be matched." << std::endl;
            return false;
        }

        if (accounts_.count(account)) {
            std::cout << "Account already exists in Bank " << name_ << "!" << std::endl;
            return false;
        }
        accounts_.insert(account);
        return true;
    }

    bool Bank::AddNewCard(std::shared_ptr<Card> card, int pin, std::shared_ptr<Account> account) {
        if (!(card->GetCardName() == account->GetAccountName())) {
            std::cout << "Names of account and card are different." << std::endl;
            return false;
        }
        else if (!(card->GetCardBank() == account->GetAccountBank() && card->GetCardBank() == name_)) {
            std::cout << "Bank names of account and card do not match." << std::endl;
            return false;
        }

        if (cards_.count(card))
            if (card_accounts_[card].count(account))
                return false;
            else
                card_accounts_[card].insert(account);
        else {
            cards_[card] = pin;
            card_accounts_[card].insert(account);
        }

        return true;
    }

    bool Bank::FindCard(uint64_t card_number, std::shared_ptr<Card> &card) {
        for (auto &c : cards_)
            if (card_number == c.first->GetCardNumber()) {
                card = c.first;
                return true;
            }

        return false;
    }

    bool Bank::CheckCardPin(std::shared_ptr<Card> card, int pin) {
        if (cards_[card] != pin)
            return false;

        return true;
    }

    std::vector<std::shared_ptr<Account>> Bank::FindAccounts(const std::shared_ptr<Card> card, int pin) {
        if (CheckCardPin(card, pin)) {
            auto accounts = card_accounts_[card];
            std::vector<std::shared_ptr<Account>> accounts_v;
            for (std::unordered_set<std::shared_ptr<Account>, Account::HashFunction>::iterator it = accounts.begin(); it != accounts.end(); it++)
                accounts_v.push_back(*it);

            return accounts_v;
        }
        else
            return {};
    }

    bool Bank::operator==(const Bank &other) const {
        if (name_ == other.name_)
            return true;
        return false;
    }
}
