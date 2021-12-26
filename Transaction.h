#ifndef TRANSACTION_H_
#define TRANSACTION_H_
#include <string>
#include <iostream>
using namespace std;

class Transaction {
public:
	Transaction(string command, bool success);
	string GetCommand();
	bool GetSuccess();
	void SetSuccess(bool success);
	friend ostream& operator <<(ostream& stream, const Transaction rhs);

private:
	string command_;
	bool success_;
};
#endif
