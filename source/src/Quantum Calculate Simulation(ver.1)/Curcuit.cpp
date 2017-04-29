#include "Circuit.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stdlib.h>
#include <math.h>
#include <string.h>

using namespace std;

Circuit::Circuit()
{
    this->gateList.clear();
}

/**
*/
bool Circuit::read(const string& filename)
{
    this->variables.clear();
    this->inputs.clear();
    this->outputs.clear();
    this->gateList.clear();

    ifstream cfile(filename);
	if (!cfile)
	{
		return 0;
	}

	string tstream;
	int tcposi_1, tcposi_2;
	int tcount;

	//# Function: XXX
	getline(cfile, tstream, '\n');
	this->circuitName = tstream.substr(12);

    //# Used Library: XXX (gates: X, quantum costs: XX)
	getline(cfile, tstream, '\n');
	tcposi_1 = 0;
	tcposi_2 = 0;
	tcposi_1 = tstream.find(" (");
	this->gateLibName = tstream.substr(16, tcposi_1 - 16);
	tcposi_1 = tstream.find("gates:") + 7;
	tcposi_2 = tstream.find(",") - tcposi_1;
	tcount = atoi(tstream.substr(tcposi_1,tcposi_2).c_str());
	this->gateNum = tcount;
	tcposi_1 = tcposi_1 + tcposi_2 + 17;
	tcposi_2 = tstream.find(")") - tcposi_1;
    tcount = atoi(tstream.substr(tcposi_1,tcposi_2).c_str());
    this->quantumCost = tcount;

    //# This file have been taken from RevLib (www.revlib.org).
    getline(cfile, tstream, '\n');
    //.version 1.0
    getline(cfile, tstream, '\n');

    //.numvars 3
    getline(cfile, tstream, '\n');
    tcposi_1 = tstream.size() - 9;
    tcount = atoi(tstream.substr(9, tcposi_1).c_str());
    this->variNum = tcount;

    //.variables a b c
    getline(cfile, tstream, '\n');
    tcposi_1 = tstream.size() - 11;
    tstream = tstream.substr(11, tcposi_1);
    tstream += ' ';
    for (int tc_index = 0; tc_index != tstream.size(); ++tc_index)
    {
        tcposi_1 = 0;
        tcposi_1 = tstream.find(" ", tc_index);
        if (tcposi_1 < tstream.size())
        {
            this->variables.push_back(tstream.substr(tc_index, tcposi_1 - tc_index));
            tc_index = tcposi_1;
        }
    }

    //.inputs a b c
    getline(cfile, tstream, '\n');
    tcposi_1 = tstream.size() - 8;
    tstream = tstream.substr(8, tcposi_1);
    tstream += ' ';
    for (int tc_index = 0; tc_index != tstream.size(); ++tc_index)
    {
        tcposi_1 = 0;
        tcposi_1 = tstream.find(" ", tc_index);
        if (tcposi_1 < tstream.size())
        {
            this->inputs.push_back(tstream.substr(tc_index, tcposi_1 - tc_index));
            tc_index = tcposi_1;
        }
    }

    //.outputs a b c
    getline(cfile, tstream, '\n');
    tcposi_1 = tstream.size() - 9;
    tstream = tstream.substr(9, tcposi_1);
    tstream += ' ';
    for (int tc_index = 0; tc_index != tstream.size(); ++tc_index)
    {
        tcposi_1 = 0;
        tcposi_1 = tstream.find(" ", tc_index);
        if (tcposi_1 < tstream.size())
        {
            this->outputs.push_back(tstream.substr(tc_index, tcposi_1 - tc_index));
            tc_index = tcposi_1;
        }
    }

    //.constants ---
    getline(cfile, tstream, '\n');
    this->constants = tstream.substr(11, tstream.size() - 11);

    //.garbage ---
    getline(cfile, tstream, '\n');
    this->garbage = tstream.substr(9, tstream.size() - 9);

    //.begin
    getline(cfile, tstream, '\n');

    for (int c_index = 0; c_index < this->gateNum; ++c_index)
    {
        getline(cfile, tstream, '\n');
        GateInCircuit tgc;
        tstream += ' ';
        tcposi_1 = tstream.find(" ");
        tgc.gateName = tstream.substr(0, tcposi_1);
        tstream = tstream.substr(tcposi_1 + 1);

        for (int tc_index = 0; tc_index != tstream.size(); ++tc_index)
        {
            tcposi_1 = 0;
            tcposi_1 = tstream.find(" ", tc_index);
            if (tcposi_1 < tstream.size())
            {
                string tc_push = tstream.substr(tc_index, tcposi_1 - tc_index);
                if (tc_push != "")
                {
                    tgc.posi.push_back(tc_push);
                }
                tc_index = tcposi_1;
            }
        }

        this->gateList.push_back(tgc);
    }

    cfile.close();
    return 1;
}

