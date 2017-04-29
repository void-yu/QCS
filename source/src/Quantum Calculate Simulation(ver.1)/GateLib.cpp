#include "GateLib.h"

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <windows.h>

/**
s-String
o-old
t-temporary
ts-temporary stream/temporary string
*/
using namespace std;

GateLib::GateLib()
{
	this->gateLibName = "-";
	this->gateNum = 0;

	this->gateLibTable.clear();

	this->useEnable = 0;
}

/**
*/
bool GateLib::read(const string& filename)
{
    WIN32_FIND_DATAA fileinfo;
    string tsfname = filename + "\\*.gatelib";
    HANDLE hfile = FindFirstFile(tsfname.c_str(), &fileinfo);
    if (INVALID_HANDLE_VALUE == hfile)
    {
        return 0;
    }
    FindClose(hfile);

    ifstream glfile(filename + "\\" + fileinfo.cFileName);
	if (!glfile)
	{
		return 0;
	}
	streambuf * ocinbuf = cin.rdbuf(glfile.rdbuf());

	string tstream;
	while (!glfile.eof())
	{
		tstream.clear();
		getline(glfile, tstream, ':');

		if (tstream.compare("gateLibName") == 0)
		{
			cin >> this->gateLibName;
			cin.get();
		}
		else if (tstream.compare("gateNum") == 0)
		{
			cin >> this->gateNum;
			cin.get();
		}
		else if (tstream.compare("libTable") == 0)
		{
		    cin.get();
			while (getline(glfile, tstream, '\n'))
			{
			    if (tstream.empty())
			    {
			        break;
			    }

                string tmapf;
                Gate* tmaps;
			    string tgfname, tgtype;
			    int tsposi = 0;
			    tsposi = tstream.find(" ");
                tmapf = tstream.substr(0, tsposi);
                tgfname = filename + "\\" + tmapf + ".gaterule";
                tgtype = tstream.substr(tsposi + 1);
                if (tgtype == "0")
                {
                    tmaps = new SimpleGate();
                    if (!tmaps->read(tgfname))
                    {
                        return 0;
                    }
                }
                else {
                    tmaps = new ComplexGate();
                    if (!tmaps->read(tgfname))
                    {
                        return 0;
                    }
                }
                tmapf = tmaps->get_gateName();
                this->gateLibTable.insert(pair<string, Gate*>(tmapf, tmaps));
			}
			break;
		}
		else {
            return 0;
		}
	}
	glfile.close();
	cin.rdbuf(ocinbuf);

	this->useEnable = 1;
    return 1;
}

/**
*/
GateLib::~GateLib()
{
    this->gateLibTable.clear();
    this->useEnable = 0;
}

/**
*/
void GateLib::unload()
{

    this->gateLibTable.clear();
    this->useEnable = 0;
}

/**
*/
GateLib::iterator GateLib::begin(void)
{
    GateLib::iterator tgl_it;
    tgl_it.gateLibTableIter = this->gateLibTable.begin();
    return tgl_it;
}

/**
*/
GateLib::iterator GateLib::end(void)
{
    GateLib::iterator tgl_it;
    tgl_it.gateLibTableIter = this->gateLibTable.end();
    return tgl_it;
}

/**
*/
GateLib::iterator& GateLib::iterator::operator = (const GateLib::iterator& gl_it)
{
    GateLib::iterator tgl_it;
    tgl_it.gateLibTableIter = gl_it.gateLibTableIter;
    this->gateLibTableIter = gl_it.gateLibTableIter;
    return tgl_it;
}

/**
*/
GateLib::iterator& GateLib::iterator::operator ++ (void)
{
    ++(this->gateLibTableIter);
    return *this;
}

/**
*/
const GateLib::iterator GateLib::iterator::operator ++ (int)
{
    const GateLib::iterator tgl_it = *this;
    ++(this->gateLibTableIter);
    return tgl_it;
}

/**
*/
bool GateLib::iterator::operator == (const GateLib::iterator& gl_it)
{
    if (this->gateLibTableIter == gl_it.gateLibTableIter)
    {
        return 1;
    }
    else {
        return 0;
    }
}

/**
*/
bool GateLib::iterator::operator != (const GateLib::iterator& gl_it)
{
    if (this->gateLibTableIter != gl_it.gateLibTableIter)
    {
        return 1;
    }
    else {
        return 0;
    }
}

/**
*/
Gate* GateLib::find(const string& gname)
{
    Gate* ng = new NullGate();
    if (this->useEnable)
    {
        string tgname = gname;
        map<string, Gate*>::iterator rg = this->gateLibTable.find(tgname);
        if (rg == this->gateLibTable.end())
        {
            string::iterator tg_its = tgname.begin();
            string::iterator tg_itf;
            for (tg_itf = tg_its + 1; tg_itf != tgname.end();)
            {
                if (*tg_itf >= '0' && *tg_itf <= '9')
                {
                    if (*tg_its != '_')
                    {
                        tgname.replace(tg_itf, tg_itf + 1, 1, '_');
                        ++tg_itf;
                        ++tg_its;
                    }
                    else {
                        tg_itf = tgname.erase(tg_itf);
                    }
                }
                else {
                    ++tg_itf;
                    ++tg_its;
                }
            }
            rg = this->gateLibTable.find(tgname);
            if (rg == this->gateLibTable.end())
            {
                return ng;
            }
        }
        return rg->second;
    }
    else {
        return ng;
    }
}

/**
*/
string GateLib::iterator::get_gateName(void)
{
    return this->gateLibTableIter->first;
}

/**
*/
Gate* GateLib::iterator::get_gate(void)
{
    return this->gateLibTableIter->second;
}

/**
*/
int GateLib::get_gateNum(void)
{
    return this->gateNum;
}

/**
*/
string GateLib::get_gateLibName(void)
{
    return this->gateLibName;
}

/**
*/
bool GateLib::get_useEnable(void)
{
    return this->useEnable;
}
