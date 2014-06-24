#ifndef PARAMETER_H
#define PARAMETER_H
#include "variable.h"
#include <string>
#include <vector>

using namespace std;

/* ***************************************************
 * A parameter is a collection of variables
 *
 *      for example the parameter "color" can contain
 *      R,G and B var
 * ***************************************************/

class Parameter
{
public:
    Parameter();
    Parameter(string _name);

    string getParameterName() const;

    void addVariable(Variable* _var);
    Variable getVariable(int _i) const;

    int getNbVariable() const;

private:
    string name;
    vector<Variable*> variables;

};

#endif // PARAMETER_H