/**
*/
void Circuit::print(void)
{
    //# Function: XXX
    cout << "# Function: " << this->circuitName << '\n';

    //# Used Library: MCT (gates: 6, quantum costs: 14)
    cout << "# Used Library: " << this->gateLibName
         << " (gates: " << this->gateNum
         << ", quantum costs: " << this->quantumCost
         << ")\n";

    //# This file have been taken from RevLib (www.revlib.org).
    cout << "# This file have been taken from RevLib (www.revlib.org).\n";

    //.version 1.0
    cout << ".version 1.0\n";

    //.numvars 3
    cout << ".numvars " << this->variNum << '\n';

    //.variables a b c
    cout << ".variables";
    for (auto tc_index : this->variables)
    {
        cout << ' ' << tc_index;
    }
    cout << '\n';

    //.inputs a b c
    cout << ".inputs";
    for (auto tc_index : this->inputs)
    {
        cout << ' ' << tc_index;
    }
    cout << '\n';

    //.outputs a b c
    cout << ".outputs";
    for (auto tc_index : this->outputs)
    {
        cout << ' ' << tc_index;
    }
    cout << '\n';

    //.constants ---
    cout << ".constants " << this->constants << '\n';

    //.garbage ---
    cout << ".garbage " << this->garbage << '\n';

    //.begin
    cout << ".begin\n";

    for (const auto &tc_index : this->gateList)
    {
        cout << tc_index.gateName;
        for (const auto &tcp_index : tc_index.posi)
        {
            cout << ' ' << tcp_index;
        }
        cout << '\n';
    }

    //.end
    cout << ".end\n";
}

/**
*/
Circuit::iterator Circuit::begin(void)
{
    Circuit::iterator c_it;
    c_it.gateListIter = this->gateList.begin();
    return c_it;
}

/**
*/
Circuit::iterator Circuit::end(void)
{
    Circuit::iterator c_it;
    c_it.gateListIter = this->gateList.end();
    return c_it;
}

/**
*/
Circuit::iterator Circuit::back(void)
{
    Circuit::iterator c_it, tc_it;
    c_it = this->begin();
    for (tc_it = c_it; c_it != this->end(); ++c_it)
    {
        tc_it = c_it;
    }
    return tc_it;
}

/**
*/
Circuit::iterator& Circuit::iterator::operator = (const Circuit::iterator& c_it)
{
    Circuit::iterator tc_it;
    tc_it.gateListIter = c_it.gateListIter;
    this->gateListIter = c_it.gateListIter;
    return tc_it;
}

/**
*/
Circuit::iterator& Circuit::iterator::operator ++ (void)
{
    ++(this->gateListIter);
    return *this;
}

/**
*/
const Circuit::iterator Circuit::iterator::operator ++ (int)
{
    const Circuit::iterator tc_it = *this;
    ++(this->gateListIter);
    return tc_it;
}

/**
*/
bool Circuit::iterator::operator == (const Circuit::iterator& c_it)
{
    if (this->gateListIter == c_it.gateListIter)
    {
        return 1;
    }
    else {
        return 0;
    }
}

/**
*/
bool Circuit::iterator::operator != (const Circuit::iterator& c_it)
{
    if (this->gateListIter != c_it.gateListIter)
    {
        return 1;
    }
    else {
        return 0;
    }
}

/**
*/
string Circuit::iterator::get_gateName(void)
{
    return this->gateListIter->gateName;
}

