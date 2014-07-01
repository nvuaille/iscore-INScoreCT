#include "../headers/parameter.h"

Parameter::Parameter()
{
    variables.clear();
}

Parameter::Parameter(string _name) : name(_name)
{
    variables.clear();
}

string Parameter::getParameterName() const
{
    return name;
}

void Parameter::addVariable(Variable *_var)
{
    variables.push_back(_var);
}

Variable Parameter::getVariable(int _i) const
{
    Variable voidVar;
    if(_i< int(variables.size()) && _i>= 0) {
       return *variables[_i];
    }
     else return voidVar;
}

int Parameter::getNbVariable() const
{
    return int(variables.size());
}



