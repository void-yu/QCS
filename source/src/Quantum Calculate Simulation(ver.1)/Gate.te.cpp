#include "Gate.h"
#include <iostream>
#include <windows.h>

using namespace std;

int main(void)
{

    cout << "SimpleGate���ԣ�\n---------------------------\n";
    SimpleGate test1;
    SimpleGate test2;

    cout << "read()����:";
    test1.read("D:\\Code Files\\��Ŀ_��ҵ���_���ӵ�·����ƽ̨ver1\\main\\gatelib\\NCV\\cnot.gaterule");
    test2.read("D:\\Code Files\\��Ŀ_��ҵ���_���ӵ�·����ƽ̨ver1\\main\\gatelib\\NCV\\cnot_1.gaterule");
    cout << '\n';

    cout << "find()���ԣ�";
    cout << test1.find("1a");
    cout << '\n';

    cout << "operator == ()���ԣ�";
    cout << (test1 == test2);
    cout << '\n';

    cout << "iterator���ԣ�"
    "\n";
    SimpleGate::iterator tspit;
    for (tspit = test1.begin(); tspit != test1.end(); tspit++)//ע�⣺��ѭ������ʱtspit��ָ��.end()
    {
        cout << tspit.input() << "->" << tspit.output() << '\n';
    }
    cout << "\n";

    cout << '\n';

    cout << "ComplexGate���ԣ�\n---------------------------\n";
    ComplexGate test3;
    ComplexGate test4;

    cout << "read()����:";
    cout << test3.read("D:\\Code Files\\��Ŀ_��ҵ���_���ӵ�·����ƽ̨ver1\\main\\gatelib\\NCV\\toffoli.gaterule");
    cout << test4.read("D:\\Code Files\\��Ŀ_��ҵ���_���ӵ�·����ƽ̨ver1\\main\\gatelib\\NCV\\toffoli_n.gaterule");
    cout << '\n';

    cout << "operator == ()���ԣ�";
    cout << (test3 == test4);
    cout << '\n';

    cout << "iterator����:"
    "\n";
    ComplexGate::iterator tcpit;
    for (tcpit = test4.begin(); tcpit != test4.end(); tcpit++)
    {
        cout << tcpit.get_ruleName() << ' ' << tcpit.get_gateName() << ':';
        for (auto t_ : tcpit.get_contPosi())
        {
            cout << t_ << ' ';
        }
        for (auto t_ : tcpit.get_targPosi())
        {
            cout << t_ << ' ';
        }
        cout << '\n';
    }
    cout << "\n";


    system("pause");
    return 0;
}
