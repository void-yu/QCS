#include "Gate.h"

#include <fstream>
#include <iostream>
#include <string>
#include <map>

/**
s-String
sg-SimpleGate
o-old
t-temporary
ts-temporary stream/temporary string
*/
using namespace std;

SimpleGate::SimpleGate()
{
	this->gateName = "-";
	this->gateLibName = "-";
	this->gateType = -1;
	this->contNum = -1;
	this->targNum = -1;

	this->quantumCost = 0;
	this->truthTable.clear();

	this->useEnable = 0;
}

/**
*/
bool SimpleGate::read(const string& filename)
{
	ifstream sgfile(filename);
	if (!sgfile)
	{
		return 0;
	}
	streambuf * ocinbuf = cin.rdbuf(sgfile.rdbuf());

	string tstream;
	while (!sgfile.eof())
	{
		tstream.clear();
		getline(sgfile, tstream, ':');

		if (tstream.compare("gateName") == 0)
		{
			cin >> this->gateName;
			cin.get();
		}
		else if (tstream.compare("gateLibName") == 0)
		{
			cin >> this->gateLibName;
			cin.get();
		}
		else if (tstream.compare("gateType") == 0)
		{
			cin >> this->gateType;
			cin.get();
		}
		else if (tstream.compare("controlNum") == 0)
		{
			cin >> this->contNum;
			cin.get();
		}
		else if (tstream.compare("targetNum") == 0)
		{
			cin >> this->targNum;
			cin.get();
		}
		else if (tstream.compare("quantumCost") == 0)
		{
			cin >> this->quantumCost;
			cin.get();
		}
		else if (tstream.compare("truthTable") == 0)
		{
		    cin.get();
			while (getline(sgfile, tstream, '\n'))
			{
			    if (tstream.empty())
			    {
			        break;
			    }

			    string tmapf, tmaps;

                string::iterator ts_it;
                int tsposi = 0;
                for (ts_it = tstream.begin(); ts_it != tstream.end(); ++ts_it)
                {
                    if (*ts_it == ' ' || *ts_it == ':')
                    {
                        tstream.erase(ts_it);
                    }
                }

                tsposi = tstream.find("->");
                tmapf = tstream.substr(0, tsposi);
                tmaps = tstream.substr(tsposi + 2);

                this->truthTable.insert(pair<string, string>(tmapf, tmaps));
			}
			break;
		}
		else {
            return 0;
		}
	}
	sgfile.close();
	cin.rdbuf(ocinbuf);

	this->useEnable = 1;
    return 1;
}

/**
*/
string SimpleGate::find(const string& truth)
{
    if (this->useEnable)
    {
        string ttruth = truth;
        string::iterator ts_it;
        for (ts_it = ttruth.begin(); ts_it != ttruth.end(); ++ts_it)
        {
            if (*ts_it == ' ' || *ts_it == ':')
            {
                ttruth.erase(ts_it);
            }
        }
        if ((this->truthTable).find(ttruth) == this->truthTable.end())
        {
            return "";
        }
        else {
            return this->truthTable.find(ttruth)->second;
        }
    }
    else {
        return "";
    }
}

/**
*/
bool SimpleGate::operator == (const SimpleGate& tGate)
{
    if (this->useEnable == 0 || tGate.useEnable == 0)
    {
        return 0;
    }
    else if (this->contNum != tGate.contNum)
    {
        return 0;
    }
    else if (this->targNum != tGate.targNum)
    {
        return 0;
    }
    else if (this->truthTable.size() != tGate.truthTable.size())
    {
        return 0;
    }
    else {
        for (const auto &ttruth : this->truthTable)
        {
            string tsfir = ttruth.second;
            string tssec = tGate.truthTable.find(ttruth.first)->second;
            if (tsfir.compare(tssec))
            {
                return 0;
            }
        }
    }
    return 1;
}

/**
*/
SimpleGate::~SimpleGate()
{
    truthTable.clear();
    this->useEnable = 0;
}

/**
*/
SimpleGate::iterator SimpleGate::begin(void)
{
    SimpleGate::iterator tsg_it;
    tsg_it.truthTableIter = this->truthTable.begin();
    return tsg_it;
}

/**
*/
SimpleGate::iterator SimpleGate::end(void)
{
    SimpleGate::iterator tsg_it;
    tsg_it.truthTableIter = this->truthTable.end();
    return tsg_it;
}

/**
*/
SimpleGate::iterator& SimpleGate::iterator::operator = (const SimpleGate::iterator& sg_it)
{
    SimpleGate::iterator tsg_it;
    tsg_it.truthTableIter = sg_it.truthTableIter;
    this->truthTableIter = sg_it.truthTableIter;
    return tsg_it;
}

/**
*/
SimpleGate::iterator& SimpleGate::iterator::operator ++ (void)
{
    ++(this->truthTableIter);
    return *this;
}

