#include "actor.h"

#include <QtCore>
#include <QtXml>
\
#ifndef MOVIE_H
#define MOVIE_H

class movie
{
protected:
    QString name;
    QString userRating,userReview;
    QString posterPath;
    QString rtid;
    int year;
    QDateTime userDate;
    QString rating,originalName;
    QString director,synopsis,runtime;
    QList<QString> genres;
    QList<actor> cast;

public:
    movie();
    //movie(const movie&);
    movie(QDomElement);
    ~movie();

    void setName(const QString&);
    QString getName(void) const;

    void setYear(int);
    int getYear(void) const;

    void setPosterPath(const QString&);
    QString getPosterPath(void) const;

    void setUserReview(const QString&);
    QString getUserReview(void) const;

    void setUserRating(const QString&);
    QString getUserRating(void) const;

    void setUserDate(const QDateTime&);
    QDateTime getUserDate(void) const;

    void setRating(const QString&);
    QString getRating(void) const;

    void setOriginalName(const QString&);
    QString getOriginalName(void) const;

    void setDirector(const QString&);
    QString getDirector(void) const;

    void setRuntime(const QString&);
    QString getRuntime(void) const;

    void setSynopsis(const QString&);
    QString getSynopsis(void) const;

    void setrtid(const QString&);
    QString getrtid(void) const;

    void addGenre(const QString&);
    QString genreAt(const int&) const;
    int genreCount(void) const;
    void removeGenre(const int&);
    void removeGenre(const QString&);

    void addActor(const actor&);
    actor actorAt(const int&) const;
    int actorCount(void) const;
    void removeActor(const int&);

    void getUserInfosXML(QDomElement);
    void getRealInfosXML(QDomElement);
    void getGenresXML(QDomElement);
    void getCastXML(QDomElement);

    //movie operator=(const movie&);
};

#endif // MOVIE_H
