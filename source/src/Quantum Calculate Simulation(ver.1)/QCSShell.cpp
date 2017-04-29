#include <iostream>
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include "Circuit.h"

using namespace std;

#define SHELL_CMD_SPACE 10
#define SHELL_ARGV_SPACE 10

typedef bool (*CmdFunction)(int argc, char* argv[]);

/**
��ָ������ָ���
*/
struct CmdRule
{
    char* instName;
    CmdFunction instFunction;
};

bool create_circuit(int argc, char* argv[]);
bool load_gateLib(int argc, char* argv[]);
bool insert_gate(int argc, char* argv[]);
bool erase_gate(int argc, char* argv[]);
bool help(int argc, char* argv[]);
bool print_circuit_cmd(int argc, char* argv[]);
bool print_circuit_file(int argc, char* argv[]);
bool match(int argc, char* argv[]);
bool calculate_cmd(int argc, char* argv[]);

CmdRule cmdTable[SHELL_CMD_SPACE] =
{
    {"CREC", create_circuit},
    {"LOAGL", load_gateLib},
    {"INSG", insert_gate},
    {"ERAG", erase_gate},
    {"HELP", help},
    {"PRINT_C", print_circuit_cmd},
    {"PRINT_F", print_circuit_file},
    {"MATCH", match},
    {"CALCULATE_C", calculate_cmd}
};

map<string, Circuit> c_save;
map<string, GateLib> gl_save;

int main(int argc, char* argv[])
{
    system("mode con cols=70 lines=40");//�ı���
    system("color f0");//�ı���ɫ
    while(1)
    {
        char str[256];

        if (cin.fail())
        {
            cin.clear();
        }

        cout << "Shell:>";
        cin >> str;

        if (strcmp(str, "QUIT") == 0)
        {
            break;
        }
        else if (strcmp(str, "CLEAR") == 0)
        {
            system("cls");
            continue;
        }

        int index;
        for (index = 0; index < SHELL_CMD_SPACE; ++index)
        {
            if (cmdTable[index].instName == NULL) continue;

            if (strcmp(str, cmdTable[index].instName) == 0)
            {
                cin.get(str, 256, '\n');
                fflush(stdin);

                char* t_argv[SHELL_ARGV_SPACE];
                int argv_index = 0;

                t_argv[0] = strtok(str, " ");
                while (t_argv[argv_index++] != NULL)
                {
                    t_argv[argv_index] = strtok(NULL ," ");
                }

                bool t_return = cmdTable[index].instFunction(argv_index - 1, t_argv);
                if (!t_return)
                {
                    cout << "failed\n";
                }
                break;
            }
        }

        if (index == SHELL_CMD_SPACE)
        {
            fflush(stdin);
            cout << "failed\n";
        }
        cout << '\n';
    }//end while

    return 0;
}



/**
*/
bool help(int argc, char* argv[])
{
    cout << "ָ���ʽ" << "\t" << "����\n"
         << "=============================\n";
    cout << "CREC ��·�� (����)��·��ȡ·��" << "\t\t" << "����ָ��·����ȡ��������·\n";

    cout << "LOAGL �ſ��� (����)�ſ��ȡ·��" << "\t\t" << "����ָ��·����ȡ�ſ�\n";

    cout << "INSG ��·�� ���� ����λ" << "\t\t\t" << "��ָ����·��ĩλ�����\n";

    cout << "ERAG ��·��" << "\t\t\t\t" << "��ָ����·��ĩλɾ����\n";

    cout << "PRINT_C ��·��" << "\t\t\t\t" << "�ڿ���̨�ϴ�ӡָ����·\n";

    cout << "PRINT_F ��·�� (����)��·��ȡ·��" << "\t" << "��ָ��·����ӡָ����·\n";

    cout << "MATCH ��·�� �ſ���" << "\t\t\t" << "��ָ����·����ָ���ſ������ƥ��\n";

    cout << "CALCULATE_C ��·�� �ſ���" << "\t\t" << "�ڿ���̨�ϴ�ӡ��ָ����·����ָ���ſ�����ż�����\n";

    cout << "CLEAR" << "\t\t\t\t\t" << "����\n";

    return 1;
}

