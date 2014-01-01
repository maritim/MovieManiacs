#include "jsonparser.h"

#include <QtCore>
#include <map>
#include <vector>
#include <stack>

//This is not a properly implemented jSon Parser!!!!!!!!!!!!!!!!!!!!
//This is a functional jSon Parser that work with a minimum of issues
//on the Rotten Tomatoes API

//For further documentations about jSon format this link is usefull:
//                      http://www.json.org/

//This parser have 2 main functions:

//1. SET PARSER
//The set parser takes a jSon SET text as a QString and return a
//std::map<QString,QString> associated with every object in that jSon SET
//2. ARRAY PARSER
//The array parser takes a jSon ARRAY text as a QString and return a
//std::vector<QString> associated with every element in that jSon ARRAY

//Unfortunately this implementation implied that the programmer MUST
//KNOW what type of jSon element is gonna to parse. In other words
//this is a minimalist jSon parser, but it's enough powerfull for what is need here

jSonParser::jSonParser(QString jSonString)
{
    this->jSonString = jSonString;
}

bool jSonParser::jSonValidityChecker(void) { //Not working yet
    std::stack<char> Stack;

    return true;
}

//This return the string without starting and ending quotes
QString jSonParser::trimQuoteMarks(const QString& string) {

    if(string[0] == '"' && string[string.size()-1] == '"')
        return string.mid(1,string.size()-2);

    return string;
}

//This method get the NAME of the object
QString jSonParser::getSpecName(void) {

    QString name;

    for(;jSonString[pos] != '"';++pos);
    for(++ pos; jSonString[pos] != '"'; ++pos) {
        name += jSonString[pos];
    }

    return trimQuoteMarks(name);
}

//This method get the ARGUMENT of the object
QString jSonParser::getArgument(void) {

    //Here it must be a finite automata, but nvm...

    QString argument = "",helper = ",}]\"";
    std::stack<QChar> Stack;
    QChar chaux;

    for(;jSonString[pos] != ':';++pos);

    if(jSonString[++pos] == '"') {
        Stack.push('"');
        argument += '"';
        ++ pos;
    }

    for(; ;++pos) {

        chaux = jSonString[pos];
        if(helper.indexOf(chaux) != -1 && Stack.empty()) {
            ++ pos;

            return trimQuoteMarks(argument);
        }

        if(chaux == '"' && Stack.top() == '"')
            Stack.pop();
        else if(chaux == '"')
            Stack.push('"');

        if(Stack.empty() == true || Stack.top() != '"') {

            if(chaux == '{' || chaux == '[')
                Stack.push(chaux);
            else if(chaux == '}' && Stack.top() == '{')
                Stack.pop();
            else if(chaux == ']' && Stack.top() == '[')
                Stack.pop();
        }

        argument += chaux;

        if(chaux == '\\')
            argument += jSonString[++pos];
    }

    throw "The jSon file is not properly formated!";
}

//This method return the parsed SET
std::map<QString,QString> jSonParser::jSonSetParsed(void) {

    std::map<QString,QString> jSon;
    QString name = "",arg = "";

    for(pos=1;pos<jSonString.size()-1;) {
        name = getSpecName();
        arg = getArgument();

        jSon[name] = arg;
    }

    return jSon;
}

//This method return the parsed ARRAY
std::vector<QString> jSonParser::jSonArrayParsed(void) {

    std::vector<QString> jSon;

    for(pos=1;pos<jSonString.size()-1;) {

        jSonString[--pos] = ':';
        jSon.push_back(getArgument());
    }

    return jSon;
}

//This method set the jSon text that will be parsed
void jSonParser::setString(QString jSonString) {
    this->jSonString = jSonString;
}
