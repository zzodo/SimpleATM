#ifndef SIMPLEATM_ATM_H
#define SIMPLEATM_ATM_H

#include <climits>
#include <iostream>
#include <iomanip>

#include "bank.h"

namespace SimpleATM {
    class Atm {
    public:
        Atm() = default;
        explicit Atm(std::vector<Bank> banks) : banks_(banks) {};

        bool AddNewBank(const Bank &bank);
        void Run();
    private:
        void PrintInitialMenu();
        std::shared_ptr<Card> InsertCard(bool &terminate);
        std::vector<std::shared_ptr<Account>> FindAccountsFromCard(std::shared_ptr<Card> card, bool &return_home);
        void PrintAccounts(std::vector<std::shared_ptr<Account>> accounts);
        std::shared_ptr<Account> SelectAccount(std::vector<std::shared_ptr<Account>> accounts, bool &return_home);
        int SelectOperationOption(bool &return_home);
        void OperateSelectedOption(std::shared_ptr<Account> account, int option);

        std::vector<Bank> banks_;
    };
}

#endif //SIMPLEATM_ATM_H
