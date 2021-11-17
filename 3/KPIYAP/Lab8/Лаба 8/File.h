#pragma once
#include <iostream>
#include <fstream>
#include <string>


#include"Exepcion.h"
#include "Employee.h"

using namespace std;


enum Key {
	none = 0,
	txt,
	bin
};

class File
{
private:
	fstream file;
	string path;
	Key key; //none txt bin
	int size;
public:
	File() :path("Space"), key(none), size(0) {}
	File(string path, Key key) {
		this->path = path;
		this->key = key;
		this->size = 0;
	}
	~File() { file.close(); }


	void open(string mode) {
		switch (key) {
		case txt: {
			if (mode == "r") {
				file.open(path, ios_base::in);
			}
			else if (mode == "add") {
				file.open(path, ios_base::app);
			}
			else if (mode == "w") {
				file.open(path, ios_base::out);
			}
			else if (mode == "wr") {
				file.open(path, ios_base::in | ios_base::out);
			}
		}
				break;
		case bin: {
			if (mode == "r") {
				file.open(path, ios_base::binary | ios_base::in);
			}
			else if (mode == "add") {
				file.open(path, ios_base::binary | ios_base::app);
			}
			else if (mode == "w") {
				file.open(path, ios_base::binary | ios_base::out);
			}
			else if (mode == "wr") {
				file.open(path, ios_base::binary | ios_base::in | ios_base::out);
			}
		}
				break;
		}
		try {
			if (!file.is_open())
			{
				throw 1;
			}
		}
		catch (int i)
		{
			Exception ex(i);
			ex.Print();
			exit(-1);
			return;
		}
	}
	void close() {
		file.close();
	}
	void begin() {
		file.seekg(0, ios_base::beg);
	}
	void set_size(int s) {
		size = s;
	}
	int get_size() {
		return	size;
	}

	void sort_name();
	void sort_id_num();
	void sort_hour_num();
	void sort_payment_num();
	void search(File);
	void edit(int line, Employee[]);

	Employee return_uni() {
		string str;
		int i1;
		Employee uni;

		getline(this->file, str, ' ');
		uni.set_employee_name(str);
		getline(this->file, str, ' ');
		i1 = stoi(str);
		uni.set_id_num(i1);
		getline(this->file, str, ' ');
		i1 = stoi(str);
		uni.set_hour_num(i1);
		getline(this->file, str);
		i1 = stoi(str);
		uni.set_payment_num(i1);
		return uni;
	}

	friend File& operator<<(File& file, const char* s);
	friend ostream& operator<<(ostream& out, File& file);
	friend File& operator<<(File& file, Employee& uni);

};