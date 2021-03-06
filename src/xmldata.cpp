#include "../headers/xmldata.h"

/* ***********************************************************
 * List of all parameters
 *
 * Color : Red, Green, Blue, Hue, Saturation, Brightness, Alpha
 *      + delta color : the same
 *
 * Position : X, Y, Z, Xorigin, Yorigin, Angle, Scale
 *      + delta Position : the same
 *
 * Size : Width, Height
 *
 * Transformation : rotatex, rotatey, rotatezs
 *
 * Time : Date, Duration
 *      + delta Date : the same
 * *********************************************************/

XmlData::XmlData()
{
    int i=0;
    //STARTSTOP
    parameters.push_back(new Parameter("display"));
        parameters[i]->addVariable(new Variable("show","integer","0 1","both","1"));
        ++i;
    //COLOR
    parameters.push_back(new Parameter("color"));
        parameters[i]->addVariable(new Variable("red","integer","0 255","both","1"));
        parameters[i]->addVariable(new Variable("green","integer","0 255","both","1"));
        parameters[i]->addVariable(new Variable("blue","integer","0 255","both","1"));
        parameters[i]->addVariable(new Variable("hue","integer","0 360","low","1"));
        parameters[i]->addVariable(new Variable("saturation","integer","0 100","both","1"));
        parameters[i]->addVariable(new Variable("brightness","integer","0 100","both","1"));
        parameters[i]->addVariable(new Variable("alpha","integer","0 255","both","1"));
        ++i;
    //DCOLOR
    parameters.push_back(new Parameter("dcolor"));
        parameters[i]->addVariable(new Variable("dred","integer","-255 255","both","1"));
        parameters[i]->addVariable(new Variable("dgreen","integer","-255 255","both","1"));
        parameters[i]->addVariable(new Variable("dblue","integer","-255 255","both","1"));
        parameters[i]->addVariable(new Variable("dhue","integer","-360 360","both","1"));
        parameters[i]->addVariable(new Variable("dsaturation","integer","-100 100","both","1"));
        parameters[i]->addVariable(new Variable("dbrightness","integer","-100 100","both","1"));
        parameters[i]->addVariable(new Variable("dalpha","integer","-255 255","both","1"));
        ++i;

    //POSITION
    parameters.push_back(new Parameter("position"));
        parameters[i]->addVariable(new Variable("x","decimal","-2 2","none","1"));
        parameters[i]->addVariable(new Variable("y","decimal","-2 2","none","1"));
        parameters[i]->addVariable(new Variable("z","decimal","-2 2","none","1"));
        parameters[i]->addVariable(new Variable("xorigin","integer","-1 1","none","1"));
        parameters[i]->addVariable(new Variable("yorigin","integer","-1 1","none","1"));
        parameters[i]->addVariable(new Variable("angle","decimal","-360 360","none","1"));
        parameters[i]->addVariable(new Variable("scale","decimal","0 10","low","1"));
        ++i;

    //DPOSITION
    parameters.push_back(new Parameter("dposition"));
        parameters[i]->addVariable(new Variable("dx","decimal","-2 2","none","1"));
        parameters[i]->addVariable(new Variable("dy","decimal","-2 2","none","1"));
        parameters[i]->addVariable(new Variable("dz","decimal","-2 2","none","1"));
        parameters[i]->addVariable(new Variable("dxorigin","integer","-1 1","none","1"));
        parameters[i]->addVariable(new Variable("dyorigin","integer","-1 1","none","1"));
        parameters[i]->addVariable(new Variable("dangle","decimal","-360 360","none","1"));
        parameters[i]->addVariable(new Variable("dscale","decimal","0 10","low","1"));
        ++i;

    //SIZE
    parameters.push_back(new Parameter("size"));
        parameters[i]->addVariable(new Variable("height","decimal","-2 2","none","1"));
        parameters[i]->addVariable(new Variable("width","decimal","-2 2","none","1"));
        ++i;

    //TRANSFORMATION
    parameters.push_back(new Parameter("transformation"));
        parameters[i]->addVariable(new Variable("rotatex","decimal","0 360","none","1"));
        parameters[i]->addVariable(new Variable("rotatey","decimal","0 360","none","1"));
        parameters[i]->addVariable(new Variable("rotatez","decimal","0 360","none","1"));
        ++i;

    //TIME
    parameters.push_back(new Parameter("time"));
        parameters[i]->addVariable(new Variable("date","decimal","0 100","low","1"));
        parameters[i]->addVariable(new Variable("duration","decimal","0 100","low","1"));
        ++i;

    //DTIME
    parameters.push_back(new Parameter("dtime"));
        parameters[i]->addVariable(new Variable("ddate","decimal","-100 100","none","1"));
        parameters[i]->addVariable(new Variable("dduration","decimal","-100 100","none","1"));
        ++i;

    //SIGNAL
    parameters.push_back(new Parameter("signal"));
        parameters[i]->addVariable(new Variable("y","decimal","-1 1","both","1"));
        parameters[i]->addVariable(new Variable("t","decimal","-1 1","none","1"));
        parameters[i]->addVariable(new Variable("h","decimal","-1 1","none","1"));
        parameters[i]->addVariable(new Variable("s","decimal","-1 1","none","1"));
        parameters[i]->addVariable(new Variable("b","decimal","-1 1","none","1"));
        parameters[i]->addVariable(new Variable("a","decimal","-1 1","none","1"));

}

