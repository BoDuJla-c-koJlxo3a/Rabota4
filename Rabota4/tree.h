#pragma once
#include "linlist.h"
#include <string>

template <class T> class Tree;


template <class T> class Node {

private:

	T* data;
	int num;
	Node* left;
	Node* right;

public:

	Node() {
		T* data = new T;
		num = 0;
		left = 0;
		right = 0;
	}

	Node(T item) {
		data = new T;
		*data = item;
		num = 1;
		left = 0;
		right = 0;
	}

	~Node() {
		delete data;
	}

	void Increment() {
		num++;
	}

	T Get() {
		return *data;
	}

	void SetL(Node<T>* ptr) {
		left = ptr;
	}

	void SetR(Node<T>* ptr) {
		right = ptr;
	}

	Node<T>* GetL() {
		return left;
	}

	Node<T>* GetR() {
		return right;
	}
};





template <class T> class Walker {
private:

	LinkedList<Node<T>*>* stack;
	Node<T>* now;

public:

	Walker() {
		stack = 0;
		now = 0;
	}

	~Walker() {
		delete stack;
	}

	Node<T>* KLP(Node<T>* ptr) {
		if (ptr) {
			delete stack;
			stack = new LinkedList<Node<T>*>();
			now = ptr;
			return now;
		}
		if (!now) {
			return 0;
		}
		if (now->GetR()) {
			stack->Prepend(now->GetR());
		}
		if (!(now->GetL())) {
			if (!stack->GetLength()) {
				return 0;
			}
			now = stack->pop();
			return now;
		}
		else {
			now = now->GetL();
			return now;
		}
	}

	Node<T>* KPL(Node<T>* ptr) {
		if (ptr) {
			delete stack;
			stack = new LinkedList<Node<T>*>();
			now = ptr;
			return now;
		}
		if (!now) {
			return 0;
		}
		if (now->GetL()) {
			stack->Prepend(now->GetL());
		}
		if (!(now->GetR())) {
			if (!stack->GetLength()) {
				return 0;
			}
			now = stack->pop();
			return now;
		}
		else {
			now = now->GetR();
			return now;
		}
	}
	
	Node<T>* LKP(Node<T>* ptr, int mode) { //0 - reset 1 - norm
		if (mode == 0) {
			delete stack;
			stack = new LinkedList<Node<T>*>();
		}
		Node<T>*cur = ptr;
		if (mode == 1) {
			if (!stack->GetLength()) {
				return 0;
			}
			return stack->pop();
		}
		if (cur->GetL()) {
			LKP(cur->GetL(), 2);
		}
		stack->Append(cur);
		if (cur->GetR()) {
			LKP(cur->GetR(), 2);
		}
		if (mode == 0) {
			return stack->pop();
		}
		return 0;
	}

	Node<T>* PKL(Node<T>* ptr, int mode) { //0 - reset 1 - norm
		if (mode == 0) {
			delete stack;
			stack = new LinkedList<Node<T>*>();
		}
		Node<T>* cur = ptr;
		if (mode == 1) {
			if (!stack->GetLength()) {
				return 0;
			}
			return stack->pop();
		}
		if (cur->GetR()) {
			LKP(cur->GetR(), 2);
		}
		stack->Append(cur);
		if (cur->GetL()) {
			LKP(cur->GetL(), 2);
		}
		if (mode == 0) {
			return stack->pop();
		}
		return 0;
	}


	Node<T>* LPK(Node<T>* ptr, int mode) { //0 - reset 1 - norm
		if (mode == 0) {
			delete stack;
			stack = new LinkedList<Node<T>*>();
		}
		Node<T>* cur = ptr;
		if (mode == 1) {
			if (!stack->GetLength()) {
				return 0;
			}
			return stack->pop();
		}
		if (cur->GetL()) {
			LPK(cur->GetL(), 2);
		}
		if (cur->GetR()) {
			LPK(cur->GetR(), 2);
		}
		stack->Append(cur);
		if (mode == 0) {
			return stack->pop();
		}
		return 0;
	}

	Node<T>* PLK(Node<T>* ptr, int mode) { //0 - reset 1 - norm
		if (mode == 0) {
			delete stack;
			stack = new LinkedList<Node<T>*>();
		}
		Node<T>* cur = ptr;
		if (mode == 1) {
			if (!stack->GetLength()) {
				return 0;
			}
			return stack->pop();
		}
		if (cur->GetL()) {
			PLK(cur->GetL(), 2);
		}
		if (cur->GetR()) {
			PLK(cur->GetR(), 2);
		}
		stack->Append(cur);
		if (mode == 0) {
			return stack->pop();
		}
		return 0;
	}
};




