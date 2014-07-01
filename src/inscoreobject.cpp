#include "../headers/inscoreobject.h"

/* ************************************************
 * ctor & dtor
 * ************************************************/
INScoreObject::INScoreObject(): name(" "), scene(" "), path(" "), type("rect"), creationValue("1. 1."), toCreate(true)
{

}

INScoreObject::INScoreObject(string _name, string _scene) : name(_name), scene(_scene)
{
    path = string("/ITL/") + _scene + string("/") + _name;
}


INScoreObject::~INScoreObject()
{

}

/* ************************************************
 * get and set methods
 * ************************************************/

// name
string INScoreObject::getName() const
{
    return name;
}
void INScoreObject::setName(const string &value)
{
    name = value;
}

// scene
string INScoreObject::getScene() const
{
    return scene;
}
void INScoreObject::setScene(const string &value)
{
    scene = value;
    string newPath = string("/ITL/") + scene + string("/") + name;
    path = newPath;
}

// path
string INScoreObject::getPath() const
{
    return path;
}
void INScoreObject::setPath(const string &value)
{
    path = value;
    string newScene = "";
    string delimiter = "/";
    size_t pos = 0;

    for (int i = 0; i<3; i++) {
        pos = path.find(delimiter);
        newScene = path.substr(0,pos);
        path.erase(0, pos + delimiter.length());
    }
    path = value;
    scene = newScene;
}

// type
string INScoreObject::getType() const
{
    return type;
}
void INScoreObject::setType(const int value)
{
    if(value>=0 && value< int(typesEnabled.size())) {
        type = typesEnabled[value];
        setCreationValue(defaultValues[value]);
    }
    if(typesEnabled[value].compare("graph") == 0) {
        setCreationValue(defaultValues[value] + name);
    }
}

void INScoreObject::setType(const string value)
{
    int i =0;
    setType(2);
    while(i< int(typesEnabled.size()))
    {
        if(value.compare(typesEnabled[i]) == 0) {
            setType(i);
        }
        ++i;
    }
}

string INScoreObject::getType(int _i)
{
    if(_i>=0 && _i< int(typesEnabled.size())) {
        return typesEnabled[_i];
    }
    else return "";
}

// creation value
string INScoreObject::getCreationValue() const
{
    return creationValue;
}

void INScoreObject::setCreationValue(const string &value)
{
    creationValue = value;
}

// parameter check
bool INScoreObject::isParameterChecked(int _i)
{
    if (_i>=0 &&_i < int(parametersName.size()))
    {
        return parametersList.find(parametersName[_i])->second;
    }
    else
    {
        return false;
    }
}

bool INScoreObject::isParameterChecked(string _name)
{
    bool buffer = false;
    if(parametersList.find(_name)!=parametersList.end()) {
            buffer = parametersList.find(_name)->second;
    }
    return buffer;
}

void INScoreObject::setParameter(string _name, bool _value)
{
    if(parametersList.find(_name)!=parametersList.end()) {
            parametersList[_name] = _value;
    }
}

string INScoreObject::getParameterName(int i)
{
    string buffer = "";
    if(i < int(parametersName.size()) && i>=0) {
        buffer = parametersName[i];
    }
    return buffer;
}


// to create
bool INScoreObject::getToCreate() const
{
    return toCreate;
}

void INScoreObject::setToCreate(bool value)
{
    toCreate = value;
}

float INScoreObject::getInitValue(const string valueName)
{
    if(initValues.find(valueName) != initValues.end()) {
        return initValues.find(valueName)->second;
    }
    else return 0;
}

void INScoreObject::setInitValue(const string name, const float value)
{
    if(initValues.find(name) != initValues.end()) {
        initValues[name]=value;
    }
}


// signal name
string INScoreObject::getSignal(int _i)
{
    if(_i > 0 || _i < int(signal.size())) {
        return signal[_i];
    }
    else return "";
}

// size
int INScoreObject::getSignalSize()
{
    return signal.size();
}

// buffer size
string INScoreObject::getBufferSize(int _i)
{
    return signalBufferSize[_i];
}

// init value
string INScoreObject::getSignalValue(int _i)
{
    return signalValue[_i];
}

int INScoreObject::nbTypes()
{
    return typesEnabled.size();
}

int INScoreObject::nbParameters()
{
    return int(parametersList.size());
}

string INScoreObject::getInitCommand()
{
    string command = path + " set " + type + " " + creationValue + ";\n";

    map<string, float>::iterator it = initValues.begin();
    while(it != initValues.end()) {
        command += path + " " + it->first + " " + std::to_string(it->second) + ";\n";
        ++it;
    }

    return command;
}
