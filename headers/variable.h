#ifndef VARIABLE_H
#define VARIABLE_H
#include <string>
#include <vector>
#include <iostream>

using namespace std;

/* **********************************************************
 * This class describes a variable : type, range ...
 * all that's needed by i-score to create the OSC tree
 * **********************************************************/

class Variable
{
public:
    Variable();
//    Variable(const Variable &_var);
    Variable(string _name,string _type, string _rangeBounds="0 100", string _rangeClipmode="none", string _priority="0", string _service="parameter", string _object = "Data");

    Variable copyVariable(const Variable _var);

    /* ************************************************
     * get and set methods
     * ************************************************/

    string getVariableName() const;
    void setName(const string &value);

    string getObject() const;
    void setObject(const string &value);

    string getService() const;
    void setService(const string &value);

    string getType() const;
    void setType(const string &value);

    string getRangeBounds() const;
    void setRangeBounds(const string &value);

    string getRangeClipmode() const;
    void setRangeClipmode(const string &value);

    string getPriority() const;
    void setPriority(const string &value);

    string getTag() const;
    void setTag(const string &value);

    /* ************************************************
     * updates the vector attributesValue
     * It's called each time an attribute is setup
     * ************************************************/
    void updateAttributeValue();

    string getAttributeName(int _i);
    string getAttributeValue(int _i);

    int nbAttribute() const; // = size of attributeName

private:
    string name;

    /* ************************************************
     * list of attributes
     *      used in class definition only
     * ************************************************/
    string object;
    string service;
    string type;
    string rangeBounds;
    string rangeClipmode;
    string priority;
    string tag;

    /* ************************************************
     * vectors of attributes names and values
     * ************************************************/
    vector<string> attributeName {"object", "service", "type", "rangeBounds", "rangeClipmode", "priority", "tag"};
    vector<string> attributeValue;
};

#endif // VARIABLE_H
