#ifndef PARTIALMOVIEDOWNLOADER_H
#define PARTIALMOVIEDOWNLOADER_H

#include "samplemovie.h"
#include "networkclass.h"
#include "movie.h"

#include<QtCore>

class partialMovieDownloader: public QObject
{
    Q_OBJECT

private:
    samplemovie smplMovie;
    QString jSonString;

signals:
    void finished(samplemovie);
    void finished();

public:
    partialMovieDownloader(const QString&);

private slots:
    //void takeMovieDetails(movie*);
    void takeMoviePoster(QImage);
    void takeMovie(movie);
    void run();
};

#endif // PARTIALMOVIEDOWNLOADER_H
