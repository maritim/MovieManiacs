#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QObject>
#include <map>
#include <vector>

class jSonParser : public QObject
{
    Q_OBJECT

    QString jSonString;
    int pos;

private:
    QString getSpecName(void);
    QString getArgument(void);
    QString getSetArgument(void);
    QString getSet(void);
    QString trimQuoteMarks(const QString &);
    QString getArrayArgument(void);

public:
    jSonParser(QString jSonString = 0);
    bool jSonValidityChecker(void);
    std::map<QString,QString> jSonSetParsed(void);
    std::vector<QString> jSonArrayParsed(void);

    void setString(QString);
};

#endif // JSONPARSER_H
