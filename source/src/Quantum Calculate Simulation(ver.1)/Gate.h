#ifndef GATE_H_INCLUDED
#define GATE_H_INCLUDED

#include <string>
#include <map>
#include <vector>

using namespace std;

/**
*/
class Gate{

protected:
	string gateName = "-";
	string gateLibName = "-";
	int gateType = 0;//0-基本门;1-非基本门;2-非基本可递归门
	int contNum = 0;
	int targNum = 0;
	bool useEnable = 0;

public:
	virtual bool read(const string&) = 0;

	virtual string get_gateName(void) = 0;
	virtual int get_gateType(void) = 0;
    virtual bool get_useEnable(void) = 0;
};


/**
*/
class SimpleGate : public Gate{

private:
    int quantumCost = 0;
	map<string, string> truthTable;

public:
    class iterator{

    private:
        map<string, string>::iterator truthTableIter;

    private:
        friend class SimpleGate;

    public:
        SimpleGate::iterator& operator = (const SimpleGate::iterator&);
        SimpleGate::iterator& operator ++ ();
        const SimpleGate::iterator operator ++ (int);
        bool operator == (const SimpleGate::iterator&);
        bool operator != (const SimpleGate::iterator&);

        string input(void);
        string output(void);
    };

public:
	SimpleGate();

	bool read(const string&);
	string find(const string&);
	bool operator == (const SimpleGate&);
	SimpleGate::iterator begin(void);
	SimpleGate::iterator end(void);

	int get_gateType(void);
	bool get_useEnable(void);
	string get_gateName(void);
	int get_contNum(void);
	int get_targNum(void);
	int get_quantumCost(void);

	~SimpleGate();
};


/**
*/
struct RuleStruct{
    string ruleName;
    string gateName;
    vector<string> contPosi;
    vector<string> targPosi;
};

/**
*/
class ComplexGate : public Gate{

private:
    string relateGate = "-";
	vector<RuleStruct> ruleTable;

public:
    class iterator{
    private:
        vector<RuleStruct>::iterator ruleTableIter;

    private:
        friend class ComplexGate;

    public:
        ComplexGate::iterator& operator = (const ComplexGate::iterator&);
        ComplexGate::iterator& operator ++ ();
        const ComplexGate::iterator operator ++ (int);
        bool operator == (const ComplexGate::iterator&);
        bool operator != (const ComplexGate::iterator&);

        const string get_ruleName(void);
        const string get_gateName(void);
        const vector<string> get_contPosi(void);
        const vector<string> get_targPosi(void);
    };

public:
    ComplexGate();

	bool read(const string&);
	bool operator == (const ComplexGate&);
	ComplexGate::iterator begin(void);
	ComplexGate::iterator end(void);

	int get_gateType(void);
	bool get_useEnable(void);
    string get_gateName(void);
    string get_relateGate(void);
	int get_contNum(void);
	int get_targNum(void);

	~ComplexGate();
};


/**
*/
class NullGate : public Gate{

public:
    bool read(const string&);
    bool read(void);

	string get_gateName(void);
	int get_gateType(void);
	bool get_useEnable(void);
};


#endif // GATE_H_INCLUDED
