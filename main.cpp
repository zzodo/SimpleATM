#include "atm.h"
#include "bank.h"

namespace SimpleATM {
    std::vector<Bank> MakeExampleBankSystem() {
        auto thomas_a1 = std::make_shared<Account>("A", "Thomas", "1111111111", 0);
        auto lewis_a1 = std::make_shared<Account>("A", "Lewis", "2222222222", 1300);
        auto lewis_a2 = std::make_shared<Account>("A", "Lewis", "3333333333", 500);
        auto david_a1 = std::make_shared<Account>("A", "David", "4444444444", 1000);
        auto john_a1 = std::make_shared<Account>("A", "John", "5555555555", 1200);
        auto john_a2 = std::make_shared<Account>("B", "John", "6666666666", 700);

        auto thomas_c1 = std::make_shared<Card>("A", "0000111122223333", "Thomas", 202508);
        auto lewis_c1 = std::make_shared<Card>("A", "0000111122224444", "Lewis", 202701);
        auto david_c1 = std::make_shared<Card>("A", "0000111122225555", "David", 202207);
        auto david_c2 = std::make_shared<Card>("A", "0000111122226666", "David", 202310);
        auto john_c1 = std::make_shared<Card>("A", "0000111133336666", "John", 202411);
        auto john_c2 = std::make_shared<Card>("B", "0000111144446666", "John", 202212);

        auto bank_a = Bank("A");
        bank_a.AddNewAccount(thomas_a1);
        bank_a.AddNewAccount(lewis_a1);
        bank_a.AddNewAccount(lewis_a2);
        bank_a.AddNewAccount(david_a1);
        bank_a.AddNewAccount(john_a1);
        bank_a.AddNewCard(thomas_c1, 123456, thomas_a1);
        bank_a.AddNewCard(lewis_c1, 111111, lewis_a1);
        bank_a.AddNewCard(lewis_c1, 111111, lewis_a2);
        bank_a.AddNewCard(david_c1, 102030, david_a1);
        bank_a.AddNewCard(david_c2, 102030, david_a1);
        bank_a.AddNewCard(john_c1, 246800, john_a1);

        auto bank_b = Bank("B");
        bank_b.AddNewAccount(john_a2);
        bank_b.AddNewCard(john_c2, 246800, john_a2);

        std::vector<Bank> banks;
        banks.push_back(bank_a);
        banks.push_back(bank_b);
        return banks;
    }
}

int main() {
    auto banks = SimpleATM::MakeExampleBankSystem();
    SimpleATM::Atm atm_example(banks);

    atm_example.Run();
    return 0;
}
