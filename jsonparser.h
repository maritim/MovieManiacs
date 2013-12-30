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

public:
    explicit jSonParser(QObject *parent = 0, QString jSonString = "");
    bool jSonValidityChecker(void);
    std::map<QString,QString> jSonParsed(void);
    std::vector<QString> jSonVectorOfSetsParsed(void);
    std::vector<QString> jSonVectorOfElementsParsed(void);

    void setString(QString);
};

#endif // JSONPARSER_H
