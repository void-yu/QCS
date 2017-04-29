#include <iostream>
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include "Circuit.h"

using namespace std;

int main(int argc, char* argv[])
{
    //∂¡≈‰÷√
    LPTSTR lpPath = new char[256];
    LPTSTR circuitPath = new char[256];
    LPTSTR gateLibPath = new char[256];

    strcpy(lpPath, ".\\config.ini");

    GetPrivateProfileString("FilePath", "Circuit", "", circuitPath, 256, lpPath);

    GetPrivateProfileString("FilePath", "GateLib", "", gateLibPath, 256, lpPath);

    delete [] lpPath;

    Circuit c;
    c.read(circuitPath);

    GateLib gl;
    gl.read(gateLibPath);

    c.matchgate(gl);
    ofstream cfile(".\\~temp.real");
    cfile.clear();
    streambuf * ocoutbuf = cout.rdbuf(cfile.rdbuf());
    c.print();
    cout.rdbuf(ocoutbuf);
    cfile.close();
    delete cfile;

    ofstream glfile(".\\~temp.truth");
    glfile.clear();
    ocoutbuf = cout.rdbuf(glfile.rdbuf());
    TruthInCircuit tr;
    c.calculate(gl, tr);
    for (auto i : tr.truthTable)
    {
        cout << i.first << ' ' << i.second << '\n';
    }
    cout.rdbuf(ocoutbuf);
    glfile.close();
    delete glfile;

    return 0;
}