/**
*/
vector<string> Circuit::iterator::get_posi(void)
{
    return this->gateListIter->posi;
}

/**
*/
int Circuit::iterator::get_posiNum(void)
{
    return this->gateListIter->posi.size();
}

/**
*/
bool Circuit::insert_gate(Circuit::iterator& g_it, GateInCircuit& gate)
{
    vector<string>::iterator v_itf, v_its;
    for (v_itf = gate.posi.begin(); v_itf != gate.posi.end(); ++v_itf)
    {
        for (v_its = this->variables.begin(); v_its != this->variables.end(); ++v_its)
        {
            if (*v_itf == *v_its)
            {
                break;
            }
        }
        if (v_its == this->variables.end())
        {
            return 0;
        }
    }

    this->gateList.insert(g_it.gateListIter, gate);//请参考stl中list::insert()，iterator指针指向
    ++this->gateNum;

    return 1;
}

/**
*/
bool Circuit::erase_gate(Circuit::iterator& g_it)
{
    Circuit::iterator c_it;
    for (c_it = this->begin(); c_it != this->end(); ++c_it)
    {
        if (c_it == g_it)
        {
            break;
        }
    }
    if (c_it == this->end())
    {
        return 0;
    }

    Circuit::iterator tg_it = g_it;
    ++tg_it;
    this->gateList.erase(g_it.gateListIter);
    g_it = tg_it;
    --this->gateNum;

    return 1;
}

/**

bool Circuit::insert_line(vector<string>::iterator& v_it, string vari)
{
    vector<string>::iterator tv_it;
    for (tv_it = this->variables.begin(); tv_it != this->variables.end(); ++tv_it)
    {
        if (*tv_it == vari)
        {
            return 0;
        }
    }

    this->variables.insert(v_it, vari);//请参考stl中list::insert()，iterator指针指向
    ++this->variNum;

    return 1;
}*/

/**

bool Circuit::erase_line(vector<string>::iterator& v_it)
{
    vector<string>::iterator tv_it;
    for (tv_it = this->variables.begin(); tv_it != this->variables.end(); ++tv_it)
    {
        if (tv_it == v_it)
        {
            break;
        }
    }

    tv_it = v_it;
    ++tv_it;
    this->variables.erase(v_it);
    v_it = tv_it;
    --this->variNum;

    return 1;
}*/

/**
*/
Circuit& Circuit::operator = (const Circuit& c)
{
    Circuit tc;
    tc.circuitName = c.circuitName;
    this->circuitName = c.circuitName;
    tc.gateLibName = c.gateLibName;
    this->gateLibName = c.gateLibName;
    tc.gateNum = c.gateNum;
    this->gateNum = c.gateNum;
    tc.quantumCost = c.quantumCost;
    this->quantumCost = c.quantumCost;
    tc.variNum = c.variNum;
    this->variNum = c.variNum;
    tc.variables = c.variables;
    this->variables = c.variables;
    tc.inputs = c.inputs;
    this->inputs = c.inputs;
    tc.outputs = c.outputs;
    this->outputs = c.outputs;
    tc.constants = c.constants;
    this->constants = c.constants;
    tc.garbage = c.garbage;
    this->garbage = c.garbage;
    tc.gateList = c.gateList;
    this->gateList = c.gateList;
    return tc;
}

