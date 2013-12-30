#include <QtXml>

#include "movie.h"

movie::movie()
{
}

movie::movie(QDomElement movieelement)
{
    setName(movieelement.attribute("name"));

    QDomNode userinfos = movieelement.elementsByTagName("user_infos").at(0);

    if(userinfos.isElement())
        getUserInfosXML(userinfos.toElement());

    QDomNode realinfos = movieelement.elementsByTagName("real_infos").at(0);

    if(realinfos.isElement())
        getRealInfosXML(realinfos.toElement());
}

void movie::getUserInfosXML(QDomElement userinfos)
{
    QDomNode userReviewInfo = userinfos.elementsByTagName("user_review").at(0);
    setUserReview(userReviewInfo.toElement().text());

    QDomNode userMarkInfo = userinfos.elementsByTagName("user_rating").at(0);
    setUserRating(userMarkInfo.toElement().text());

    QDomNode userDateInfo = userinfos.elementsByTagName("date").at(0);
    QDateTime dateTime;
    QDate date;
    date.setDate(userDateInfo.toElement().attribute("year").toInt(),
                 userDateInfo.toElement().attribute("month").toInt(),
                 userDateInfo.toElement().attribute("day").toInt());
    dateTime.setDate(date);
    setUserDate(dateTime);
}

void movie::getRealInfosXML(QDomElement realinfos)
{
    QDomNode originalNameInfo = realinfos.elementsByTagName("name").at(0);
    setOriginalName(originalNameInfo.toElement().text());

    QDomNode ratingIngo = realinfos.elementsByTagName("rating").at(0);
    setRating(ratingIngo.toElement().text());

    QDomNode yearinfo = realinfos.elementsByTagName("year").at(0);
    setYear(yearinfo.toElement().text().toInt());

    QDomNode posterinfo = realinfos.elementsByTagName("poster").at(0);
    setPosterPath(posterinfo.toElement().text());

    QDomNode synopsisinfo = realinfos.elementsByTagName("synopsis").at(0);
    setSynopsis(synopsisinfo.toElement().text());

    QDomNode directorinfo = realinfos.elementsByTagName("director").at(0);
    //setDirector(directorinfo.toElement().text());

    //qDebug() << getDirector();

    QDomNode runtimeinfo = realinfos.elementsByTagName("runtime").at(0);
    setRuntime(runtimeinfo.toElement().text());

    QDomNode genreInfos = realinfos.elementsByTagName("genres").at(0);
    if(genreInfos.isElement())
        getGenresXML(genreInfos.toElement());

    QDomNode castinfo = realinfos.elementsByTagName("cast").at(0);
    if(castinfo.isElement())
        getCastXML(castinfo.toElement());
}

void movie::getGenresXML(QDomElement genreInfos)
{
    QDomNodeList genresinfo = genreInfos.elementsByTagName("genre");

    for(int i=0;i<genresinfo.count();i++)
    {
        QDomNode genreinfo = genresinfo.at(i);
        if(genreinfo.isElement())
        {
            addGenre(genreinfo.toElement().text());
            //qDebug() << genreinfo.toElement().text();
        }
    }
}

void movie::getCastXML(QDomElement castinfo)
{
    QDomNodeList castinginfo = castinfo.elementsByTagName("actor");

    for(int i=0;i<castinginfo.count();i++)
    {
        QDomNode actorinfo = castinginfo.at(i);
        if(actorinfo.isElement())
        {
            QString name = actorinfo.toElement().attribute("name");
            QString role = actorinfo.toElement().text();
            addActor(actor(name,role));

            //qDebug() << name + " " + role;
        }
    }
}

movie::~movie()
{
}

QString movie::getName() const {
    return this->name;
}

void movie::setName(const QString &name) {
    this->name = name;
}

int movie::getYear() const {
    return this->year;
}

void movie::setYear(int year) {
    this->year = year;
}

void movie::setPosterPath(const QString& posterPath) {
    this->posterPath = posterPath;
}

QString movie::getPosterPath(void) const {
    return this->posterPath;
}

void movie::setUserReview(const QString& userReview) {
    this->userReview = userReview;
}

QString movie::getUserReview(void) const {
    return userReview;
}

void movie::setUserRating(const QString& userRating) {
    this->userRating = userRating;
}

QString movie::getUserRating(void) const {
    return userRating;
}

void movie::setUserDate(const QDateTime& userDate) {
    this->userDate = userDate;
}

QDateTime movie::getUserDate(void) const {
    return userDate;
}

void movie::setOriginalName(const QString& originalName) {
    this->originalName = originalName;
}

QString movie::getOriginalName(void) const {
    return originalName;
}

void movie::setRating(const QString& rating) {
    this->rating = rating;
}

QString movie::getRating(void) const {
    return rating;
}

void movie::setDirector(const QString& director) {
    this->director = director;
}

QString movie::getDirector(void) const {
    return director;
}

void movie::setSynopsis(const QString& synopsis) {
    this->synopsis = synopsis;
}

QString movie::getSynopsis(void) const {
    return synopsis;
}

void movie::setRuntime(const QString& runtime) {
    this->runtime = runtime;
}

QString movie::getRuntime(void) const {
    return runtime;
}

void movie::addGenre(const QString& genre) {
    this->genres.push_back(genre);
}

int movie::genreCount(void) const {
    return genres.count();
}

QString movie::genreAt(const int& position) const {
    if(genres.count() <= position)
        throw "Genre list limits exceeded!";

    return genres[position];
}

void movie::removeGenre(const int& position) {
    if(genres.count() <= position)
        throw "Genre list limits esceeded!";

    genres.removeAt(position);
}

void movie::removeGenre(const QString& genre) {
    int position = 0;
    for(;position < genres.count();position ++)
        if(genres[position] == genre)
        {
            break ;
        }

    removeGenre(position);
}

void movie::addActor(const actor& act) {
    cast.push_back(act);
}

actor movie::actorAt(const int& position) const {
    if(cast.count() <= position)
        throw "Genre list limits exceeded!";

    return cast.at(position);
}

int movie::actorCount(void) const {
    return cast.count();
}

void movie::removeActor(const int& position) {
    if(cast.count() <= position)
        throw "Actor list limits exceeded!";

    cast.removeAt(position);
}

void movie::setrtid(const QString& rtid) {
    this->rtid = rtid;
}

QString movie::getrtid(void) const {
    return rtid;
}



