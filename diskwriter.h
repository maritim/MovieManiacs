#ifndef DISKWRITER_H
#define DISKWRITER_H

#include "movie.h"

#include <QObject>


class diskwriter : public QObject
{
    Q_OBJECT

private:
    static QString validateText(QString);

public:
    explicit diskwriter(QObject *parent = 0);
    
    static void XMLCollectionWriter(QString,const QList<movie>&);
    static void XMLUserInfosWriter(QTextStream&,const movie&);
    static void XMLRealInfosWriter(QTextStream&,const movie&);
    static void XMLCastWriter(QTextStream&, const movie&);
    static void XMLSetWriter(QTextStream&, QString, QString,const QList<QString>&);

};

#endif // DISKWRITER_H
