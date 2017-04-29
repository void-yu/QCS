#ifndef CIRCUIT_H_INCLUDED
#define CIRCUIT_H_INCLUDED

#include <string>
#include <vector>
#include <list>

#include "GateLib.h"

using namespace std;

/**
*/
struct GateInCircuit{
    string gateName;
    vector<string> posi;
};

struct TruthInCircuit{
	map<string, string> truthTable;
};

/**
*/
class Circuit{

private:
    string circuitName = "-";
    string gateLibName = "-";
    int gateNum = 0;
    int quantumCost = 0;
    int variNum = 0;
    vector<string> variables;
    vector<string> inputs;
    vector<string> outputs;
    string constants = "";
    string garbage = "";
    list<GateInCircuit> gateList;

public:
    class iterator{

    private:
        list<GateInCircuit>::iterator gateListIter;

    private:
        friend class Circuit;

    public:
        Circuit::iterator& operator = (const Circuit::iterator&);
        Circuit::iterator& operator ++ ();
        const Circuit::iterator operator ++ (int);
        bool operator == (const Circuit::iterator&);
        bool operator != (const Circuit::iterator&);

        string get_gateName(void);
        vector<string> get_posi(void);
        int get_posiNum(void);
    };

public:
    Circuit();

    bool read(const string&);
    void print(void);
	Circuit::iterator begin(void);
	Circuit::iterator end(void);
	Circuit::iterator back(void);
	Circuit& operator = (const Circuit&);

    bool insert_gate(Circuit::iterator&, GateInCircuit&);
    bool erase_gate(Circuit::iterator&);
    //bool insert_line(vector<string>::iterator&, string);
    //bool erase_line(vector<string>::iterator&);
    bool changegate(Circuit::iterator&, ComplexGate*);
    bool matchgate(GateLib&);
    bool calculate(GateLib&, TruthInCircuit&);
    bool calculate_value(GateLib&, string&, string&);
    //void refresh(void);

    int get_variNum(void);
    int get_quantumCost(void);
    int get_gateNum(void);
    string get_circuitName(void);
    string get_gateLibName(void);
};


#endif // CIRCUIT_H_INCLUDED
