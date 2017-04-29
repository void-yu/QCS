#include "Circuit.h"

#include <iostream>
#include <fstream>

using namespace std;

int main(void)
{
    cout << "Circuit测试：\n---------------------------\n";
    //Circuit *test1 = new Circuit();
    Circuit test2;
    Circuit::iterator tcpit;


    cout << "read()测试:\n";
    //test1->read("D:\\Code Files\\项目_毕业设计_量子电路仿真平台ver1\\main\\circuitlib\\1.real");
    test2.read("C:\\Users\\yu\\Desktop\\QCS\\circuitlib\\t3.real");

    /**
    ofstream cfile("D:\\Code Files\\项目_毕业设计_量子电路仿真平台ver1\\main\\circuitlib\\4.real");
    streambuf * ocinbuf = cout.rdbuf(cfile.rdbuf());
    test1->print();
    cfile.close();
    */

    /**
    cout << "insert&erase测试:\n";
    GateInCircuit gatea;
    gatea.gateName = "t1";
    //for (tcpit = test1->begin(); tcpit != test1->end(); tcpit++)
    //{
    //    test1->insert_gate(tcpit, gatea);
    //}
    //gatea.posi.push_back("a");
    //auto xx = test2.back();
    //cout << test2.insert_gate(xx, gatea);
    //auto xxx = test2.back();
    //cout << test2.erase_gate(xx);
    test2.print();
    */
    GateLib testgl;
    //testgl.read("D:\\Code Files\\项目_毕业设计_量子电路仿真平台ver1\\main\\gatelib\\MCT(for test)");
    cout << testgl.read("C:\\Users\\yu\\Desktop\\QCS\\gatelib\\MCT(toffoli)");
    TruthInCircuit testtr;

    //test1->matchgate(testgl);
    test2.matchgate(testgl);
    //test2.print();

    test2.calculate(testgl, testtr);
    for (auto i : testtr.truthTable)
    {
        cout << i.first << ' ' << i.second << '\n';
    }

    //string truth = "00100";
    //string outputs;
    //test2.calculate_value(testgl, truth, outputs);
    //cout << outputs;
    /**cout << "iterator测试:"
    "\n";
    for (tcpit = test1->begin(); tcpit != test1->end(); tcpit++)
    {
        cout << tcpit.get_gateName();
        cout << '\n';
    }*/



    return 0;
}
