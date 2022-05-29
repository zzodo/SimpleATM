#include <iostream>

#include "atm.h"
#include "bank.h"

namespace SimpleATM {
    std::vector<Bank> MakeExampleBankSystem() {
        auto thomas_1 = std::make_shared<Account>("A", "Thomas", "1111111111", 0);
        auto thomas_2 = std::make_shared<Account>("A", "Thomas", "1111122222", 100);
        auto lewis_1 = std::make_shared<Account>("A", "Lewis", "2222222222", 1300);
        auto lewis_2 = std::make_shared<Account>("A", "Lewis", "2222233333", 500);
        auto lewis_3 = std::make_shared<Account>("A", "Lewis", "3333333333", 150);
        auto david_1 = std::make_shared<Account>("A", "David", "4444444444", 1000);
        auto thomas = std::make_shared<Card>("A", "0000111122223333", "Thomas", 202508);
        auto lewis = std::make_shared<Card>("A", "0000111122224444", "Lewis", 202701);
        auto david = std::make_shared<Card>("A", "0000111122225555", "David", 202207);

        auto bank_a = Bank("A");
        bank_a.AddNewAccount(thomas_1);
        bank_a.AddNewAccount(thomas_2);
        bank_a.AddNewAccount(lewis_1);
        bank_a.AddNewAccount(lewis_2);
        bank_a.AddNewAccount(lewis_3);
        bank_a.AddNewAccount(david_1);
        bank_a.AddNewCard(thomas, 123456, thomas_1);
        bank_a.AddNewCard(thomas, 123456, thomas_2);
        bank_a.AddNewCard(lewis, 111111, lewis_1);
        bank_a.AddNewCard(lewis, 111111, lewis_2);
        bank_a.AddNewCard(lewis, 111111, lewis_3);
        bank_a.AddNewCard(david, 001122, david_1);

        std::vector<Bank> banks;
        banks.push_back(bank_a);
        return banks;
    }
}

int main() {
    auto banks = SimpleATM::MakeExampleBankSystem();
    SimpleATM::Atm atm_example(banks);

    atm_example.Run();
    return 0;
}
