#include <iostream>
#include <string>
#include <exception>
#include<time.h>
#include <cstdlib>	

template<class S>
class Stract;

template<typename S>
S input() {
	S i;
	bool fail = true;
	//	std::cout << "\nInput:";
	do
	{
		std::cin >> i;
		if (std::cin.fail() || std::cin.rdbuf()->in_avail() > 1)
			std::cout << "\nError" << std::endl;
		else
			fail = false;
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
	} while (fail);
	return i;
}

template<class S>
struct STR
{
	S data;
	STR* right ,* left;
	STR() :data() { left = right = nullptr; };
};

class Kotik {
private:
	int id;
	std::string name;
	std::string diagnos;
public:
	Kotik() :id(rand() % 100), name("Blank"), diagnos("Bebebes bababa") {};
	Kotik(std::string t_name, std::string t_diagnos) :
		id(rand() % 100), name(t_name), diagnos(t_diagnos) {};
	~Kotik() {};
	bool operator<(const Kotik& kot) { return id < kot.id; };
	bool operator==(const Kotik& kot) { return id == kot.id; };
	friend std::ostream& operator<<(std::ostream& out, const Kotik& kot) {
		out << kot.id << " " << kot.name << " " << kot.diagnos;
		return out;
	};

};
class Exception
{
public:
	Exception(const std::string errorMessage = "Something wrong") : m_ErrorMessage(errorMessage) { }
	friend std::ostream& operator<< (std::ostream& out, const Exception& ex) { out << ex.m_ErrorMessage << '\n'; return out; }
private:
	std::string m_ErrorMessage;
};
template <class S>
class Iterator
{
public:
	friend class Stract<S>;
	Iterator(STR<S>* node=nullptr) : node(node) {};
	~Iterator() {};
	Iterator(const Iterator& it) { node = it.node; }
	Iterator& operator=(const Iterator& it) { node = it.node; return *this; }
	S& operator*() { if (node == nullptr) 
		throw Exception("Empty iterator");	
	return node->data; }
	S* operator->() { if (node == nullptr)
		throw Exception("Empty iterator");
	return &node->data; }
	Iterator& operator++() { if (node == nullptr) 
		throw Exception("Empty iterator"); 
	if (node->right != nullptr)
		node = node->right;
	else throw Exception("Not a way");
	return *this; }
	Iterator& operator--() { if (node == nullptr)
		throw Exception("Empty iterator"); 
	if (node->left != nullptr)
		node = node->left;
	else throw Exception("Not a way");
	return *this; }
	Iterator operator++(int unused) { 
		if (node == nullptr) 
			throw Exception("Empty iterator");
		Iterator res = *this; 
		node = node->right;
		return res; }
	Iterator operator--(int unused) { 
		if (node == nullptr) 
			throw Exception("Empty iterator");
		Iterator res = *this;
		node = node->left; 
		return res; }
	bool operator== (const Iterator& it) { return node == it.node; }
	bool operator!= (const Iterator& it) { return node != it.node; }
private:
	STR<S>* node;
};

template<class S>
class Stract
{
public:
	typedef :: Iterator<S> Iterator;
	Stract() :head(nullptr) {};
	~Stract() 
	{
		STR<S>* temp = head;
		while (temp->right != nullptr)
			temp = temp->right;
		while(temp!=nullptr)
		{
			STR<S>* ss=temp;
			temp = temp->left;
			temp->right = nullptr;
			delete ss;
		}
	};
	void push_right(S zn, bool unique)
	{
		if (unique) {
			Iterator it = find(zn);
			if (it != null()) {
				throw Exception("duplicate value find");
			}
		}
		STR<S>* t_head = new STR<S>();
		t_head->right = nullptr;
		t_head->data = zn;
		t_head->left = nullptr;
		if (head != nullptr)
		{
			head->right = t_head;
			t_head->left = head;
			//t_head->right = nullptr;
		}
		head = t_head;
	};
	void pop_right()
	{
		if (head == nullptr)
			throw Exception("Stract is empty");
		STR<S>* temp = head;
		head = head->left;
		head->right = nullptr;
		delete temp;
	};
	Iterator find(S data) const {
		STR<S>* it = head;
		do
		{
			if (it->data == data)
				return Iterator(it);
			it = it->left;
		} while (it != nullptr);
		return Iterator();
	};
	void search() 
	{
		Iterator xz = head;
		std::cout << *xz;
		xz--;
		std::cout << *xz;
		xz++;
		std::cout << *xz;
	
		
	};
	void out() const
	{
		STR<S>* it = head;
		do
		{
			std::cout << ' ' << it->data;
			it = it->left;
		} while (it != nullptr);
		std::cout << '\n';
	};
	Iterator begin() { return Iterator(head); }
	Iterator null() { return Iterator(); }
private:
	STR<S>* head;
};


int main()
{
	Stract<Kotik> kot;
	kot.push_right(Kotik("Bebebe", " S Bababa"),0);
	kot.push_right(Kotik("Bebebe", " SBababa"),0);
	kot.push_right(Kotik("Bebebe", "S Bababa"),0);
	kot.out();
	kot.pop_right();
	kot.out();
	

}