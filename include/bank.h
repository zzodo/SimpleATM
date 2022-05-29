#ifndef SIMPLEATM_BANK_H
#define SIMPLEATM_BANK_H

#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "account.h"
#include "card.h"

namespace SimpleATM {
    class Bank {
    public:
        Bank() = default;
        explicit Bank(std::string name) : name_(name) {};

        bool AddNewAccount(std::shared_ptr<Account> account);
        bool AddNewCard(std::shared_ptr<Card> card, int pin, std::shared_ptr<Account> account);
        bool FindCard(uint64_t card_number, std::shared_ptr<Card> &card);
        bool CheckCardPin(std::shared_ptr<Card> card, int pin);
        std::vector<std::shared_ptr<Account>> FindAccounts(std::shared_ptr<Card> card, int pin);

        bool operator==(const Bank& other) const;
    private:
        std::string name_;

        std::unordered_set<std::shared_ptr<Account>, Account::HashFunction> accounts_;
        std::unordered_map<std::shared_ptr<Card>, int, Card::HashFunction> cards_; // <card, pin>
        std::unordered_map<std::shared_ptr<Card>, std::unordered_set<std::shared_ptr<Account>, Account::HashFunction>, Card::HashFunction> card_accounts_; // <card, accounts>
    };
}

#endif //SIMPLEATM_BANK_H