template <class T> class Tree {
private: 

	Node<T>* root;

public:

	Tree() {
		root = 0;
	}

	Tree(T item) {
		root = new Node<T>(item);
	}

	~Tree() {
		if (!root) {
			delete root;
		}
	}

	Node<T>* getRoot() {
		return root;
	}

	void Put(T info) {
		Node<T>* item = new Node<T>(info);
		if (!root) {
			root = item;
			return;
		}
		Node<T> *now = 0, *next = root;
		while (next) {
			now = next;
			if (info == now->Get()) {
				now->Increment();
				return;
			}
			if (info < now->Get()) {
				next = now->GetL();
			}
			if (info > now->Get()) {
				next = now->GetR();
			}
		}
		if (info < now->Get()) {
			now->SetL(item);
		}
		else {
			now->SetR(item);
		}
	 }

	Tree<T>* merge(const Tree<T>* origin) {
		Tree<T>* out = new Tree<T>();
		Walker<T>* a = new Walker<T>();
		Node<T>* now = a->KLP(this->root);
		while (!now) {
			out->Put(*now);
			now = a->KLP(0);
		}
		now = a->KLP(origin);
		while (!now) {
			out->Put(*now);
			now = a->KLP(0);
		}
		delete a;
		return out;
	}

	Tree<T>* getSubTree(T item) {
		Tree<T>* out = new Tree<T>();
		Walker<T>* a = new Walker<T>();
		Node<T>* now = a->KLP(this->root);
		while (now) {
			if (now->Get() == item) {
				break;
			}
			now = a->KLP(0);
		}
		if (!now) {
			delete a;
			return 0;
		}
		now = a->KLP(now);
		while (now) {
			out->Put(now->Get());
			now = a->KLP(0);
		}
		delete a;
		return out;
	}

	bool includesItem(T item) {
		Walker<T>* a = new Walker<T>();
		Node<T>* now = a->KLP(this->root);
		while (now) {
			if (*now == item) {
				delete a;
				return true;
			}
			now = a->KLP(0);
		}
		delete a;
		return false;
	}

	std::string* toString(int walkIndex) {
		Walker<T>* a = new Walker<T>();
		std::string* s = new std::string();
		Node<T>* now;
		switch (walkIndex) {
		case 1:
			now = a->KLP(this->root);
			while (now) {
				*s = *s + std::to_string(now->Get());
				*s = *s + ' ';
				now = a->KLP(0);
			}
			break;
		case 2:
			now = a->KPL(this->root);
			while (now) {
				*s = *s + std::to_string(now->Get());
				*s = *s + ' ';
				now = a->KPL(0);
			}
			break;
		case 3:
			now = a->LKP(this->root, 0);
			while (now) {
				*s = *s + std::to_string(now->Get());
				*s = *s + ' ';
				now = a->LKP(0, 1);
			}
			break;
		case 4:
			now = a->PKL(this->root, 0);
			while (now) {
				*s = *s + std::to_string(now->Get());
				*s = *s + ' ';
				now = a->PKL(0, 1);
			}
			break;
		case 5:
			now = a->LPK(this->root, 0);
			while (now) {
				*s = *s + std::to_string(now->Get());
				*s = *s + ' ';
				now = a->LPK(0, 1);
			}
			break;
		case 6:
			now = a->PLK(this->root, 0);
			while (now) {
				*s = *s + std::to_string(now->Get());
				*s = *s + ' ';
				now = a->LPK(0, 1);
			}
			break;
		}
		delete a;
		return s;
	}
};


template <typename T>
Tree<T>* TreeWhere(bool (*filter)(T), Tree<T>* origin) {
	Tree<T>* out = new Tree<T>();
	Walker<T>* a = new Walker<T>();
	Node<T>* now = a->KLP(origin->getRoot());
	while (now) {
		if (filter(now->Get())) {
			out->Put(now->Get());
		}
		now = a->KLP(0);
	}
	delete a;
	return out;
}

template <typename T>
Tree<T>* map(T(*func)(T), Tree<T>* origin) {
	Tree<T>* out = new Tree<T>();
	Walker<T>* a = new Walker<T>();
	Node<T>* now = a->KLP(origin->getRoot());
	while (now) {
		out->Put(func(now->Get()));
		now = a->KLP(0);
	}
	delete a;
	return out;
}