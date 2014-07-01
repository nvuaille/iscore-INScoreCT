#ifndef INSCOREOBJECT_H
#define INSCOREOBJECT_H
#include <string>
#include <vector>
#include <iostream>
#include <map>

using namespace std;

/* **********************************************
 * Describe an INScore object, with all
 * informations needed to create it.
 * **********************************************/

class INScoreObject
{
public:
    INScoreObject();
    INScoreObject(string _name, string _scene);

    ~INScoreObject();

    /* ************************************************
     * get and set methods
     * ************************************************/
    string getName() const;
    void setName(const string &value);

    string getScene() const;
    void setScene(const string &value);

    string getPath() const;
    void setPath(const string &value);

    string getType() const;
    string getType(int _i);
    void setType(const int value);
    void setType(const string value);

    string getCreationValue() const;
    void setCreationValue(const string &value);

    bool isParameterChecked(int _i);
    bool isParameterChecked(string _name);
    void setParameter(string _name, bool _value);

    string getParameterName(int i);

    bool getToCreate() const;
    void setToCreate(bool value);

    float getInitValue(const string valueName);
    void setInitValue(const string name, const float value);

    /* ************************************************
     * get and set for signal vector
     * ************************************************/
    string getSignal(int _i);
    int getSignalSize();

    string getBufferSize(int _i);
    string getSignalValue(int _i);

    int nbTypes();
    int nbParameters();

    string getInitCommand();

private:
    string name;
    string scene;
    string path;  // form : /ITL/sceneName/objectName
    string type;
    string creationValue;

    map<string, float> initValues {{"red", 0}, {"green", 0}, {"blue", 0}, {"alpha", 255}, {"x", 0.0}, {"y", 0.0}, {"z", 0.0}, {"xorigin", 0.0}, {"yorigin", 0.0}, {"angle", 0}, {"scale", 1.0}};
    vector<string> parametersName {"display", "size", "color", "dcolor", "position", "dposition", "time", "dtime", "transformation", "signal"};

    map<string, bool> parametersList {{"display", true}, {"size", false}, {"color", false}, {"dcolor", false}, {"position", false}, {"dposition", false}, {"time", false}, {"dtime", false}, {"transformation", false}, {"signal", false}};

    bool toCreate;

    // default setup
    vector<string> typesEnabled {"none", "curve", "ellipse", "fastgraph", "file", "gmnf", "grid", "graph", "html", "layer", "line xy" ,      "polygon",       "rect",  "svgf", "txt"};
    vector<string> defaultValues {"",      "",     "1. 1.",     "",         "",     "",   "1 1", "mySignal",  "",    "" ,      "1. 1." ,"0. 0. 1. 1. 0. 1.",  "1. 1.",  "", "\"hello\""};

    // signal
    vector<string> signal {           "y",   "t",   "h",   "s",   "b",   "a" };
    vector<string> signalBufferSize {"200", "200", "200", "200", "200", "200"};
    vector<string> signalValue {     "0.0","0.05", "0.0", "1.0", "1.0", "-1.0"};
};

#endif // INSCOREOBJECT_H
