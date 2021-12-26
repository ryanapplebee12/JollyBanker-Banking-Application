#include "JollyBanker.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

void ProcessCommands(string command);
void ReadFile(string file);


JollyBanker::JollyBanker() {
    
}

int main(int argc, char* argv[])
{
    // Make sure correct input is inputted into the command line
    if (argc == 2) {
        string file = argv[1];
        JollyBanker bank;
        bank.ReadFile(file);
    }
    else {
        cerr << "ERROR: Incorrect amount of parameters inputted into the command line!" << endl;
    }

}

void JollyBanker::ProcessCommands(Transaction t) {
    string command = t.GetCommand();
    // Split command by whitespace that way it's easier to get information from the transaction
    stringstream stream(command);
    string word;
    queue <string> tokens;
    while (stream >> word) {
        tokens.push(word);
    }
    string letter = tokens.front();
    tokens.pop();
    string temp = tokens.front();
    // Convert string to int
    int id = stoi(temp);
    tokens.pop();

    // Check what the first letter of the transaction command is to determine which method in Account needs to be called
    if (letter == "O") {
        string name2 = tokens.front() + " ";
        tokens.pop();
        string name = tokens.front();
        tokens.pop();
        name += " ";
        name += name2;
        Account* account = new Account(id, name);
        // Insert account into BST
        accounts_.Insert(id, account); 
        return;
    }

    // Deposit is called when D is the first letter
    if (letter == "D") {
        int fund = stoi(tokens.front());
        tokens.pop();
        int amount = stoi(tokens.front());
        tokens.pop();
        // Find correct account and call Deposit() method if the account isnt NULL
        Account* account{};
        accounts_.Retrieve(id, account);
        if (account != NULL) {
            t.SetSuccess(account->Deposit(fund, amount));
            account->AddTransaction(fund, t);  
        }
        else {
            t.SetSuccess(false);
        }
        return;
    }

    // Withdraw is called when W is the first letter
    if (letter == "W") {
        int fund = stoi(tokens.front());
        tokens.pop();
        int amount = stoi(tokens.front());
        tokens.pop();
        Account* account{};
        accounts_.Retrieve(id, account);
        if (account != NULL) {
            // I pass in the transaction object that way I can handle creating transactions for withdrawals for linked assets
            account->Withdraw(fund, amount, t);
            return;
        }
    }

    if (letter == "T") {
        // Figure out what funds are being used in the transfer
        int f1 = stoi(tokens.front());
        tokens.pop();
        int id2 = stoi(tokens.front());
        tokens.pop();
        int f2 = stoi(tokens.front());
        tokens.pop();
        int amount = stoi(tokens.front());
        Account* account{};
        accounts_.Retrieve(id, account);

        if (account != NULL) {
            bool withdraw_success = account->Withdraw(f1, amount, t);
            t.SetSuccess(withdraw_success);
            // If withdrawal is successful then the program can proceed to depositing the withdrawed money into the correct fund
            if (withdraw_success) {
                Account* account2{};
                accounts_.Retrieve(id2, account2);
                if (account2 != NULL) {
                    account2->Deposit(f2, amount);
                    //Add transaction to fund
                    account2->AddTransaction(f2, t);
                }
                else {
                    account->Deposit(f1, amount);
                    t.SetSuccess(false);
                }
            }
             
        }
        return;
    }

    // Print account's history of transactions
    if (letter == "A") {
        Account* account{};
        accounts_.Retrieve(id, account);
        if (account != NULL) {
            account->PrintAccountHistory();
        }
        return;
    }

    // Prints the specific history of a fund's transactions
    if (letter == "F") {
        Account* account{};
        accounts_.Retrieve(id, account);
        int f = stoi(tokens.front());
        tokens.pop();
        if (account != NULL) {
            account->PrintFundHistory(f);
        }

    }

}

// Reads commands in from a file and pushes them to a Queue in the form of Transaction objects
void JollyBanker::ReadFile(string file) {
    // Read input from file
    ifstream my_file;
    my_file.open(file);
    string input;
    while (!my_file.eof()) {
        getline(my_file, input);
        // Make a new transaction for each line in the file and push it to the queue
        Transaction t(input, true);
        commands_.push(t);
    }
    while (!commands_.empty()) {
        // Call a method to process the transactions in the queue
        ProcessCommands(commands_.front());
        commands_.pop();
    }
    // Print final balances
    cout << endl;
    cout << "FINAL BALANCES:" << endl;
    accounts_.Display();
}