XmlData::~XmlData()
{

}

void XmlData::readFile(QString _file)
{
    QFile doc_xml(_file);
    if(!doc_xml.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this,"Erreur","Impossible d'ouvrir le ficher XML");
        doc_xml.close();
        return;
    }
    domDoc = new QDomDocument;
    if(!domDoc->setContent(&doc_xml))
    {
        QMessageBox::critical(this,"Erreur","Impossible de charger le ficher XML");
        doc_xml.close();
        return;
    }
    doc_xml.close();
}

void XmlData::writeFile(QString _fileName)
{
    QFile fichier(_fileName);
    if(!fichier.open(QIODevice::WriteOnly))
    {
        fichier.close();
        QMessageBox::critical(this,"Erreur","Impossible d'écrire dans le document XML");
        return;
    }
    QTextStream stream(&fichier);
    stream << domDoc->toString();
    fichier.close();
    delete domDoc;
}

void XmlData::generateOSCTree(map<int, INScoreObject *> *_objectList)
{
    domDoc = new QDomDocument();
    /* Init of the XML file : header, roots node */
    domDoc->appendChild(domDoc->createComment("This file describe the i-score's OSC tree to communicate with INScore"));
    domDoc->appendChild(domDoc->createTextNode("\n"));

    QDomNode versionNode = domDoc->createProcessingInstruction("xml", "version=\"1.0\" encoding=\"ISO-8859-1\" standalone=\"yes\"");
    domDoc->insertBefore(versionNode,domDoc->firstChild());
    QDomElement rootElement = domDoc->createElement("jamoma");
//        rootElement.setAttribute("version","O.6");
//        rootElement.setAttribute("xmlns:xsi","http://www.w3.org/2001/XMLSchema-instance");
//        rootElement.setAttribute("xsi:schemaLocation","http://jamoma.org/ file:jamoma.xsd");
    QDomElement appli = domDoc->createElement("application");
//        appli.setAttribute("author","OSSIA");
//        appli.setAttribute("version","0.0.0");
//        appli.setAttribute("name","INScore");
//        appli.setAttribute("type","proxy");

    QDomElement sceneElement;
    QDomElement objectElement;
    QDomElement paramElement;
    QDomElement variableElement;

    map<int, INScoreObject *>::iterator pairIt = _objectList->begin();
    string currentScene = (pairIt->second)->getScene();

        appli.appendChild(domDoc->createComment("scene"));
        sceneElement = domDoc->createElement(currentScene.c_str());
        sceneElement.setAttribute("object","Container");
        sceneElement.setAttribute("service","model");
        sceneElement.setAttribute("priority","0");
        sceneElement.setAttribute("tag","scene");

    /* User Nodes */
    while(pairIt != _objectList->end()) // <check each object
    {
        INScoreObject * it(pairIt->second);
        if((it)->getScene().compare(currentScene) != 0)
        {
            appli.appendChild(sceneElement);
            appli.appendChild(domDoc->createComment("scene"));
            currentScene = (it)->getScene();
            sceneElement.clear();
            sceneElement = newContainerElement(currentScene, "INScore Scene");
        }

        sceneElement.appendChild(domDoc->createComment((it)->getPath().c_str()));
        objectElement = newContainerElement((it)->getName(), "INScore Object");
        objectElement.setAttribute("tag",(it)->getPath().c_str());
        int i = 0;
        while(i<getNbParameters()) // look the state of each parameter
        {
            string currentParamName = parameters[i]->getParameterName();
            if((it)->isParameterChecked(currentParamName.c_str())) //if it's check
            {
                objectElement.appendChild(domDoc->createComment(currentParamName.c_str()));
                paramElement = newContainerElement(parameters[i]->getParameterName(), "INScore Parameter");

                int j=0;
                while(j<parameters[i]->getNbVariable()) // variables
                {
                    QString elementName(parameters[i]->getVariable(j).getVariableName().c_str());
                    variableElement = domDoc->createElement(elementName);
                    int k=0;
                    while(k<parameters[i]->getVariable(j).nbAttribute()) // attributes
                    {
                        QString name(parameters[i]->getVariable(j).getAttributeName(k).c_str());
                        QString value(parameters[i]->getVariable(j).getAttributeValue(k).c_str());
                        variableElement.setAttribute(name, value);
                        k++;
                    }
                    paramElement.appendChild(variableElement);
                    j++;
                }
                if(i==0) { // the "show" variable is in the same level than a parameter.
                    objectElement.appendChild(variableElement);
                }
                else {
                    objectElement.appendChild(paramElement);
                }
            }
            i++;
        }
        sceneElement.appendChild(objectElement);
        objectElement.clear();
        pairIt++;
    }
    appli.appendChild(sceneElement);
    rootElement.appendChild(appli);
    domDoc->appendChild(rootElement);
}

