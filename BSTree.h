#ifndef BSTREE_H_
#define BSTREE_H_
#include "Account.h"

class BSTree {
	
	struct Node
	{
		int p_id;
		Account* pAcct;
		Node* left;
		Node* right;
	};

public:
	BSTree();
	~BSTree();
	bool Insert(int id, Account* account);
	bool Retrieve(const int id, Account*& account) const;

	void Display()const;
	void Empty();
	bool isEmpty() const; 

private:
	
	Node* root;
	void InorderPrint(Node* root_node) const;
	bool RetrieveHelper(const int id, Account*& account, Node* current) const;
	void PostOrderDelete(Node* current);
};

#endif