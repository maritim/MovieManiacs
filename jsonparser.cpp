#include "jsonparser.h"

#include <QtCore>
#include <map>
#include <vector>
#include <stack>

jSonParser::jSonParser(QObject *parent, QString jSonString) :
    QObject(parent)
{
    this->jSonString = jSonString;
}

bool jSonParser::jSonValidityChecker(void) {
    std::stack<char> Stack;

    return true;
}

QString jSonParser::trimQuoteMarks(const QString& string) {

    int i,j;
    QString resString;

    for(i=0;string[i] == '"';i++);
    for(j=string.size()-1;string[j] == '"';j--);

    for(;i<=j;++i)
        resString += string[i];

    return resString.trimmed();
}

QString jSonParser::getSpecName(void) {

    QString name;

    for(;jSonString[pos] != '"';++pos);
    for(++ pos; jSonString[pos] != '"'; ++pos) {
        name += jSonString[pos];
    }

    return trimQuoteMarks(name);
}

QString jSonParser::getArgument(void) {

    QString argument,helper = ",}]\"";
    std::stack<QChar> Stack;
    QChar chaux;

    for(;jSonString[pos] != ':';++pos);

    if(jSonString[pos+1] == '"') {
        Stack.push('"');
        ++ pos;
    }

    for(++pos; ;++pos) {

        chaux = jSonString.at(pos);
        if(helper.indexOf(chaux) != -1 && Stack.empty()) {
            ++ pos;

            return trimQuoteMarks(argument);
        }

        if(chaux == '"' && Stack.top() == '"')
            Stack.pop();
        else if(chaux == '"')
            Stack.push('"');

        if(chaux == '{' || chaux == '[')
            Stack.push(chaux);
        else if(chaux == '}' && Stack.top() == '{')
            Stack.pop();
        else if(chaux == ']' && Stack.top() == '[')
            Stack.pop();

        argument += chaux;
    }
}

std::map<QString,QString> jSonParser::jSonParsed(void) {

    std::map<QString,QString> jSon;
    QString name,arg;

    for(pos=1;pos<jSonString.size()-1;) {
        //qDebug() << "plm" << pos ;
        name = getSpecName();
        arg = getArgument();

        //qDebug() << name;
        //qDebug() << arg;

        jSon[name] = arg;
    }

    return jSon;
}

QString jSonParser::getSet(void) {

    std::stack<QChar> Stack;
    QString result;

    for(;jSonString[pos] != '{';++pos);
    for(; ;++pos) {

        if(jSonString[pos] == '}' && Stack.top() == '{')
            Stack.pop();
        else if(jSonString[pos] == '{')
            Stack.push('{');

        result += jSonString[pos];

        if(Stack.empty()) {
            ++ pos ;

            return trimQuoteMarks(result);
        }
    }

    return "";
}

std::vector<QString> jSonParser::jSonVectorOfSetsParsed(void) {
    std::vector<QString> jSon;

    for(pos=1;pos<jSonString.size()-1;) {

        jSon.push_back(getSet());
    }

    return jSon;
}

QString jSonParser::getSetArgument(void) {

    QString result,helper = ",]";

    for(;jSonString[pos] == ',';++pos);
    for(;helper.indexOf(jSonString[pos]) == -1;++pos) {
        result += jSonString[pos];
    }

    return result.trimmed();
}

std::vector<QString> jSonParser::jSonVectorOfElementsParsed(void) {

    std::vector<QString> jSon;

    for(pos=1;pos < jSonString.size()-1;) {
        jSon.push_back(getSetArgument());
    }

    return jSon;
}

void jSonParser::setString(QString jSonString) {
    this->jSonString = jSonString;
}
