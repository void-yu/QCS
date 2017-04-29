#include "GateLib.h"
#include <iostream>
#include <windows.h>

using namespace std;

int main(void)
{
    cout << "GateLib���ԣ�\n---------------------------\n";
    GateLib test1;

    cout << "read()����:";
    cout << test1.read("D:\\Code Files\\��Ŀ_��ҵ���_���ӵ�·����ƽ̨ver1\\main\\gatelib\\MCT(for test)");
    cout <<'\n';

    cout << "iterator���ԣ�"
    "\n";
    GateLib::iterator tglit;
    for (tglit = test1.begin(); tglit != test1.end(); tglit++)//ע�⣺��ѭ������ʱtspit��ָ��.end()
    {
        cout << tglit.get_gateName() << ":\n";
        if (tglit.get_gate()->get_gateType() == 0)
        {
            SimpleGate* tsp = (SimpleGate*)tglit.get_gate();
            SimpleGate::iterator tspit;
            for (tspit = tsp->begin(); tspit != tsp->end(); ++tspit)
            {
                cout <<tspit.input() << "->" << tspit.output() << '\n';
            }
        }
        else if (tglit.get_gate()->get_gateType() == 1 || tglit.get_gate()->get_gateType() == 2)
        {
            ComplexGate* tcp = (ComplexGate*)tglit.get_gate();
            ComplexGate::iterator tcpit;
            for (tcpit = tcp->begin(); tcpit != tcp->end(); ++tcpit)
            {
                cout << tcpit.get_gateName() << ' ';
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
        }
        cout << '\n';
    }

    cout << "find()���ԣ�";
    cout << test1.find("t123")->get_gateType();
    cout << '\n';
    return 0;
}
