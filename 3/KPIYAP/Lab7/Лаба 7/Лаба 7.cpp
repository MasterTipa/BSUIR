#include <iostream>
#include <string>
#include <exception>
#include<time.h>
#include <cstdlib>        

using namespace std;

template <class T>
class Stac;

class Kotik {
private:
	int id;
	string name;
	string diagnos;
public:
	Kotik() :id(0), name("Blank "), diagnos("Blank ") { }
	Kotik(string t_name, string t_diagnos, int id) :name(t_name), diagnos(t_diagnos), id(id) { }
	~Kotik() { }
	bool operator< (const Kotik& kot) { return id < kot.id; }
	bool operator> (const Kotik& kot) { return id > kot.id; }
	bool operator== (const Kotik& kot) { return id == kot.id && name == kot.name; }
	friend ostream& operator<< (ostream& out, const Kotik& Kotik)
	{
		out << Kotik.id << ' ' << Kotik.name << ' ' << Kotik.diagnos << '\n'; return out;
	}

};

class Exception
{
public:
	Exception(const string errorMessage = "Something wrong") : m_ErrorMessage(errorMessage) { }
	friend ostream& operator<< (ostream& out, const Exception& ex) { out << ex.m_ErrorMessage << '\n'; return out; }
private:
	string m_ErrorMessage;
};

template <class T>
struct Node {
	T value;
	Node* left, * right;
	Node() : value() { left = right = nullptr; }
};

template <class T>
class Iterator
{
public:
	friend class Stac<T>;
	//friend void swomp(Iterator<T> , Iterator<T> );
	Iterator(Node<T>* node = nullptr) : node(node) { }
	~Iterator() { }
	Iterator(const Iterator& it) { node = it.node; }
	Iterator& operator=(const Iterator& it) { node = it.node; return *this; }
	T& operator*() {
		if (node == nullptr)
			throw Exception("Empty iterator");
		return node->value;
	}
	T* operator->() { if (node == nullptr) throw Exception("Empty iterator"); return &node->value; }
	Iterator& operator++() { if (node == nullptr) throw Exception("Empty iterator"); node = node->right; return *this; }
	Iterator& operator--() { if (node == nullptr) throw Exception("Empty iterator"); node = node->left; return *this; }
	Iterator operator++(int unused) { if (node == nullptr) throw Exception("Empty iterator"); Iterator res = *this; node = node->right; return res; }
	Iterator operator--(int unused) { if (node == nullptr) throw Exception("Empty iterator"); Iterator res = *this; node = node->left; return res; }
	bool operator== (const Iterator& it) { return node == it.node; }
	bool operator!= (const Iterator& it) { return node != it.node; }
public:
	Node<T>* node;
};

template<class T>
class Stac
{
public:
	typedef Iterator<T> Iterator;
public:
	Stac() : head(nullptr) {}
	~Stac()
	{/*
		Node<T>* it = head;
		while (it != nullptr) {
			Node<T>* temp = it;
			it = it->left;
			temp->right = nullptr;
			delete temp;
		}*/
	}
	void push(T value, bool unique = false)
	{
		if (unique) {
			Iterator it = find(value);
			if (!(it == null())) {
				throw Exception("duplicate value find");
			}
		}
		Node<T>* newNode = new Node<T>();
		newNode->value = value;
		newNode->right = nullptr;
		newNode->left = nullptr;
		if (head != nullptr) {
			head->right = newNode;
			newNode->left = head;
		}
		head = newNode;
	}
	void pop()
	{
		if (head == nullptr)
			throw Exception("Stuck is empty");
		Node<T>* temp = head;
		head = head->left;
		head->right = nullptr;
		delete temp;
	}
	Iterator erase(Iterator);
	Iterator find(T value) const;
	void show() const;
	void show(Iterator) const;
	Iterator begin() { return Iterator(head); }
	Iterator null() { return Iterator(); }
	void swap(Iterator, Iterator);
private:
	Node<T>* head;
};

template<class T>
typename Stac<T>::Iterator Stac<T>::erase(Stac<T>::Iterator it)
{
	if (head == nullptr)
		throw Exception("Stuck is empty");
	if (it == null())
		throw Exception("Invalid iterator");
	Node<T>* temp = it.node;
	if (it.node->left != nullptr) {
		it.node = it.node->left;
		it.node->right = temp->right;
		if (temp->right != nullptr)
			temp->right->left = it.node;
		delete temp;
		return it;
	}
	else {
		Node<T>* temp = it.node;
		it.node = it.node->right;
		it.node->left = nullptr;
		delete temp;
		return it;
	}
}

template<class T>
typename Stac<T>::Iterator Stac<T>::find(T value) const
{
	Node<T>* it = head;
	do
	{
		if (it->value == value)
			return Iterator(it);
		it = it->left;
	} while (it != nullptr);
	return Iterator();
}

template<class T>
void Stac<T>::show() const
{
	Node<T>* it = head;
	while (it->right != nullptr) it = it->right;
	do
	{
		cout << ' ' << it->value;
		it = it->left;
	} while (it != nullptr);
	cout << '\n';
}

template<class T>
void Stac<T>::show(Iterator it) const
{
	while (it.node->right != nullptr) it.node = it.node->right;
	do
	{
		cout << ' ' << it.node->value;
		it.node = it.node->left;
	} while (it.node != nullptr);
	cout << '\n';
	/*Node<T>* it = head;
	while (it->right != nullptr) it = it->right;
	do
	{
		cout << ' ' << it->value;
		it = it->left;
	} while (it != nullptr);
	cout << '\n';*/
}

