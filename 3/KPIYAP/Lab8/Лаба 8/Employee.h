#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


class Employee
{
private:
	string employee_name;
	int id_num;
	int hour_num;
	double payment_num;

public:
	Employee() :employee_name("Space"), id_num(0), hour_num(0), payment_num(0) {}
	Employee(string employee_name, int id_num, int hour_num, double payment_num) {
		this->employee_name = employee_name;
		this->id_num = id_num;
		this->hour_num = hour_num;
		this->payment_num = payment_num;
	}
	~Employee() {}

	friend ostream& operator<<(ostream& out, const Employee& uni);
	friend istream& operator>>(istream& in, Employee& uni);
	friend bool operator==(const Employee C1, const Employee C2);

	string get_employee_name();
	int get_id_num();
	int get_hour_num();
	double get_payment_num();

	void set_employee_name(string);
	void set_id_num(int);
	void set_hour_num(int);
	void set_payment_num(double);
};

