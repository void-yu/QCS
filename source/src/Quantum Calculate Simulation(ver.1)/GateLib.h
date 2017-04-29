#ifndef GATELIB_H_INCLUDED
#define GATELIB_H_INCLUDED

#include <string>
#include <map>

#include "Gate.h"

using namespace std;

class GateLib{

private:
	string gateLibName = "-";
    int gateNum = 0;
    bool useEnable = 0;
    map<string, Gate*> gateLibTable;

public:
    class iterator{

    private:
        map<string, Gate*>::iterator gateLibTableIter;

    private:
        friend class GateLib;

    public:
        GateLib::iterator& operator = (const GateLib::iterator&);
        GateLib::iterator& operator ++ ();
        const GateLib::iterator operator ++ (int);
        bool operator == (const GateLib::iterator&);
        bool operator != (const GateLib::iterator&);
        string get_gateName(void);
        Gate* get_gate(void);
    };

public:
    GateLib();

	bool read(const string&);
    Gate* find(const string&);
	GateLib::iterator begin(void);
	GateLib::iterator end(void);

	string get_gateLibName(void);
	int get_gateNum(void);
	bool get_useEnable(void);

	~GateLib();
	void unload();
};

#endif // GATELIB_H_INCLUDED
