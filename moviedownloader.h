#ifndef MOVIEDOWNLOADER_H
#define MOVIEDOWNLOADER_H

#include "movie.h"

#include <QObject>

class movieDownloader : public QObject
{
    Q_OBJECT
    QString ID;
    movie mov;

public:
    explicit movieDownloader(QObject *parent = 0,QString ID = "");
    void run();

signals:
    void finished();
    void finished(movie);
    
public slots:
    void getMovie(QString);
};

#endif // MOVIEDOWNLOADER_H