/**
*/
const SimpleGate::iterator SimpleGate::iterator::operator ++ (int)
{
    const SimpleGate::iterator tsg_it = *this;
    ++(this->truthTableIter);
    return tsg_it;
}

/**
*/
bool SimpleGate::iterator::operator == (const SimpleGate::iterator& sg_it)
{
    if (this->truthTableIter == sg_it.truthTableIter)
    {
        return 1;
    }
    else {
        return 0;
    }
}

/**
*/
bool SimpleGate::iterator::operator != (const SimpleGate::iterator& sg_it)
{
    if (this->truthTableIter != sg_it.truthTableIter)
    {
        return 1;
    }
    else {
        return 0;
    }
}

/**
*/
string SimpleGate::iterator::input(void)
{
    return this->truthTableIter->first;
}

/**
*/
string SimpleGate::iterator::output(void)
{
    return this->truthTableIter->second;
}

/**
*/
int SimpleGate::get_gateType(void)
{
    return this->gateType;
}

/**
*/
bool SimpleGate::get_useEnable(void)
{
    return this->useEnable;
}

/**
*/
int SimpleGate::get_contNum(void)
{
    return this->contNum;
}

/**
*/
int SimpleGate::get_targNum(void)
{
    return this->targNum;
}

/**
*/
string SimpleGate::get_gateName(void)
{
    return this->gateName;
}

/**
*/
int SimpleGate::get_quantumCost(void)
{
    return this->quantumCost;
}

////////////////////////////////////////////


ComplexGate::ComplexGate()
{
	this->gateName = "-";
	this->gateLibName = "-";
	this->gateType = -1;
	this->contNum = -1;
	this->targNum = -1;

	this->ruleTable.clear();

	this->useEnable = 0;
}

/**
*/
bool ComplexGate::read(const string& filename)
{
	ifstream cgfile(filename);
	if (!cgfile)
	{
		return 0;
	}
	streambuf * ocinbuf = cin.rdbuf(cgfile.rdbuf());

	string tstream;
	while (!cgfile.eof())
	{
		tstream.clear();
		getline(cgfile, tstream, ':');

		if (tstream.compare("gateName") == 0)
		{
			cin >> this->gateName;
			cin.get();
		}
		else if (tstream.compare("gateLibName") == 0)
		{
			cin >> this->gateLibName;
			cin.get();
		}
		else if (tstream.compare("gateType") == 0)
		{
			cin >> this->gateType;
			cin.get();
		}
		else if (tstream.compare("relateGate") == 0)
        {
            cin >> this->relateGate;
            cin.get();
        }
		else if (tstream.compare("controlNum") == 0)
		{
			cin >> this->contNum;
			cin.get();
		}
		else if (tstream.compare("targetNum") == 0)
		{
			cin >> this->targNum;
			cin.get();
		}
		else if (tstream.compare("ruleTable") == 0)
		{
		    cin.get();
			while (getline(cgfile, tstream, '\n'))
			{
			    RuleStruct trule;
			    string tscontrol, tstarget;

                int tsposi = 0;
                int ts_size;
                vector<string> ts_split;

                tstream += ' ';
                ts_size = tstream.size();
                for (int ts_index = 0; ts_index != ts_size; ++ts_index)
                {
                    tsposi = tstream.find(" ", ts_index);
                    if (tsposi < ts_size)
                    {
                        ts_split.push_back(tstream.substr(ts_index, tsposi - ts_index));
                        ts_index = tsposi;
                    }
                }

                trule.ruleName = ts_split[0];
                trule.gateName = ts_split[1];

                tsposi = ts_split[2].find(":");
                tscontrol = ts_split[2].substr(0, tsposi);
                tstarget = ts_split[2].substr(tsposi + 1);
                tscontrol += ',';
                tstarget += ',';
                int tsc_size = tscontrol.size();
                int tst_size = tstarget.size();

                for (int tsc_index = 0; tsc_index != tsc_size; ++tsc_index)
                {
                    int tscposi = 0;
                    tscposi = tscontrol.find(",", tsc_index);
                    if (tscposi < tsc_size)
                    {
                        string tsc_push = tscontrol.substr(tsc_index, tscposi - tsc_index);
                        if (tsc_push != "")
                        {
                            trule.contPosi.push_back(tsc_push);
                        }
                        tsc_index = tscposi;
                    }
                }
                for (int tst_index = 0; tst_index != tst_size; ++tst_index)
                {
                    int tstposi = 0;
                    tstposi = tstarget.find(",", tst_index);
                    if (tstposi < tst_size)
                    {
                        string tst_push = tstarget.substr(tst_index, tstposi - tst_index);
                        if (tst_push != "")
                        {
                            trule.targPosi.push_back(tst_push);
                        }
                        tst_index = tstposi;
                    }
                }
                this->ruleTable.push_back(trule);
			}
		}
		else
        {
            return 0;
		}
	}
	cgfile.close();
	cin.rdbuf(ocinbuf);

    if (this->gateType == 1)
    {
        this->relateGate = this->gateName;
    }

	this->useEnable = 1;
    return 1;
}

