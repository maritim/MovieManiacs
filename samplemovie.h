#ifndef SAMPLEMOVIE_H
#define SAMPLEMOVIE_H

#include "movie.h"

#include<QtCore>
#include<QImage>

class samplemovie : public movie
{
private:
    QImage moviePoster;

public:
    samplemovie();
    samplemovie(QString);
    //samplemovie(const samplemovie&);
    QImage getMoviePoster(void) const;
    void setMoviePoster(QImage);
};

#endif // SAMPLEMOVIE_H
