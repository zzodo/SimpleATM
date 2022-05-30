#ifndef SIMPLEATM_CARD_H
#define SIMPLEATM_CARD_H

#pragma once

#include <functional>
#include <string>
#include <memory>

namespace SimpleATM {
    class Card {
    public:
        Card() = default;
        explicit Card(std::string bank, std::string number, std::string name, int exp_date) :
            bank_(bank), number_(std::stoll(number)), name_(name), exp_date_(exp_date) {};

        std::string GetCardBank() const;
        std::string GetCardName() const;
        uint64_t GetCardNumber() const;

        bool operator==(const Card& other) const;
        struct HashFunction {
            size_t operator()(const std::shared_ptr<Card> card) const{
                return std::hash<uint64_t>()(card->number_);
            }
        };
    private:
        std::string bank_; // A
        uint64_t number_; // 1234567812345678
        std::string name_; // Dohoon Cho
        int exp_date_; // YYYYMM
    };
}

#endif //SIMPLEATM_CARD_H
