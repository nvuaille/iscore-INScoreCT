#include "../headers/variable.h"

Variable::Variable(): name(" "), object(" "), service("parameter"), type("none"), rangeBounds(" "), rangeClipmode("none"), priority("0"), tag(" ")
{
    updateAttributeValue();
}
/*
Variable::Variable(const Variable &_var): object(_var.getObject()), priority(_var.getPriority()), type(_var.getType()), tag(_var.getTag()), rangeBounds(_var.getRangeBounds()), rangeClipmode(_var.getRangeClipmode()), service(_var.getService()), name(_var.getVariableName())
{

}*/

Variable::Variable(string _name, string _type, string _rangeBounds, string _rangeClipmode, string _priority, string _service, string _object) : name(_name), object(_object), service(_service), type(_type), rangeBounds(_rangeBounds), rangeClipmode(_rangeClipmode), priority(_priority), tag(_name)
{
    updateAttributeValue();
}

Variable Variable::copyVariable(const Variable _var)
{
    Variable buffer(_var);
    return buffer;
}

/* ************************************************
 * get and set methods
 * ************************************************/

// name
string Variable::getVariableName() const
{
    return name;
}
void Variable::setName(const string &value)
{
    name = value;
}

// object
string Variable::getObject() const
{
    return object;
}
void Variable::setObject(const string &value)
{
    object = value;
    updateAttributeValue();
}

// service
string Variable::getService() const
{
    return service;
}
void Variable::setService(const string &value)
{
    service = "parameter";
    int comparison = value.compare(string("parameter")) * value.compare(string("message")) * value.compare(string("return"));
    if(comparison == 0) { service = value; }
    updateAttributeValue();
}

// type
string Variable::getType() const
{
    return type;
}
void Variable::setType(const string &value)
{
    type = "none";
    int comparison = value.compare(string("none")) * value.compare(string("boolean")) * value.compare(string("integer")) * value.compare(string("decimal")) * value.compare(string("string")) * value.compare(string("array")) * value.compare(string("generic"));
    if(comparison == 0) {type = value;}
    updateAttributeValue();
}

// rangebounds
string Variable::getRangeBounds() const
{
    return rangeBounds;
}
void Variable::setRangeBounds(const string &value)
{
    rangeBounds = value;
    updateAttributeValue();
}

// rangeClipmode
string Variable::getRangeClipmode() const
{
    return rangeClipmode;
}
void Variable::setRangeClipmode(const string &value)
{
    rangeClipmode = "none";
    int comparison = value.compare(string("none")) * value.compare(string("both")) * value.compare(string("low")) * value.compare(string("high"));
    if(comparison == 0) {rangeClipmode = value;}
    updateAttributeValue();
}

// priority
string Variable::getPriority() const
{
    return priority;
}
void Variable::setPriority(const string &value)
{
    priority = value;
    updateAttributeValue();
}

// tag
string Variable::getTag() const
{
    return tag;
}
void Variable::setTag(const string &value)
{
    tag = value;
    updateAttributeValue();
}

/* *************************************************************** */

void Variable::updateAttributeValue()
{
    attributeValue = {object,service, type, rangeBounds, rangeClipmode, priority, tag};
}

string Variable::getAttributeName(int _i)
{
    if(_i>=0 && _i<nbAttribute()) {
        return attributeName[_i];
    }
    else {
        return "";
    }
}

string Variable::getAttributeValue(int _i)
{
    if(_i>=0 && _i<nbAttribute()) {
        return attributeValue[_i];
    }
    else {
        return "";
    }
}
int Variable::nbAttribute() const
{
    return int(attributeName.size());
}