void XmlData::generateSaveFile(map<int, INScoreObject *> *_objectList)
{
    domDoc = new QDomDocument;

    domDoc->appendChild(domDoc->createComment("This file saves datas for iscore-INScoreCT"));
    domDoc->appendChild(domDoc->createTextNode("\n"));

    QDomElement ITL = domDoc->createElement("ITL");

    QDomElement sceneElement;
    QDomElement objectElement;
    QDomElement initElement;
    QDomElement paramElement;
    QDomElement setElement;

    map<int, INScoreObject *>::iterator it = _objectList->begin();
    while(it != _objectList->end()) {
        QString sceneName(it->second->getScene().c_str());
        sceneElement = ITL.firstChildElement(sceneName);

        if(sceneElement.isNull()) {
            sceneElement = domDoc->createElement(it->second->getScene().c_str());
        }

        objectElement = domDoc->createElement(it->second->getName().c_str());
        objectElement.setAttribute("path", it->second->getPath().c_str());
        objectElement.setAttribute("create", it->second->getToCreate());

        if(it->second->getToCreate() == 1) {

            setElement = domDoc->createElement("set");
                setElement.setAttribute("type", it->second->getType().c_str());
                setElement.setAttribute("creationValue", it->second->getCreationValue().c_str());

            initElement = domDoc->createElement("init");
            map<string, float> buffer = it->second->getInitValues();
            map<string, float>::iterator valueIt = buffer.begin();
            while(valueIt != buffer.end()) {
                initElement.setAttribute(valueIt->first.c_str(), valueIt->second);
                ++valueIt;
            }
            objectElement.appendChild(setElement);
            objectElement.appendChild(initElement);
        }
        paramElement = domDoc->createElement("parameters");
        int i(0);
        while(i<it->second->nbParameters()) {
            paramElement.setAttribute(it->second->getParameterName(i).c_str(), it->second->isParameterChecked(i));
            ++i;
        }

        objectElement.appendChild(paramElement);
        sceneElement.appendChild(objectElement);
        ITL.appendChild(sceneElement);
        ++it;
    }
    domDoc->appendChild(ITL);

}

void XmlData::xmlToInscoreObject()
{
    inscoreObjectList.clear();
    int i(0);
    QDomElement doc = domDoc->documentElement();
    QDomElement scene = doc.firstChild().toElement();
    QDomElement parameter;

    while(!scene.isNull()) {
        QDomElement object = scene.firstChild().toElement();
        while(!object.isNull()) {
            inscoreObjectList[i] = new INScoreObject(object.tagName().toStdString(), scene.tagName().toStdString());
            inscoreObjectList[i]->setPath(object.attribute("path").toStdString());

            if(object.attribute("create").toStdString().compare("1") == 0) {
                inscoreObjectList[i]->setToCreate(true);
                parameter = object.firstChildElement("set");
                if(! parameter.isNull()) {
                    inscoreObjectList[i]->setType(parameter.attribute("type").toStdString());
                    inscoreObjectList[i]->setCreationValue(parameter.attribute("creationValue").toStdString());
                }

                parameter = object.firstChildElement("init");
                if(! parameter.isNull()) {

                    map<string, float> buffer = inscoreObjectList[i]->getInitValues();
                    map<string, float>::iterator it = buffer.begin();
                    while(it!= buffer.end()) {
                        inscoreObjectList[i]->setInitValue(it->first,parameter.attribute(it->first.c_str(), "0").toFloat());
                        ++it;
                    }
                }
            }

            parameter = object.firstChildElement("parameters");
            int j(0);
            while(j<inscoreObjectList[i]->nbParameters()) {
                string paramName = inscoreObjectList[i]->getParameterName(j);
                inscoreObjectList[i]->setParameter(paramName, parameter.attribute(paramName.c_str(), "0").toInt());
                ++j;
            }

            object = object.nextSibling().toElement();
            ++i;
        }
        scene = scene.nextSibling().toElement();
    }
}

INScoreObject *XmlData::getObject(int index)
{
    return inscoreObjectList[index];
}

QDomElement XmlData::newContainerElement(string _name, string _tag)
{
    QDomElement newElement;
    newElement = domDoc->createElement(_name.c_str());
    newElement.setAttribute("object","Container");
    newElement.setAttribute("service","model");
    newElement.setAttribute("priority","0");
    newElement.setAttribute("tag",_tag.c_str());

    return newElement;
}

int XmlData::getNbParameters()
{
    return int(parameters.size());
}

Parameter *XmlData::getParameter(int _i)
{
    return parameters[_i];
}

int XmlData::nbInscoreObject()
{
    return int(inscoreObjectList.size());
}
