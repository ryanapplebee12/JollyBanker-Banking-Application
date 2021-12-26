#ifndef FUND_H_
#define FUND_H_
#include "Transaction.h"
#include <vector>
#include <iostream>

#include <iostream>

class Fund {
public:
	Fund(int num, string asset);

	// getters and setters
	int GetBalance();
	void ChangeBalance(int num);
	void AddTransactionToHistory(Transaction t);
	void PrintTransactions() const;
	void PrintFund() const;

	// Overloaded operators
	friend ostream& operator<<(ostream& stream, Fund rhs);
private:
	int balance_;
	string asset_;
	vector<Transaction> transactions_;
};
#endif
