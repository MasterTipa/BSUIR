#include "File.h"

File& operator<<(File& file, const char* s)
{
	try {
		if (!file.file.is_open())
		{
			throw 1;
		}
	}
	catch (int i)
	{
		Exception ex(i);
		ex.Print();
	}
	string str = s;
	file.file << str;
	return file;
}

fstream& operator<<(fstream& out, Employee& uni) {
	try {
		if (!out.is_open())
		{
			throw 1;
		}
	}
	catch (int i)
	{
		Exception ex(i);
		ex.Print();
	}
	int a = out.tellg();
	string employee_name = uni.get_employee_name();
	size_t len1 = employee_name.length() + 1;

	int hour_num = uni.get_hour_num();
	int id_num = uni.get_id_num();

	double payment_num = uni.get_payment_num();

	out.write((char*)(&len1), sizeof(len1));
	out.write((char*)(employee_name.c_str()), len1);

	out.write((char*)(&id_num), sizeof(id_num));
	out.write((char*)(&hour_num), sizeof(hour_num));

	out.write((char*)(&payment_num), sizeof(payment_num));

	return out;
}

File& operator<<(File& file, Employee& uni)
{
	int pos = 0, a = 0, size = 0;
	try {
		if (!file.file.is_open())
		{
			throw 1;
		}
	}
	catch (int i)
	{
		Exception ex(i);
		ex.Print();
	}
	if (file.key == txt) {
		file.file << uni.get_employee_name() << " " << uni.get_id_num() << " " << uni.get_hour_num() << " "
			<< uni.get_payment_num() << endl;
	}
	else if (file.key == bin) {
		string employee_name = uni.get_employee_name();
		size_t len1 = employee_name.length() + 1;

		int id_num = uni.get_id_num();
		int hour_num = uni.get_hour_num();

		double payment_num = uni.get_payment_num();

		file.file.write((char*)(&len1), sizeof(len1));
		file.file.write((char*)(employee_name.c_str()), len1);

		file.file.write((char*)(&id_num), sizeof(id_num));
		file.file.write((char*)(&hour_num), sizeof(hour_num));

		file.file.write((char*)(&payment_num), sizeof(payment_num));
	}
	return file;
}



ostream& operator<<(ostream& out, File& file)
{
	int a = 0;
	try {
		if (!file.file.is_open())
		{
			throw 1;
		}
	}
	catch (int i)
	{
		Exception ex(i);
		ex.Print();
	}
	if (file.key == txt) {
		string str;
		while (!file.file.eof()) {
			getline(file.file, str);
			a = file.file.tellg();
			cout << str << endl;
		}
	}
	else if (file.key == bin) {
		int i = 0;
		int size = 0, step = 0;
		/*University tmp;*/
		while (i < file.size) {
			int hour_num;
			int id_num;
			double payment_num;

			size_t len;

			file.file.read((char*)(&len), sizeof(len));
			char* employee_name = new char[len];

			file.file.read((char*)(employee_name), len);
			employee_name[len - 1] = '\0';

			file.file.read((char*)(&id_num), sizeof(int));
			file.file.read((char*)(&hour_num), sizeof(int));

			file.file.read((char*)(&payment_num), sizeof(double));

			cout << employee_name << " " << id_num << " " << hour_num << " " << payment_num << endl;

			delete[] employee_name;
			i++;

		}
	}
	return out;
}



