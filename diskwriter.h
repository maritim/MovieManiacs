#ifndef DISKWRITER_H
#define DISKWRITER_H

#include "movie.h"

#include <QObject>


class diskwriter : public QObject
{
    Q_OBJECT
public:
    explicit diskwriter(QObject *parent = 0);
    
    static void XMLCollectionWriter(QString,const QList<movie>&);
    static void XMLUserInfosWriter(QTextStream&,const movie&);
    static void XMLRealInfosWriter(QTextStream&,const movie&);
    static void XMLCastWriter(QTextStream&, const movie&);

signals:
    
public slots:
    
};

#endif // DISKWRITER_H
