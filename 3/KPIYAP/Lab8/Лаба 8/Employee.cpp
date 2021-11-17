#include "Employee.h"
#include "Exepcion.h"


ostream& operator<<(ostream& out, const Employee& univ)
{
	try {
		if (univ.employee_name == "Space")
		{
			throw 2;
		}
	}
	catch (int i)
	{
		Exception ex(i);
		ex.Print();
	}
	out << univ.employee_name << " " << univ.id_num << " " << univ.hour_num << " "
		<< univ.payment_num << endl;
	return out;
}

istream& operator>>(istream& in, Employee& univ)
{
	in >> univ.employee_name;
	in >> univ.id_num;
	in >> univ.hour_num;
	in >> univ.payment_num;
	return in;
}

bool operator==(Employee u1, Employee u2) {
	if (u1.get_employee_name() == u2.get_employee_name() && u1.get_id_num() == u2.get_id_num() && u1.get_hour_num() == u2.get_hour_num() &&
		u1.get_payment_num() == u2.get_payment_num()) {
		return true;
	}
	else {
		return false;
	}
}


string Employee::get_employee_name() {
	return this->employee_name;
}
int Employee::get_id_num() {
	return this->id_num;
}
int Employee::get_hour_num() {
	return this->hour_num;
}
double Employee::get_payment_num() {
	return this->payment_num;
}

void Employee::set_employee_name(string tmp) {
	this->employee_name = tmp;
}
void Employee::set_id_num(int tmp) {
	this->id_num = tmp;
}
void Employee::set_hour_num(int tmp) {
	this->hour_num = tmp;
}
void Employee::set_payment_num(double tmp) {
	this->payment_num = tmp;
}