/**
函数名:changegate
参数:Circuit::iterator指向电路中的门
     ComplexGate指向该门的替换规则
     this为隐含参数，指向本电路
功能:在本电路中根据替换规则替换电路中的门，该门为“非递归的复杂门”
*/
bool Circuit::changegate(Circuit::iterator& c_it, ComplexGate* tcg)
{
    //获取原门(c_it)的所有位，该门肯定是复杂门
    vector<string> g_posi = c_it.get_posi();

    //获得门规则中门的控制位和目标位个数
    int gr_cnum = tcg->get_contNum();
    int gr_tnum = tcg->get_targNum();


    //删除该门
    this->erase_gate(c_it);

    //用于查询该门规则的指针(gr_it)
    ComplexGate::iterator gr_it;
    //门规则遍历
    for (gr_it = tcg->begin(); gr_it != tcg->end(); ++gr_it)
    {
        //获取门规则 N t2 cb0:cb1
        string tg_rule = gr_it.get_ruleName();
        string tg_name = gr_it.get_gateName();
        vector<string> tg_cont = gr_it.get_contPosi();
        vector<string> tg_targ = gr_it.get_targPosi();

        //N规则
        if (tg_rule == "N")
        {
            GateInCircuit ng;
            ng.gateName = tg_name;

            int tg_size = g_posi.size();

            int tgc_b, tgc_e, tgt_b, tgt_e;
            if (gr_cnum > 0)
            {
                tgc_b = 0;
                tgc_e = gr_cnum - 1;
                tgt_b = tgc_e + 1;
                tgt_e = tg_size - 1;
            }
            else if (gr_tnum > 0)
            {
                tgc_b = 0;
                tgt_e = tg_size - 1;
                tgt_b = tgt_e - gr_tnum + 1;
                tgc_e = tgt_b - 1;
            }

            for (auto tgc_index : tg_cont)
            {
                string tgc_r = tgc_index.substr(0, 2);
                int tgc_p = atoi(tgc_index.substr(2).c_str());

                if (tgc_r == "cb")
                {
                    ng.posi.push_back(g_posi[tgc_b + tgc_p]);
                }
                else if (tgc_r == "ce")
                {
                    ng.posi.push_back(g_posi[tgc_e - tgc_p]);
                }
                else if (tgc_r == "tb")
                {
                    ng.posi.push_back(g_posi[tgt_b + tgc_p]);
                }
                else if (tgc_r == "te")
                {
                    ng.posi.push_back(g_posi[tgt_e - tgc_p]);
                }
            }//end for
            for (auto tgt_index : tg_targ)
            {
                string tgt_r = tgt_index.substr(0, 2);
                int tgt_p = atoi(tgt_index.substr(2).c_str());

                if (tgt_r == "cb")
                {
                    ng.posi.push_back(g_posi[tgc_b + tgt_p]);
                }
                else if (tgt_r == "ce")
                {
                    ng.posi.push_back(g_posi[tgc_e - tgt_p]);
                }
                else if (tgt_r == "tb")
                {
                    ng.posi.push_back(g_posi[tgt_b + tgt_p]);
                }
                else if (tgt_r == "te")
                {
                    ng.posi.push_back(g_posi[tgt_e - tgt_p]);
                }
            }//end for
            this->insert_gate(c_it, ng);
        }//end if (tg_rule == "N")
        //E规则
        else if (tg_rule == "E")
        {
            GateInCircuit ng;
            ng.gateName = tg_name;

            ng.posi = g_posi;
            int tg_size = g_posi.size();

            int tgc_b, tgc_e, tgt_b, tgt_e;
            if (gr_cnum > 0)
            {
                tgc_b = 0;
                tgc_e = gr_cnum - 1;
                tgt_b = tgc_e + 1;
                tgt_e = tg_size - 1;
            }
            else if (gr_tnum > 0)
            {
                tgc_b = 0;
                tgt_e = tg_size - 1;
                tgt_b = tgt_e - gr_tnum + 1;
                tgc_e = tgt_b - 1;
            }

            for (auto tgc_index : tg_cont)
            {
                string tgc_r = tgc_index.substr(0, 2);
                int tgc_p = atoi(tgc_index.substr(2).c_str());

                if (tgc_r == "cb")
                {
                    ng.posi[tgc_b + tgc_p] = "-";
                }
                else if (tgc_r == "ce")
                {
                    ng.posi[tgc_e - tgc_p] = "-";
                }
                else if (tgc_r == "tb")
                {
                    ng.posi[tgt_b + tgc_p] = "-";
                }
                else if (tgc_r == "te")
                {
                    ng.posi[tgt_e - tgc_p] = "-";
                }
            }//end for
            for (auto tgt_index : tg_targ)
            {
                string tgt_r = tgt_index.substr(0, 2);
                int tgt_p = atoi(tgt_index.substr(2).c_str());

                if (tgt_r == "cb")
                {
                    ng.posi[tgc_b + tgt_p] = "-";
                }
                else if (tgt_r == "ce")
                {
                    ng.posi[tgc_e - tgt_p] = "-";
                }
                else if (tgt_r == "tb")
                {
                    ng.posi[tgt_b + tgt_p] = "-";
                }
                else if (tgt_r == "te")
                {
                    ng.posi[tgt_e - tgt_p] = "-";
                }
            }//end for
            vector<string>::iterator tg_itf, tg_its;
            tg_itf = tg_its = ng.posi.begin();
            int tg_popnum = 0;
            for (; tg_its != ng.posi.end(); ++tg_itf, ++tg_its)
            {
                while (*tg_its == "-")
                {
                    ++tg_its;
                    ++tg_popnum;
                }
                *tg_itf = *tg_its;
            }
            while (tg_popnum)
            {
                ng.posi.pop_back();
                --tg_popnum;
            }

            this->insert_gate(c_it, ng);
        }//end if (tg_rule == "E")
    }//end for
    return 1;
}

