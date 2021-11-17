//"The moment man devoured the fruit of knowledge, he sealed his fate ... 
//Entrusting his future to the cards, man clings to a dim hope. 
//Yet, the Arcana is the means by which all is revealed. 
//Beyond the beaten path lies the absolute end. 
//It matters not who you are ... 
//Death awaits you."

#include <iostream>
#include <fstream>
#include <string>

#include"Exepcion.h"
#include"File.h"
#include"Employee.h"
#include"Ring.h"

using namespace std;



int main()
{

    Employee u1("Oleg", 4, 3, 15);
    Employee u2("Igor", 1, 1, 48);
    Employee u3("Grzergorgz", 0, 1, 89);
    Employee u4("Aloyzich", 2, 5, 15);
    Employee u5("Biba", 1, 2, 32);
    Employee flg[5] = { u1,u2,u3,u4,u5 };
    File f1("1.txt", txt);
    f1.open("w");
    f1.set_size(5);
    f1 << u1;
    f1 << u2;
    f1 << u3;
    f1 << u4;
    f1 << u5;
    f1.close();
    f1.open("r");
    cout << f1;
    f1.close();
    cout << "\n\n";
    File f2("2.txt", bin);
    f2.open("w");
    f2.set_size(5);
    f2 << u1;
    f2 << u2;
    f2 << u3;
    f2 << u4;
    f2 << u5;
    f2.close();
    f2.open("r");
    cout << f2;
    f2.close();
    cout << "\n\n";
    File f3("3.bin", bin);
    f3.open("w");
    f3.set_size(5);
    f3 << u1;
    f3 << u2;
    f3 << u3;
    f3 << u4;
    f3 << u5;
    f3.close();
    f3.open("r");
    cout << f3;
    f3.close();
    cout << "\n\n";

    int a = 0, line = 0;
    do {
        cout << "Enter the line that you want to change:" << endl;
        cin >> line;
        f2.edit(line, flg);
        f2.open("r");
        cout << f2;
        f2.close();
        cout << "Do you want to change anything else?\n1 - yes\n0 - no" << endl;
        rewind(stdin);
        cin >> a;
    } while (a);

    cout << "Sort by name:" << endl;
    f1.sort_name();
    f1.open("r");
    cout << f1;
    f1.close();

    cout << "Sort by id_num:" << endl;
    f1.sort_id_num();
    f1.open("r");
    cout << f1;
    f1.close();

    cout << "Sort by hour_num:" << endl;
    f1.sort_hour_num();
    f1.open("r");
    cout << f1;
    f1.close();

    cout << "Sort by payment_name:" << endl;
    f1.sort_payment_num();
    f1.open("r");
    cout << f1;
    f1.close();


    Ring r;
    int pos;
    cout << "NE RABOTYAGI" << endl;
    f1.sort_name();
    f1.open("r");
    Employee tmp;
    int o = 0;
        f1.begin();
        for (int i = 0; i < f1.get_size(); i++) {
            tmp = f1.return_uni();
                if (tmp.get_hour_num() < 3)
                {
                    r.input(tmp);
                    o++;
                }
        }
    Iterator  I(&r);
    f1.set_size(o);
    for (int i = 0; i < f1.get_size(); i++) {
        cout << *I;
        ++I;
    }

    return 0;
}