void File::edit(int line, Employee mas[]) {
	this->open("wr");

	int a, b;

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
		return;
	}
	Employee tmp;
	if (this->key == txt) {
		string temp;
		for (int i = 0; i < line - 1; i++) {
			getline(this->file, temp);
		}
		getline(this->file, temp, ' ');
		tmp.set_employee_name(temp);
		getline(this->file, temp, ' ');
		tmp.set_id_num(stoi(temp));
		getline(this->file, temp, ' ');
		tmp.set_hour_num(stoi(temp));
		getline(this->file, temp);
		tmp.set_payment_num(stoi(temp));
	}
	else if (this->key == bin) {
		size_t len;
		for (int i = 0; i < line; i++) {
			this->file.read((char*)(&len), sizeof(len));
			char* n = new char[len];
			string name;
			double payment_num;
			int hour_num = 0;
			int id_num = 0;

			this->file.read((char*)(n), len);
			name = n;
			name[len - 1] = '\0';
			this->file.read((char*)(&id_num), sizeof(int));
			this->file.read((char*)(&hour_num), sizeof(int));


			this->file.read((char*)(&payment_num), sizeof(double));

			tmp.set_employee_name(name);
			tmp.set_id_num(id_num);
			tmp.set_hour_num(hour_num);
			tmp.set_payment_num(payment_num);

		}
		a = file.tellg();
	}

	cout << "What do you want to change?\n1-Pizza Name\n2-Products id\n3-Kvo pz\n4-Kvo pr" << endl;
	int choice;
	cin >> choice;
	cout << "Put new data: ";
	switch (choice) {
	case 1: {
		string a;
		rewind(stdin);
		cin >> a;
		tmp.set_employee_name(a);
		break;
	}
	case 2: {
		int a;
		cin >> a;
		tmp.set_id_num(a);
		break;
	}
	case 3: {
		int a;
		cin >> a;
		tmp.set_hour_num(a);
		break;
	}
	case 4: {
		double a;
		cin >> a;
		tmp.set_payment_num(a);
		break;
	}
	}
	a = file.tellg();
	file.seekg(0, ios_base::end);
	b = file.tellg();
	this->file.seekg(0, ios_base::beg);
	if (this->key == txt) {
		string temp;
		for (int i = 0; i < line - 1; i++) {
			getline(this->file, temp);
		}
		int pos = this->file.tellg();
		this->file.seekg(pos, ios_base::beg);
		this->file << tmp;
		return;
	}
	else if (this->key == bin) {
		for (int i = 0; i < line - 1; i++) {

			size_t len;
			this->file.read((char*)(&len), sizeof(len));
			char* n = new char[len];
			string name;
			double payment_num;
			int hour_num = 0;
			int id_num = 0;

			this->file.read((char*)(n), len);
			name = n;
			name[len] = '\0';
			this->file.read((char*)(&id_num), sizeof(int));
			this->file.read((char*)(&hour_num), sizeof(int));


			this->file.read((char*)(&payment_num), sizeof(double));

			delete[]n;
		}
		int pos = this->file.tellg();

		char* last = new char[b - a];
		this->file.read((char*)last, b - a);

		this->close();
		this->open("w");
		pos = this->file.tellg();
		file << tmp;
		for (int i = 0; i < get_size(); i++) {
			if (i != line - 1)
				file << mas[i];
			else {
				mas[i].set_employee_name(tmp.get_employee_name());
				mas[i].set_id_num(tmp.get_id_num());
				mas[i].set_hour_num(tmp.get_hour_num());
				mas[i].set_payment_num(tmp.get_payment_num());
			}
		}
	}

	this->close();
}


void File::sort_name() {
	string temp;
	string j1, j2;
	int pos;
	this->open("wr");
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
		return;
	}
	for (int i = 0; i < this->size - 1; i++) {
		for (int j = 0; j < this->size - i - 1; j++) {
			this->file.seekg(0, ios_base::beg);
			for (int k = 0; k < j; k++) {
				getline(this->file, j1);
			}
			getline(this->file, j1, ' ');
			getline(this->file, j2);
			getline(this->file, j2, ' ');
			if (j1 > j2) {
				this->file.seekg(0, ios_base::beg);
				pos = this->file.tellg();
				for (int k = 0; k <= j; k++) {
					getline(this->file, j1);
					pos = this->file.tellg();
				}
				temp = j1;
				getline(this->file, j2);
				this->file.seekg(0, ios_base::beg);
				for (int k = 0; k < j; k++) {
					getline(this->file, j1);
				}
				pos = this->file.tellg();
				this->file.seekg(pos, ios_base::beg);
				this->file << j2 << '\n';
				this->file << temp << '\n';
			}
		}
	}
	this->close();
}

