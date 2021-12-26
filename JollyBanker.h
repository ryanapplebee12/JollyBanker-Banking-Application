#ifndef JOLLYBANKER_H_
#define JOLLYBANKER_H_
#include <vector>
#include <iostream>
#include <queue>
#include "BSTree.h"
#include "Account.h"
#include "Transaction.h"

using namespace std;

class JollyBanker {
public:

	JollyBanker();
	void ReadFile(string file);
	void ProcessCommands(Transaction t);
	

private:
	queue<Transaction> commands_;
	BSTree accounts_;

};
#endif
