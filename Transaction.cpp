#include "Transaction.h"
#include <iostream>

Transaction::Transaction(string command, bool success) {
	command_ = command;
	success_ = success;
}

string Transaction::GetCommand() {
	return command_;
}

bool Transaction::GetSuccess() {
	return success_;
}

void Transaction::SetSuccess(bool success) {
	success_ = success;
}

ostream& operator <<(ostream& stream, const Transaction rhs) {
	stream << rhs.command_;
	if (!rhs.success_) {
		stream << " (Failed)";
	}
	return stream;
}