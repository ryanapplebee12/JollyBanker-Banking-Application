#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include <string>
#include <iostream>
#include "Fund.h"
#include <vector>
#include"Transaction.h"
using namespace std;

class Account {
public:
	Account(int id, string name);
	friend ostream& operator<<(ostream& stream, const Account& rhs);

	bool Withdraw(int asset, int amount, Transaction t);
	bool Deposit(int asset, int amount);
	void Print() const;
	void PrintAccountHistory() const;
	void PrintFundHistory(int asset) const;
	void AddTransaction(int asset, Transaction t);

private:
	int id_;
	string name_;
	vector<Fund> funds_;
	bool WithdrawHelper(int asset, int amount);
};
#endif


