#include "atm.h"

namespace SimpleATM {
    bool Atm::AddNewBank(const Bank &bank) {
        if (std::find(banks_.begin(), banks_.end(), bank) != banks_.end())
            return false;
        banks_.push_back(bank);
        return true;
    }

    void Atm::Run() {
        bool terminate = false, return_home;
        while (!terminate) {
            std::shared_ptr<Card> card_inserted;
            std::vector<std::shared_ptr<Account>> accounts_found;
            std::shared_ptr<Account> account_selected;
            return_home = false;

            PrintInitialMenu();

            card_inserted = InsertCard(terminate);
            if (terminate) break;

            accounts_found = FindAccountsFromCard(card_inserted, return_home);
            if (return_home) continue;

            PrintAccounts(accounts_found);

            account_selected = SelectAccount(accounts_found, return_home);
            if (return_home) continue;

            auto option = SelectOperationOption(return_home);
            if (return_home) continue;

            OperateSelectedOption(account_selected, option);
            std::cout << std::endl << std::endl;
        }
    }

    void Atm::PrintInitialMenu() {
        std::cout << "========================================" << std::endl;
        std::cout << "          Welcome to SimpleATM          " << std::endl;
        std::cout << "                                        " << std::endl;
        std::cout << "   -- Insert your card to continue --   " << std::endl;
        std::cout << "========================================" << std::endl;
    }

    std::shared_ptr<Card> Atm::InsertCard(bool &terminate) {
        std::shared_ptr<Card> card_inserted;

        std::cout << "Type your card number(type 't' to terminate): ";
        std::string card_number;
        std::getline(std::cin, card_number);
        if (card_number == "t") {
            terminate = true;
            return {};
        }

        std::cout << "Checking your card...";
        bool card_found = false;
        if (card_number.size() > 0) {
            for (auto &bank : banks_) {
                if (bank.FindCard(static_cast<uint64_t>(std::stoll(card_number)), card_inserted)) {
                    card_found = true;
                    break;
                }
            }
        }
        if (card_found) {
            std::cout << "  OK!" << std::endl << std::endl;
            return card_inserted;
        }
        else {
            std::cout << std::endl << "The card number does not exist. Please try again." << std::endl << std::endl;
            return InsertCard(terminate);
        }
    }

    std::vector<std::shared_ptr<Account>> Atm::FindAccountsFromCard(std::shared_ptr<Card> card, bool &return_home) {
        std::vector<std::shared_ptr<Account>> accounts_found;

        std::cout << "Enter PIN number(type 'r' to return to home): ";
        std::string pin;
        std::getline(std::cin, pin);
        if (pin == "r") {
            return_home = true;
            return {};
        }

        std::cout << "Checking PIN number...";
        if (pin.size() > 0) {
            for (auto &bank : banks_) {
                if (bank.CheckCardPin(card, std::stoi(pin)))
                    accounts_found = bank.FindAccounts(card, std::stoi(pin));
            }
        }
        if (accounts_found.size() > 0) {
            std::cout << "  OK!" << std::endl << std::endl;
            return accounts_found;
        }
        else {
            std::cout << std::endl << "Invalid PIN number. Please try again.\n"  << std::endl;
            FindAccountsFromCard(card, return_home);
        }
    }

    void Atm::PrintAccounts(std::vector<std::shared_ptr<Account>> accounts) {
        std::cout << "--- Your accounts ---" << std::endl;
        for (int i = 1; i <= accounts.size(); i++) {
            std::ostringstream account_oss;
            account_oss << std::setw(10) << std::setfill('0') << accounts[i - 1]->GetAccountNumber();
            std::cout << i << ": " << account_oss.str() << std::endl;
        }
        std::cout << "---------------------" << std::endl;
    }

    std::shared_ptr<Account> Atm::SelectAccount(std::vector<std::shared_ptr<Account>> accounts, bool &return_home) {
        std::shared_ptr<Account> account_selected;

        std::string num_s;
        std::cout << "Select account(type 'r' to return to home): ";
        std::getline(std::cin, num_s);
        if (num_s == "r") {
            return_home = true;
            return {};
        }

        int num = std::stoi(num_s);
        if (num > 0 && num <= accounts.size()) {
            account_selected = accounts[num - 1];
            std::cout << std::endl << "Selected account: " << account_selected->GetAccountNumber()
                      << "(Bank: " << account_selected->GetAccountBank() << ")\n" << std::endl;
            return account_selected;
        }
        else {
            std::cout << "Invalid account. Please try again.\n" << std::endl;
            SelectAccount(accounts, return_home);
        }
    }

    int Atm::SelectOperationOption(bool &return_home) {
        std::cout << "--- Which operation do you want? ---" << std::endl;
        std::cout << "1: Deposit" << std::endl;
        std::cout << "2: Withdraw" << std::endl;
        std::cout << "3: See balance" << std::endl;
        std::cout << "------------------------------------" << std::endl;

        std::string option;
        std::cout << "Select option(type 'r' to return to home): ";
        std::getline(std::cin, option);
        if (option == "r") {
            return_home = true;
            return 0;
        }

        if (std::stoi(option) > 0 && std::stoi(option) < 4)
            return std::stoi(option);
        else {
            std::cout << "Invalid operation. Please try again" << std::endl;
            SelectOperationOption(return_home);
        }
    }

    void Atm::OperateSelectedOption(std::shared_ptr<Account> account, int option) {
        int dollars = 0;
        int balance = 0;
        switch (option) {
            case 1:
                std::cout << "Enter dollars to be deposited in your account: ";
                std::cin >> dollars;
                std::cin.ignore();
                balance = account->Deposit(dollars);

                std::cout << "--- Deposit result ---" << std::endl;
                std::cout << "Input dollars: " << dollars << std::endl;
                std::cout << "Balance before deposit: " << balance - dollars << std::endl;
                std::cout << "Balance after deposit: " << balance << std::endl;
                std::cout << "----------------------" << std::endl;
                std::cout << "Please collect your card from the reader." << std::endl;
                break;
            case 2:
                std::cout << "Enter dollars to be withdrawn in your account: ";
                std::cin >> dollars;
                std::cin.ignore();
                balance = account->Withdraw(dollars);

                if (balance < 0) {
                    std::cout << "Not enough balance." << std::endl;
                    std::cout << "Please collect your card from the reader." << std::endl;
                }
                else {
                    std::cout << "--- Withdraw result ---" << std::endl;
                    std::cout << "Withdrawn dollars: " << dollars << std::endl;
                    std::cout << "Balance before Withdraw: " << balance + dollars << std::endl;
                    std::cout << "Balance after Withdraw: " << balance << std::endl;
                    std::cout << "-----------------------" << std::endl;
                    std::cout << "Please collect your card and money from the reader." << std::endl;
                }
                break;
            case 3:
                std::cout << "--- Your balance ---" << std::endl;
                std::cout << account->GetBalance() << std::endl;
                std::cout << "--------------------" << std::endl;
                std::cout << "Please collect your card from the reader." << std::endl;
                break;
            default:
                std::cout << "Unexpected error" << std::endl;
                break;
        }
    }
}