void File::sort_id_num() {
	string temp;
	string j1, j2;
	int i1, i2;
	int pos;
	this->open("wr");
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
		return;
	}
	for (int i = 0; i < this->size - 1; i++) {
		for (int j = 0; j < this->size - i - 1; j++) {
			this->file.seekg(0, ios_base::beg);
			for (int k = 0; k < j; k++) {
				getline(this->file, j1);
			}
			getline(this->file, j1, ' ');
			getline(this->file, j1, ' ');
			getline(this->file, j2);
			getline(this->file, j2, ' ');
			getline(this->file, j2, ' ');
			i1 = stoi(j1);
			i2 = stoi(j2);
			if (i1 > i2) {
				this->file.seekg(0, ios_base::beg);
				pos = this->file.tellg();
				for (int k = 0; k <= j; k++) {
					getline(this->file, j1);
					pos = this->file.tellg();
				}
				temp = j1;
				getline(this->file, j2);
				this->file.seekg(0, ios_base::beg);
				for (int k = 0; k < j; k++) {
					getline(this->file, j1);
				}
				pos = this->file.tellg();
				this->file.seekg(pos, ios_base::beg);
				this->file << j2 << '\n';
				this->file << temp << '\n';
			}
		}
	}
	this->close();
}

void File::sort_hour_num() {
	string temp;
	string j1, j2;
	int i1, i2;
	int pos;
	this->open("wr");
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
		return;
	}
	for (int i = 0; i < this->size - 1; i++) {
		for (int j = 0; j < this->size - i - 1; j++) {
			this->file.seekg(0, ios_base::beg);
			for (int k = 0; k < j; k++) {
				getline(this->file, j1);
			}
			getline(this->file, j1, ' ');
			getline(this->file, j1, ' ');
			getline(this->file, j1, ' ');
			getline(this->file, j2);
			getline(this->file, j2, ' ');
			getline(this->file, j2, ' ');
			getline(this->file, j2, ' ');
			i1 = stoi(j1);
			i2 = stoi(j2);
			if (i1 > i2) {
				this->file.seekg(0, ios_base::beg);
				pos = this->file.tellg();
				for (int k = 0; k <= j; k++) {
					getline(this->file, j1);
					pos = this->file.tellg();
				}
				temp = j1;
				getline(this->file, j2);
				this->file.seekg(0, ios_base::beg);
				for (int k = 0; k < j; k++) {
					getline(this->file, j1);
				}
				pos = this->file.tellg();
				this->file.seekg(pos, ios_base::beg);
				this->file << j2 << '\n';
				this->file << temp << '\n';
			}
		}
	}
	this->close();
}
void search(File f1) {

	cout << "To chto IsPoRtItSyA\n";
	f1.sort_hour_num();
	f1.open("r");
	cout << f1;
	f1.close();

};
void File::sort_payment_num() {
	string temp;
	string j1, j2;
	int i1, i2, i11, i22;
	int pos;
	this->open("wr");
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
		return;
	}
	for (int i = 0; i < this->size - 1; i++) {
		for (int j = 0; j < this->size - i - 1; j++) {
			this->file.seekg(0, ios_base::beg);
			for (int k = 0; k < j; k++) {
				getline(this->file, j1);
			}
			getline(this->file, j1, ' ');
			getline(this->file, j1, ' ');
			getline(this->file, j1, ' ');
			getline(this->file, j1);
			pos = file.tellg();

			getline(this->file, j2, ' ');
			getline(this->file, j2, ' ');
			getline(this->file, j2, ' ');
			getline(this->file, j2);
			pos = file.tellg();

			if (j1 > j2) {
				this->file.seekg(0, ios_base::beg);
				pos = this->file.tellg();
				for (int k = 0; k <= j; k++) {
					getline(this->file, j1);
					pos = this->file.tellg();
				}
				temp = j1;
				getline(this->file, j2);
				this->file.seekg(0, ios_base::beg);
				for (int k = 0; k < j; k++) {
					getline(this->file, j1);
				}
				pos = this->file.tellg();
				this->file.seekg(pos, ios_base::beg);
				this->file << j2 << '\n';
				this->file << temp << '\n';
			}
		}
	}
	this->close();
}