template<class T>
void Stac<T>::swap(Stac<T>::Iterator it1, Stac<T>::Iterator it2) {
	Node<T>* temp = nullptr;

	if (it2.node->right) it2.node->right->left = it1.node;
	temp = it1.node->right;
	it1.node->right = it2.node->right;
	it2.node->right = temp;
	if (temp) temp->left = it2.node;
	if (it2.node->left) it2.node->left->right = it1.node;
	temp = it1.node->left;
	it1.node->left = it2.node->left;
	it2.node->left = temp;
	if (temp) temp->right = it2.node;

	if (this->head == it1.node) {
		this->head = it2.node;
	}
	if (this->head == it2.node) {
		this->head = it1.node;
	}
}

template<class T>
void fastSort(Iterator<T> begin, Iterator<T> end, Stac<T> stac)
{
	if (begin == Iterator<T>())
		throw Exception("Invalid iterator");
	if (end == Iterator<T>())
		throw Exception("Invalid iterator");
	if (begin == end) return;
	Iterator<T> bgn=begin;
	Iterator<T> nd=end;
	for (Iterator<T> i =begin;i!=end;i--)
	{
		if (*i < *bgn) 
		{
			stac.swap(i,bgn);
			begin = i;
			bgn = i;
			//stac.show();
		}
	}
	for (Iterator<T> i = end;i != begin;i++)
	{
		if (*i>*nd)
		{
			stac.swap(i, nd);
			end = i;
			nd = i;
		//	stac.show();
		}
	}
	//stac.show();
	begin--;
	fastSort(begin, end, stac);
	begin++;end++;
	fastSort(begin, end, stac);
	return;
	//while (stac.head->right != nullptr) stac.head = stac.head->right;
}

//
//template<class T>
//void swomp(Iterator<T> it1, Iterator<T> it2)
//{
//	/*if(it2.node->right)
//		it2.node->right->left = it1.node;
//	Node<T>* temp = it1.node->right;
//	it1.node->right = it2.node->right;
//	it2.node->right = temp;
//	if(temp)
//		temp->left = it2.node;
//	temp = it1.node->left;
//	it1.node->left = it2.node->left;
//	if(it2.node->left && temp)
//		it2.node->left->right = temp->right;
//	it2.node->left = temp;
//	if(temp) temp->right = it2.node;*/
//
//	
//	Node<T>* temp = nullptr;
//
//	if(it2.node->right) it2.node->right->left = it1.node;
//	temp = it1.node->right;
//	it1.node->right = it2.node->right;
//	it2.node->right = temp;
//	if(temp) temp->left = it2.node;
//	if(it2.node->left) it2.node->left->right = it1.node;
//	temp = it1.node->left;
//	it1.node->left = it2.node->left;
//	it2.node->left = temp;
//	if(temp) temp->right = it2.node;
//	
//}

void my_terminate() {
	cerr << "terminate handler called\n";
	abort();
}

void my_unexpected_handler()
{
	cerr << "Unexpected exception\n";
	terminate();
}

int main() {
	srand(time(NULL));
	set_terminate(my_terminate);
	set_unexpected(my_unexpected_handler);
	Stac<Kotik> stac;
	try {
		stac.pop();
	}
	catch (Exception ex) {
		cerr << ex;
	}
	cout << "\nInserting\n";
	try {
		stac.push(Kotik("Stas", "Beba", 11));
		stac.show();
		stac.push(Kotik("Danila", "Beba", 20),true);
		stac.show();
		stac.push(Kotik("Anzelika", "Beba", 6),true);
		stac.show();
		stac.push(Kotik("Kek", "Beba", 5),true);
		stac.show();
		stac.push(Kotik("Max", "Beba", 7),true);
		stac.show();
		stac.push(Kotik("Xim", "Beba", 8),true);
		stac.show();
		stac.push(Kotik("Xim", "Beba", 8), true);
		stac.show();
	}
	catch (Exception ex) { cerr << ex; }
	try {
		stac.pop();
		stac.show();
		stac.show(stac.begin());
		try {
			cout << "\nErase Kek Beba 5\n";
			stac.erase(stac.find(Kotik("Kek", "Beba", 5)));
		}
		catch (Exception ex) { cerr << ex; };
		stac.show();
		try {
			auto dan = stac.find(Kotik("Max", "Beba", 7));
			auto anz = stac.find(Kotik("Anzelika", "Beba", 6));
			stac.swap(dan, anz);
		}
		catch (Exception ex) { cerr << ex; };
		stac.show();
		try {
			Stac<Kotik>::Iterator bgn = stac.begin();
			Stac<Kotik>::Iterator end = stac.begin();
			while (end.node->left != nullptr) end--;
			fastSort(bgn, end, stac);
		}
		catch (Exception ex) { cerr << ex; };
		cout << "\nAfter Sorting\n";
		stac.show();
	}
	catch (Exception ex) { cerr << ex; }
	cout << "\nNew Temp\n";
	try {
		Stac<double> stac1;
		try {
			stac1.push(4);
			stac1.show();
			stac1.push(2,true);
			stac1.show();
			stac1.push(1,true);
			stac1.show();
			stac1.push(0,true);
			stac1.show();
			stac1.push(3,true);
			stac1.show();
			stac1.push(7,true);
			stac1.show();
			stac1.push(7, true);
			stac1.show();
		}
		catch (Exception ex) {
			cerr << ex;
		}
		try {
			Stac<double>::Iterator bgn = stac1.begin();
			Stac<double>::Iterator end = stac1.begin();
			while (end.node->left != nullptr) end--;
			fastSort(bgn, end, stac1);
		}
		catch (Exception ex) { cerr << ex; };
		cout << "\nAfter Sorting\n";
		stac1.show();
	}
	catch (Exception ex) { cerr << ex; };
	return 0;
}