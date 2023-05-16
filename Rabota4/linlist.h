#pragma once
#include <iostream>

template <class T> class element {
public:
	T item;
	element* next;
};

template <class T> class LinkedList {

private:

	element<T>* head;
	element<T>* tail;
	int size;

public:

	LinkedList(T* items, int count) {
		if (count <= 0) {
			size = 0;
			head = 0;
			tail = 0;
			throw(-1);     //zero-length list
		}
		size = count;
		element<T>* prev = new element<T>;
		head = prev;
		element<T>* el = 0;
		prev->item = *items;
		for (int i = 1; i < count; i++) {
			el = new element<T>;
			el->item = items[i];
			prev->next = el;
			prev = el;
		}
		el->next = 0;
		tail = el;
	}

	LinkedList() {
		size = 0;
		head = 0;
		tail = 0;
	}

	LinkedList(const LinkedList <T> &list) {
		if (list.size <= 0) {
			size = 0;
			head = 0;
			tail = 0;
			throw(-1);     //zero-length list
		}
		size = list.size;
		element<T>* prev = new element<T>;
		head = prev;
		element<T>* el = 0;
		element<T>* ptr = list.head;
		prev->item = ptr->item;
		while (ptr != list.tail) {
			el = new element<T>;
			ptr = ptr->next;
			el->item = ptr->item;
			prev->next = el;
			prev = el;
		}
		el->next = 0;
		tail = el;
	}

	~LinkedList() {
		size = 0;
		element<T>* prev = 0;
		element<T>* ptr = head;
		while (ptr != tail) {
			prev = ptr;
			ptr = ptr->next;
			delete prev;
		}
		delete ptr;
	}

	T GetFirst() {
		if (size <= 0 || !head) {
			throw(-1);     //zero-length list
		}
		return head->item;
	}

	T GetLast() {
		if (size <= 0 || !tail) {
			throw(-1);     //zero-length list
		}
		return tail->item;
	}

	T Get(int index) {
		if (size <= 0 || !head) {
			throw(-1);     //zero-length list
		}
		if (index >= size) {
			throw(index);  //out of range
		}
		element<T>* ptr = head;
		for (int i = 0; i < index; i++) {
			ptr = ptr->next;
		}
		return ptr->item;
	}

	int GetLength() {
		return size;
	}

	LinkedList<T>* GetSubList(int startIndex, int endIndex) {
		if (startIndex < 0 || endIndex < 0 || startIndex >= size || endIndex >= size) {
			throw(1);     // index out of range;
		}
		if (startIndex > endIndex) {
			throw(-1);    // wrong order
		}
		LinkedList<T>* list = new LinkedList();
		list->size = endIndex - startIndex + 1;
		element<T>* ptr = head;
		int i = 0;
		for (i = 0; i < startIndex; i++) {
			ptr = ptr->next;
		}
		element<T>* prev = new element<T>;
		element<T>* el = 0;
		list->head = prev;
		prev->item = ptr->item;
		while (i != endIndex) {
			el = new element<T>;
			ptr = ptr->next;
			el->item = ptr->item;
			prev->next = el;
			prev = el;
			i++;
		}
		el->next = 0;
		list->tail = el;
		return list;
	}

	void Prepend(T item) {
		element<T>* el = new element<T>;
		el->item = item;
		if (!head) {
			tail = el;
		}
		el->next = head;
		head = el;
		size++;
	}

	void Append(T item) {
		element<T>* el = new element<T>;
		el->item = item;
		el->next = 0;
		if (!head) {
			head = el;
			tail = el;
		}
		else {
			tail->next = el;
			tail = el;
		}
		size++;
	}

	void InsertAt(T item, int index) {
		if (index < 0 || index > size) {
			throw(index); //index out of range
		}
		size++;
		if (index == 0) {
			this->Prepend(item);
			return;
		}
		if (index == size - 1) {
			this->Append(item);
			return;
		}
		element<T>* ptr = head;
		for (int i = 1; i < index; i++) {
			ptr = ptr->next;
		}
		element<T>* el = new element<T>;
		el->item = item;
		el->next = ptr->next;
		ptr->next = el;
	}

	LinkedList<T>* Concat(const LinkedList<T>* list) {
		LinkedList<T>* out1 = new LinkedList<T>(*this);
		LinkedList<T>* out2 = new LinkedList<T>(*list);
		out1->size += out2->size;
		out1->size--;
		out1->tail->next = out2->head;
		out1->tail = out2->tail;
		delete out2;
		return out1;
	}

	T pop() {
		if (!head) {
			throw(0); //zero-length
		}
		element<T>* prev = head;
		T info = head->item;
		head = prev->next;
		size--;
		if (size <= 0) {
			tail = 0;
		}
		delete prev;
		return info;
	}
};