/**
*/
bool ComplexGate::operator == (const ComplexGate& tGate)
{
    if (this->useEnable == 0 || tGate.useEnable == 0)
    {
        return 0;
    }
    else if (this->contNum != tGate.contNum)
    {
        return 0;
    }
    else if (this->targNum != tGate.targNum)
    {
        return 0;
    }
    else if (this->ruleTable.size() != tGate.ruleTable.size())
    {
        return 0;
    }
    else {
        for (int tindex = 0; tindex < this->ruleTable.size(); ++tindex)
        {
            string tsfir;
            string tssec;

            tsfir = this->ruleTable[tindex].ruleName;
            tssec = tGate.ruleTable[tindex].ruleName;
            if (tsfir != tssec)
            {
                return 0;
            }

            tsfir = this->ruleTable[tindex].gateName;
            tssec = tGate.ruleTable[tindex].gateName;
            if (tsfir != tssec)
            {
                return 0;
            }

            if (this->ruleTable[tindex].contPosi != tGate.ruleTable[tindex].contPosi)
            {
                return 0;
            }
            if (this->ruleTable[tindex].targPosi != tGate.ruleTable[tindex].targPosi)
            {
                return 0;
            }
        }
    }
    return 1;
}

/**
*/
ComplexGate::~ComplexGate()
{
    this->ruleTable.clear();
    this->useEnable = 0;
}

/**
*/
ComplexGate::iterator ComplexGate::begin(void)
{
    ComplexGate::iterator tcg_it;
    tcg_it.ruleTableIter = this->ruleTable.begin();
    return tcg_it;
}

/**
*/
ComplexGate::iterator ComplexGate::end(void)
{
    ComplexGate::iterator tcg_it;
    tcg_it.ruleTableIter = this->ruleTable.end();
    return tcg_it;
}

/**
*/
ComplexGate::iterator& ComplexGate::iterator::operator = (const ComplexGate::iterator& cg_it)
{
    ComplexGate::iterator tcg_it;
    tcg_it.ruleTableIter = cg_it.ruleTableIter;
    this->ruleTableIter = cg_it.ruleTableIter;
    return tcg_it;
}

/**
*/
ComplexGate::iterator& ComplexGate::iterator::operator ++ (void)
{
    ++(this->ruleTableIter);
    return *this;
}

/**
*/
const ComplexGate::iterator ComplexGate::iterator::operator ++ (int)
{
    const ComplexGate::iterator tcg_it = *this;
    ++(this->ruleTableIter);
    return tcg_it;
}

/**
*/
bool ComplexGate::iterator::operator == (const ComplexGate::iterator& cg_it)
{
    if (this->ruleTableIter == cg_it.ruleTableIter)
    {
        return 1;
    }
    else {
        return 0;
    }
}

/**
*/
bool ComplexGate::iterator::operator != (const ComplexGate::iterator& cg_it)
{
    if (this->ruleTableIter != cg_it.ruleTableIter)
    {
        return 1;
    }
    else {
        return 0;
    }
}

/**
*/
const string ComplexGate::iterator::get_ruleName(void)
{
    string trname = this->ruleTableIter->ruleName;
    return trname;
}

/**
*/
const string ComplexGate::iterator::get_gateName(void)
{
    string tgname = this->ruleTableIter->gateName;
    return tgname;
}

/**
*/
const vector<string> ComplexGate::iterator::get_contPosi(void)
{
    vector<string> tcposi = this->ruleTableIter->contPosi;
    return tcposi;
}

/**
*/
const vector<string> ComplexGate::iterator::get_targPosi(void)
{
    vector<string> ttposi = this->ruleTableIter->targPosi;
    return ttposi;
}

/**
*/
int ComplexGate::get_gateType(void)
{
    return this->gateType;
}

/**
*/
bool ComplexGate::get_useEnable(void)
{
    return this->useEnable;
}

/**
*/
int ComplexGate::get_contNum(void)
{
    return this->contNum;
}

/**
*/
int ComplexGate::get_targNum(void)
{
    return this->targNum;
}

/**
*/
string ComplexGate::get_gateName(void)
{
    return this->gateName;
}

/**
*/
string ComplexGate::get_relateGate(void)
{
    return this->relateGate;
}


////////////////////////////////////////////


bool NullGate::read(const string&)
{
    return 1;
}

bool NullGate::read(void)
{
    return 1;
}

int NullGate::get_gateType(void)
{
    return -1;
}

bool NullGate::get_useEnable(void)
{
    return 0;
}

string NullGate::get_gateName(void)
{
    return "-";
}