/**
*/
bool Circuit::matchgate(GateLib& glib)
{
    if (this->gateLibName != glib.get_gateLibName())
    {
        return 0;
    }
    Circuit::iterator c_it;
    for (c_it = this->begin(); c_it != this->end(); )
    {
        string gname = c_it.get_gateName();
        Gate* tgrule = glib.find(gname);
        if (tgrule->get_gateType() == -1)
        {
            return 0;
        }
        else if (tgrule->get_gateType() == 0)
        {
            ++c_it;
            continue;
        }
        else if (tgrule->get_gateType() == 1)
        {
            ComplexGate* tcg = (ComplexGate*)tgrule;
            //调用changegate
            if (! this->changegate(c_it, tcg))
            {
                return 0;
            }
        }
        else if (tgrule->get_gateType() == 2)
        {
            ComplexGate* tcg = (ComplexGate*)tgrule;
            //调用changegate
            int tg_recursion = (tcg->get_contNum() > 0) ? -tcg->get_targNum() : -tcg->get_contNum();
            int tg_present = c_it.get_posiNum();

            //递归情形
            if (tg_present > tg_recursion)
            {
                if (! this->changegate(c_it, tcg))
                {
                    return 0;
                }
                this->matchgate(glib);
            }
            //非递归情形
            else {
                string tg_relate = tcg->get_relateGate();
                Gate* tg_newgate = glib.find(tg_relate);
                if (tg_newgate->get_gateType() == -1)
                {
                    return 0;
                }
                else if (tg_newgate->get_gateType() == 0)
                {
                    continue;
                }
                else if (tg_newgate->get_gateType() == 1)
                {
                    ComplexGate *tg_newgate_cg = (ComplexGate*) tg_newgate;
                    if (! this->changegate(c_it, tg_newgate_cg))
                    {
                        return 0;
                    }
                }
            }
        }//end if (tgrule->get_gateType())
    }//end for

    this->quantumCost = 0;
    for (c_it = this->begin(); c_it != this->end(); ++c_it)
    {
        string gname = c_it.get_gateName();
        SimpleGate* tgrule = (SimpleGate(*))glib.find(gname);
        this->quantumCost += tgrule->get_quantumCost();
    }

    return 1;
}

