#include "samplemovie.h"
#include "partialmoviedownloader.h"
#include "networkclass.h"
#include "jsonparser.h"
#include "moviedownloader.h"
#include "movie.h"

#include<QtCore>

partialMovieDownloader::partialMovieDownloader(const QString &jSonString)
{
    this->jSonString = jSonString;
}

void partialMovieDownloader::run() {

    jSonParser jSon(this,jSonString);

    std::map<QString,QString> jSonResult = jSon.jSonParsed();

    smplMovie.setName(jSonResult["title"] + " (" + jSonResult["year"] + ")");
    smplMovie.setrtid(jSonResult["id"]);

    networkclass *net = new networkclass();

    QObject::connect(net, SIGNAL(finished(QImage)),this, SLOT(takeMoviePoster(QImage)));

    jSon.setString(jSonResult["posters"]);
    jSonResult = jSon.jSonParsed();

    smplMovie.setPosterPath(jSonResult["original"]);

    net->getInternetImage(jSonResult["detailed"]);

//    movieDownloader *mDownloader = new movieDownloader(this,smplMovie.getrtid());

//    QObject::connect()
}

void partialMovieDownloader::takeMoviePoster(QImage image)
{
    smplMovie.setMoviePoster(image);

    emit finished(smplMovie);
    emit finished();
}

void partialMovieDownloader::takeMovie(movie mov) {

    smplMovie.setOriginalName(mov.getOriginalName());
    smplMovie.setYear(mov.getYear());

    networkclass *net = new networkclass();

    QObject::connect(net, SIGNAL(finished(QImage)), this, SLOT(takeMoviePoster(QImage)));

    net->getInternetImage(smplMovie.getPosterPath());
}
