#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
int main()
{
	cout << "Enter the text"<<endl;
	string s;
	getline(cin,s);
	cout <<"It's your text : "
		<< s <<endl<<"His length : "
		<< s.length()<<endl
		<<"Reverse text : ";
	for (int i = s.length();i > 0;i--)
		cout << s[i - 1];
	cout << endl<<hex<<25039751;

}

