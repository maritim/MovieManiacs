#ifndef MOVIEDOWNLOADER_H
#define MOVIEDOWNLOADER_H

#include "movie.h"

#include <QtCore>
#include <QObject>
#include <QImage>

class movieDownloader : public QObject
{
    Q_OBJECT
    QString ID;
    movie *mov;

public:
    explicit movieDownloader(QObject *parent = 0,QString ID = "");
    movieDownloader(const QString&);

signals:
    void finished();
    void finished(movie*);
    void progress(int);
    
public slots:
    void run();
    void getMovie(QString);
    void getPoster(QImage);
};

#endif // MOVIEDOWNLOADER_H
