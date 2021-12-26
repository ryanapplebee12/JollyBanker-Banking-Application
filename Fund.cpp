#include "Fund.h"
#include <iostream>

Fund::Fund(int num, string asset) {
	balance_ = num;
	asset_ = asset;
}

void Fund::ChangeBalance(int num) {
	balance_ += num;
}

int Fund::GetBalance() {
	return balance_;
}

void Fund::AddTransactionToHistory(Transaction t) {
	transactions_.push_back(t);
}

void Fund::PrintTransactions() const {
	if (!transactions_.size() > 0) {
		return;
	}
	cout << this->asset_ << ": $" << this->balance_ << endl;
	for (int i = 0; i < transactions_.size(); i++) {
		cout << "  " << transactions_[i] << endl;
	}
}

void Fund::PrintFund() const {
	cout << this->asset_ << ": " << to_string(this->balance_) << endl;
	for (int i = 0; i < transactions_.size(); i++) {
		cout << "  " << transactions_[i] << endl;
	}
}

ostream& operator<<(ostream& stream, Fund rhs) {
	stream << rhs.asset_ << ": $" << rhs.balance_;
	return stream;
}