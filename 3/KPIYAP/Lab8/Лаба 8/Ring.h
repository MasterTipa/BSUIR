#include "Employee.h"
#include"Exepcion.h"
#include<iostream>

using namespace std;

class  Node
{
public:
	Employee data;
	Node* next;
	Node* prev;
	Node() : data(), next(nullptr), prev(nullptr) { }
	Node(Employee value) : data(value), next(nullptr), prev(nullptr) { }
};

class Ring : public Node
{
private:
	Node* head;
	int size;
public:
	Ring() : head(nullptr), size(0) { };
	void input(Employee value) {

		Node* newNode = new Node(value);
		newNode->next = head;
		if (head != nullptr) {
			newNode->prev = head->prev;
			head->prev->next = newNode;
			head->prev = newNode;
		}
		else {
			newNode->next = newNode;
			newNode->prev = newNode;
			head = newNode;
		}
	}
	void show() {
		try {
			if (size == 0)
			{
				throw 3;
			}
		}
		catch (int i)
		{
			Exception ex(i);
			ex.Print();
			return;
		}
		Node* it = head;
		do {
			cout << ' ' << it->data;
			it = it->next;
		} while (it != head);
		cout << '\n';
	}
	Node* get_node() {
		return this->head;
	}
	void del()
	{
		try {
			if (head == nullptr)
				throw 3;
		}
		catch (int i) {
			Exception ex(i);
			ex.Print();
		}
		Node* temp = head;
		if (head->next != head->prev) {
			head->next->prev = head->prev;
			head->prev->next = head->next;
			head = head->next;
		}
		else {
			head = nullptr;
		}
		delete temp;
	}

	friend ostream& operator<<(ostream& out, const Node& node);
};

class Iterator
{
private:
	Node* node;
public:
	friend Ring;
	~Iterator() { }
	Iterator(Ring* element) {
		this->node = element->get_node();
	}

	Iterator& operator++() {
		try {
			if (node == nullptr)
			{
				throw 3;
			}
		}
		catch (int i)
		{
			Exception ex(i);
			ex.Print();
		}
		node = node->next;
		return *this;
	}
	Employee operator*() {
		try {
			if (node == nullptr)
			{
				throw 3;
			}
		}
		catch (int i)
		{
			Exception ex(i);
			ex.Print();
		}
		return node->data;
	}

	friend ostream& operator<<(ostream& out, const Iterator& it);
};