/**
*/
bool Circuit::calculate(GateLib& glib, TruthInCircuit& trtable)
{
    for (auto c_it = this->begin(); c_it != this->end(); ++c_it)
    {
        string gname = c_it.get_gateName();
        if (glib.find(gname)->get_gateType() != 0)
        {
            return 0;
        }
    }

    int truthlength = this->get_variNum();
    int truthrange = pow(2, truthlength);

    for (int truth_D = 0; truth_D < truthrange; ++truth_D)
    {
        //十进制转换成二进制字符数组
        int ttruth_D = truth_D;
        int ttruth_index = truthlength - 1;
        char *ttruth_B = new char[truthlength + 1];
        ttruth_B[truthlength] = '\0';
        memset(ttruth_B, '0', truthlength);

        while (ttruth_D / 2)
        {
            ttruth_B[ttruth_index--] = '0' + ttruth_D % 2;
            ttruth_D /= 2;
        }
        ttruth_B[ttruth_index] = '0' + ttruth_D;

        //保存输入真值
        char *c_inputs = new char[truthlength + 1];
        strcpy(c_inputs, ttruth_B);

        //保存需计算真值
        string c_inputs_part;
        Circuit::iterator c_it;
        for (c_it = this->begin(); c_it != this->end(); ++c_it)
        {
            c_inputs_part.clear();
            //从this电路中提取被处理门的门名称，该门为基本门
            string gname = c_it.get_gateName();
            //遍历被处理门的所有位,并保存
            vector<int> gp_save;
            for (auto gp_index : c_it.get_posi())
            {
                vector<string>::iterator c_index;
                int c_index_num;
                for (c_index = this->variables.begin(), c_index_num = 0; c_index != this->variables.end(); ++c_index, ++c_index_num)
                {
                   if (gp_index == *c_index)
                   {
                       c_inputs_part += c_inputs[c_index_num];
                       gp_save.push_back(c_index_num);
                       break;
                   }
                }
            }
            //从GateLib& glib中提取被处理门
            SimpleGate* c_gate = (SimpleGate*)glib.find(gname);
            //真值运算
            c_inputs_part = c_gate->find(c_inputs_part);
            //保存运算结果
            int gp_save_index = 0;
            for (auto c_inputs_iter : c_inputs_part)
            {
                int c_inputs_posi = gp_save[gp_save_index++];
                c_inputs[c_inputs_posi] = c_inputs_iter;
            }
        }//end for this circuit

        string tmapf(ttruth_B);
        string tmaps(c_inputs);
        trtable.truthTable.insert(pair<string, string>(ttruth_B, c_inputs));
    }
    return 1;
}

/**
*/
bool Circuit::calculate_value(GateLib& glib, string& inputs, string& outputs)
{
    for (auto c_it = this->begin(); c_it != this->end(); ++c_it)
    {
        string gname = c_it.get_gateName();
        if (glib.find(gname)->get_gateType() != 0)
        {
            return 0;
        }
    }

    int truthlength = this->get_variNum();
    char *c_inputs = new char[inputs.length()];
    strcpy(c_inputs, inputs.c_str());

    string c_inputs_part;
    Circuit::iterator c_it;
    for (c_it = this->begin(); c_it != this->end(); ++c_it)
    {
        c_inputs_part.clear();
        string gname = c_it.get_gateName();
        vector<int> gp_save;
        for (auto gp_index : c_it.get_posi())
        {
            vector<string>::iterator c_index;
            int c_index_num;
            for (c_index = this->variables.begin(), c_index_num = 0; c_index != this->variables.end(); ++c_index, ++c_index_num)
            {
                if (gp_index == *c_index)
                {
                    c_inputs_part += c_inputs[c_index_num];
                    gp_save.push_back(c_index_num);
                    break;
                }
            }
        }
        //从GateLib& glib中提取被处理门
        SimpleGate* c_gate = (SimpleGate*)glib.find(gname);
        //真值运算
        c_inputs_part = c_gate->find(c_inputs_part);
        //保存运算结果
        int gp_save_index = 0;
        for (auto c_inputs_iter : c_inputs_part)
        {
            int c_inputs_posi = gp_save[gp_save_index++];
            c_inputs[c_inputs_posi] = c_inputs_iter;
        }
    }//end for this circuit
    outputs.clear();
    outputs.append(c_inputs);
    return 1;
}

/**
*/
int Circuit::get_variNum(void)
{
    return this->variNum;
}

/**
*/
int Circuit::get_quantumCost(void)
{
    return this->quantumCost;
}

/**
*/
int Circuit::get_gateNum(void)
{
    return this->gateNum;
}

/**
*/
string Circuit::get_circuitName(void)
{
    return this->circuitName;
}

/**
*/
string Circuit::get_gateLibName(void)
{
    return this->gateLibName;
}





/**
函数名:refresh
参数:this为隐含参数，指向本电路
功能:刷新变量variables名称

void Circuit::refresh(void)
{
    string tvname = "a";
    string::iterator tvname_it = tvari.begin();

    vector<string>::iterator v_it;
    for (v_it = this->variables.begin(); v_it != this->variables.end(); ++v_it)
    {
        v_it = tvname;
    }
}*/
