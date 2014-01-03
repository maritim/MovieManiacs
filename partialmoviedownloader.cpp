#include "partialmoviedownloader.h"

#include "samplemovie.h"
#include "networkclass.h"
#include "jsonparser.h"
#include "moviedownloader.h"
#include "movie.h"

#include<QtCore>

partialMovieDownloader::partialMovieDownloader(const QString &jSonString) {

    this->jSonString = jSonString;
}

void partialMovieDownloader::run() {

    jSonParser jSon(jSonString);

    std::map<QString,QString> jSonResult = jSon.jSonSetParsed();

    if(jSonResult["year"].isEmpty() == false)
        smplMovie.setName(jSonResult["title"] + " (" + jSonResult["year"] + ")");
    else
        smplMovie.setName(jSonResult["title"]);

    smplMovie.setrtid(jSonResult["id"]);

    networkclass *net = new networkclass();

    QObject::connect(net, SIGNAL(finished(QImage)),this, SLOT(takeMoviePoster(QImage)));

    jSon.setString(jSonResult["posters"]);
    jSonResult = jSon.jSonSetParsed();

    smplMovie.setPosterPath(jSonResult["original"]);

    net->getInternetImage(jSonResult["detailed"]);
}

void partialMovieDownloader::takeMoviePoster(QImage image) {

    smplMovie.setMoviePoster(image);

    emit finished(smplMovie);
    emit finished();
}

/*void partialMovieDownloader::takeMovie(movie mov) {

    smplMovie.setOriginalName(mov.getOriginalName());
    smplMovie.setYear(mov.getYear());

    networkclass *net = new networkclass();

    QObject::connect(net, SIGNAL(finished(QImage)), this, SLOT(takeMoviePoster(QImage)));

    net->getInternetImage(smplMovie.getPosterPath());
}*/
