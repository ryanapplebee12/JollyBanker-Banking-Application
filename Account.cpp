#include "Account.h"
#include <iostream>
using namespace std;

Account::Account(int id, string name) {
	id_ = id;
	name_ = name;

	// Construct all 8 funds
	Fund one(0, "Money Market");
	Fund two(0, "Prime Money Market");
	Fund three(0, "Long-Term Bond");
	Fund four(0, "Short-Term Bond");
	Fund five(0, "500 Index Fund");
	Fund six(0, "Capital Value Fund");
	Fund seven(0, "Growth Equity Fund");
	Fund eight(0, "Growth Index Fund");

	funds_.push_back(one);
	funds_.push_back(two);
	funds_.push_back(three);
	funds_.push_back(four);
	funds_.push_back(five);
	funds_.push_back(six);
	funds_.push_back(seven);
	funds_.push_back(eight);
}

// Implement fund sharing later
bool Account::Withdraw(int asset, int amount, Transaction t) {
	// If the asset number is less than 4, the asset is linked to another one and must be processed differently in WithdrawHelper()
	if (asset < 4) {
		bool successful = false;
		if ( (funds_[asset].GetBalance()) < amount) {
			successful = WithdrawHelper(asset, amount);
			if (!successful) {
				cerr << "ERROR: Insufficient Funds!" << endl;
			}
			return successful;
		}
		
		
	}

	// If the fund has sufficient balance, the money will be withdrawn
	if (funds_[asset].GetBalance() >= amount) {
		amount = -amount;
		funds_[asset].ChangeBalance(amount);
		this->AddTransaction(asset, t);
		return true;
	}
	else {
		t.SetSuccess(false);
		this->AddTransaction(asset, t);
		cerr << "ERROR: Insufficient Funds!" << endl;
		return false;
	}
}

bool Account::Deposit(int asset, int amount) {
	// Increase amount in fund balance
	funds_[asset].ChangeBalance(amount);
	return true;
}

void Account::Print() const {
	cout << this;
}

void Account::PrintAccountHistory() const {
	cout << "Transaction History for " << this->name_ << "by fund." << endl;
	for (int i = 0; i < 8; i++) {
		this->funds_[i].PrintTransactions();
	}
	cout << endl;
}

void Account::PrintFundHistory(int asset) const {
	cout << "Transaction History for " << this->name_;
	this->funds_[asset].PrintFund();
	cout << endl;
}

//This is called in the Withdraw methods to add a withdraw transaction to a fund
void Account::AddTransaction(int asset, Transaction t) {
	funds_[asset].AddTransactionToHistory(t);
}

ostream& operator<<(ostream& stream, const Account& rhs) {
	stream << "Name: " << rhs.name_ << " Account ID: " << rhs.id_ << endl;
	for (int i = 0; i < 8; i++) {
		stream << "    " << rhs.funds_[i] << endl;
	}
	return stream;
}

bool Account::WithdrawHelper(int asset, int amount) {
	int balance;
	int linked_balance;
	
	// If asset is less than two, than I'm handling fund 0 and fund 1
	if (asset < 2) {

		if (asset == 0) {
			balance = funds_[asset].GetBalance();
			linked_balance = funds_[1].GetBalance();
			if ((balance + linked_balance) >= amount) {

				// Make new transaction based on partial withdrawals
				string command1 = "W " + to_string(this->id_) + " " + to_string(asset) + " " + to_string(balance);
				Transaction t1(command1, true);

				string command2 = "W " + to_string(this->id_) + " " + to_string(1) + " " + to_string((amount - balance));
				Transaction t2(command2, true);

				this->AddTransaction(asset, t1);
				this->AddTransaction(1, t2);
				
				// Calculate difference and subtract amounts from each fund
				int difference = (amount - balance) * -1;
				balance = -balance;
				funds_[asset].ChangeBalance(balance);
				funds_[1].ChangeBalance(difference);
				return true;
			}
			else {
				return false;
			}
		}
		else {
			// Same thing but fund 1 is now the fund that doesn't have sufficient funds and needs help from fund 0 to cover it
			balance = funds_[asset].GetBalance();
			linked_balance = funds_[0].GetBalance();
			if ((balance + linked_balance) >= amount) {

				string command1 = "W " + to_string(this->id_) + " " + to_string(asset) + " " + to_string(balance);
				Transaction t1(command1, true);

				string command2 = "W " + to_string(this->id_) + " " + to_string(0) + " " + to_string((amount - balance));
				Transaction t2(command2, true);

				this->AddTransaction(asset, t1);
				this->AddTransaction(0, t2);

				int difference = (amount - balance) * -1;
				balance = -balance;
				funds_[asset].ChangeBalance(balance);
				funds_[0].ChangeBalance(difference);
				return true;
			}
			else {
				return false;
			}
		}
	}

	if (asset == 2) {
		balance = funds_[asset].GetBalance();
		linked_balance = funds_[3].GetBalance();
		if ((balance + linked_balance) >= amount) {

			string command1 = "W " + to_string(this->id_) + " " + to_string(asset) + " " + to_string(balance);
			Transaction t1(command1, true);

			string command2 = "W " + to_string(this->id_) + " " + to_string(3) + " " + to_string((amount - balance));
			Transaction t2(command2, true);

			this->AddTransaction(asset, t1);
			this->AddTransaction(3, t2);

			int difference = (amount - balance) * -1;
			balance = -balance;
			funds_[asset].ChangeBalance(balance);
			funds_[3].ChangeBalance(difference);
			return true;
		}
		else {
			return false;
		}
	}
	else {
		balance = funds_[asset].GetBalance();
		linked_balance = funds_[2].GetBalance();
		if ((balance + linked_balance) >= amount) {

			string command1 = "W " + to_string(this->id_) + " " + to_string(asset) + " " + to_string(balance);
			Transaction t1(command1, true);

			string command2 = "W " + to_string(this->id_) + " " + to_string(2) + " " + to_string((amount - balance));
			Transaction t2(command2, true);

			this->AddTransaction(asset, t1);
			this->AddTransaction(2, t2);

			int difference = (amount - balance) * -1;
			balance = -balance;
			funds_[asset].ChangeBalance(balance);
			funds_[2].ChangeBalance(difference);
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}