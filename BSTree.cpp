#include "BSTree.h"
#include <iostream>
using namespace std;


BSTree::BSTree() {
	root = nullptr;
}

BSTree::~BSTree() {
	// Destructor calls the Empty() method which deletes all the pointers and nodes in the tree
	this->Empty();
}
bool BSTree::Insert(int id, Account* account) {
	// If the root is empty, create a new node and make it the root node
	if (root == nullptr) {
		Node* temp = new Node{id, account, nullptr, nullptr};
		root = temp;
		return true;
	}

	Node* current = root;
	bool searching = true;
	while (searching) {

		// Check for duplicates
		if (id == current->p_id) {
			cerr << "ERROR: THERE IS ALREADY AN ACCOUNT WITH THIS ID!" << endl;
			searching = false;
			return false;
		}

		// If id is less than current, it must go left of the current node
		if (id < current->p_id) {
			// If there is nothing left of the currrent node, insert the Node into this spot
			if (current->left == nullptr) {
				Node* temp = new Node{ id, account, nullptr, nullptr };
				current->left = temp;
				searching = false; 
				return true;
			}
			else {
				current = current->left;
			}
		}
		// same logic is used if the id is greater than the current node
		else if (id > current->p_id) {
			if (current->right == nullptr) {
				Node* temp = new Node{ id, account, nullptr, nullptr };
				current->right = temp;
				searching = false;
				return true;
			}
			else {
				current = current->right;
			}
		}
	}
	
	return false;
}
bool BSTree::Retrieve(const int id, Account*& account) const {
	return (RetrieveHelper(id, account, this->root));
}

bool BSTree::RetrieveHelper(const int id, Account*& account, Node* current) const {
	if (current == nullptr) {
		cerr << "ERROR: Account could not be found" << endl;
		return false;
	}

	// If node passed in is the correct account, return it
	if (id == current->p_id) {
		account = current->pAcct;
		return true;
	}

	// Search left and right side of tree
	if (id < current->p_id) {
		RetrieveHelper(id, account, current->left);
	}

	if (id > current->p_id) {
		RetrieveHelper(id, account, current->right);
	}

	return false;
}

void BSTree::Display()const {
	InorderPrint(this->root);
}
void BSTree::Empty() {
	PostOrderDelete(this->root);
}
bool BSTree::isEmpty() const {
	if (root == nullptr) {
		return true;
	}
	return false;
}

// Prints the tree In Order. It's best to use In Order traversal so that the accounts will be printed in ascending order
void BSTree::InorderPrint(Node* current) const {
	if (current == nullptr) {
		return;
	}

	InorderPrint(current->left);
	cout << *current->pAcct << endl;
	InorderPrint(current->right);
}

// Deletes the tree in Post Order. It's best to use post order for this because the leaf nodes should be deleted before the roots
void BSTree::PostOrderDelete(Node* current) {

	if (current == nullptr) {
		return;
	}

	PostOrderDelete(current->left);
	PostOrderDelete(current->right);
	delete current->pAcct;
	current->left = NULL;
	current->right = NULL;
	delete current;
	current = NULL;

}