bool create_circuit(int argc, char* argv[])
{
    if (argv[0] == NULL)
    {
        return 0;
    }
    string c_name(argv[0]);
    Circuit c_new;
    string filetrace;
    getline(cin, filetrace);
    if (c_new.read(filetrace))
    {
        auto ret=c_save.insert(pair<string, Circuit>(c_name, c_new));
        if (ret.second == false)
        {
            cout << "element \'" << c_name << "\' already existed\n";
            return 0;
        }
        return 1;
    }
    else {
        return 0;
    }
}

bool load_gateLib(int argc, char* argv[])
{
    if (argv[0] == NULL)
    {
        return 0;
    }
    string gl_name(argv[0]);
    GateLib gl_new;
    string filetrace;
    getline(cin, filetrace);
    if (gl_new.read(filetrace))
    {
        auto ret = gl_save.insert(pair<string, GateLib>(gl_name, gl_new));
        if (ret.second == false)
        {
            cout << "element \'" << gl_name << "\' already existed\n";
            return 0;
        }
        return 1;
    }
    else {
        return 0;
    }
}

bool insert_gate(int argc, char* argv[])
{
    if (argv[0] == NULL || argv[1] == NULL)
    {
        return 0;
    }
    Circuit &c = c_save.find(argv[0])->second;
    GateInCircuit g_insert;
    g_insert.gateName = argv[1];
    int argv_index = 2;
    while (argv[argv_index] != NULL)
    {
        g_insert.posi.push_back(argv[argv_index++]);
    }
    auto c_it = c.end();
    if (c.insert_gate(c_it, g_insert))
    {
        return 1;
    }
    else {
        return 0;
    }
}

bool erase_gate(int argc, char* argv[])
{
    if (argv[0] == NULL)
    {
        return 0;
    }
    Circuit &c = c_save.find(argv[0])->second;
    auto c_it = c.back();
    if (c.erase_gate(c_it))
    {
        return 1;
    }
    else {
        return 0;
    }
}

bool print_circuit_cmd(int argc, char* argv[])
{
    if (argv[0] == NULL)
    {
        return 0;
    }
    auto c_it = c_save.find(argv[0]);
    if (c_it != c_save.end())
    {
        c_it->second.print();
        return 1;
    }
    else{
        return 0;
    }
}

bool print_circuit_file(int argc, char* argv[])
{
    if (argv[0] == NULL)
    {
        return 0;
    }
    string filetrace;
    getline(cin, filetrace);
    ofstream cfile(filetrace);
    if (!cfile)
	{
		return 0;
	}
    auto c_it = c_save.find(argv[0]);
    if (c_it != c_save.end())
    {
        streambuf * ocoutbuf = cout.rdbuf(cfile.rdbuf());
        c_it->second.print();
        cfile.close();
        cout.rdbuf(ocoutbuf);
        return 1;
    }
    else{
        cfile.close();
        return 0;
    }
}

bool match(int argc, char* argv[])
{
    if (argv[0] == NULL || argv[1] == NULL)
    {
        return 0;
    }
    Circuit &c = c_save.find(argv[0])->second;
    GateLib &gl = gl_save.find(argv[1])->second;
    if (c.matchgate(gl))
    {
        return 1;
    }
    else {
        return 0;
    }
}

bool calculate_cmd(int argc, char* argv[])
{
    if (argv[0] == NULL || argv[1] == NULL)
    {
        return 0;
    }
    Circuit &c = c_save.find(argv[0])->second;
    if (c.get_variNum() > 30)
    {
        cout << "hard to be calculated(the number of variables is more than 30)\n";
        return 0;
    }
    GateLib &gl = gl_save.find(argv[1])->second;
    TruthInCircuit tr;
    if (c.calculate(gl, tr))
    {
        for (auto index : tr.truthTable)
        {
            cout << index.first << ' ' << index.second << '\n';
        }
        return 1;
    }
    else {
        return 0;
    }
    return 1;
}
