#include "Gate.h"
#include <iostream>
#include <windows.h>

using namespace std;

int main(void)
{

    cout << "SimpleGate测试：\n---------------------------\n";
    SimpleGate test1;
    SimpleGate test2;

    cout << "read()测试:";
    test1.read("D:\\Code Files\\项目_毕业设计_量子电路仿真平台ver1\\main\\gatelib\\NCV\\cnot.gaterule");
    test2.read("D:\\Code Files\\项目_毕业设计_量子电路仿真平台ver1\\main\\gatelib\\NCV\\cnot_1.gaterule");
    cout << '\n';

    cout << "find()测试：";
    cout << test1.find("1a");
    cout << '\n';

    cout << "operator == ()测试：";
    cout << (test1 == test2);
    cout << '\n';

    cout << "iterator测试："
    "\n";
    SimpleGate::iterator tspit;
    for (tspit = test1.begin(); tspit != test1.end(); tspit++)//注意：此循环结束时tspit已指向.end()
    {
        cout << tspit.input() << "->" << tspit.output() << '\n';
    }
    cout << "\n";

    cout << '\n';

    cout << "ComplexGate测试：\n---------------------------\n";
    ComplexGate test3;
    ComplexGate test4;

    cout << "read()测试:";
    cout << test3.read("D:\\Code Files\\项目_毕业设计_量子电路仿真平台ver1\\main\\gatelib\\NCV\\toffoli.gaterule");
    cout << test4.read("D:\\Code Files\\项目_毕业设计_量子电路仿真平台ver1\\main\\gatelib\\NCV\\toffoli_n.gaterule");
    cout << '\n';

    cout << "operator == ()测试：";
    cout << (test3 == test4);
    cout << '\n';

    cout << "iterator测试:"
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
