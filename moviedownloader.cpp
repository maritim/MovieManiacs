#include "moviedownloader.h"

#include "networkclass.h"
#include "jsonparser.h"
#include "actor.h"
#include "movie.h"

#include <QtCore>
#include <QImageWriter>

movieDownloader::movieDownloader(QObject *parent, QString ID) :
    QObject(parent) {

    this->ID = ID;
}

movieDownloader::movieDownloader(const QString& ID) {

    //Constructor take and set the movie ID

    this->ID = ID;
    mov = new movie();
    mov->setrtid(ID);
}

void movieDownloader::run(void) {

    //URL String to the JSON String on Rotten Tomatoes API
    QString urlString = "http://api.rottentomatoes.com/api/public/v1.0/movies/" \
            + ID + ".json?apikey=haak3yvy8dsw4gfxu8vprvnv";

    try {
        networkclass *net = new networkclass();
        QObject::connect(net, SIGNAL(finished(QString)), this, SLOT(getMovie(QString)));
        net->getSourceCode(urlString);
    }
    catch(...) {
        throw "An error occured while trying to connect to Data Base!";
    }
}

void movieDownloader::getMovie(QString jSonString) {

    //Movie informations are in jSonString
    //jSonParser is used to scrape the infos

    QString posterUrl = "";
    int movieScore = 0;

    emit progress("Downloading completed...");

    try {

        jSonParser jSon(jSonString);

        std::map<QString,QString> jSonResult = jSon.jSonSetParsed();

        //Parsing general informations...

        mov->setOriginalName(jSonResult["title"]);
        mov->setYear(jSonResult["year"].toInt());
        mov->setRuntime(jSonResult["runtime"]);
        mov->setSynopsis(jSonResult["synopsis"]);

        //Rotten Tomatoes API reffer to movie numeric ratings as "score"
        //In "movie" class it is the same thing as "rating" member variable
        //The rating is rounded value of (critics_score+audience_score)/2
        jSon.setString(jSonResult["ratings"]);
        std::map<QString,QString> jSonScoreResult = jSon.jSonSetParsed();

        movieScore = (jSonScoreResult["critics_score"].toInt()+
                      jSonScoreResult["audience_score"].toInt());
        movieScore = (movieScore + 1) / 2;
        mov->setRating(QString::number(movieScore));

        //Parsing informations about Genres...

        jSon.setString(jSonResult["genres"]);

        std::vector<QString> jSonVectorResult = jSon.jSonArrayParsed();

        for(unsigned int i=0;i<jSonVectorResult.size();i++) {
            mov->addGenre(jSonVectorResult[i]);
        }

        jSon.setString(jSonResult["posters"]);
        posterUrl = jSon.jSonSetParsed()["detailed"];

        //Parsing informations about Directors...

        std::map<QString,QString> jSonDirectorResult;

        jSon.setString(jSonResult["abridged_directors"]);
        jSonVectorResult = jSon.jSonArrayParsed();

        for(unsigned int i=0;i<jSonVectorResult.size();i++) {

            jSon.setString(jSonVectorResult[i]);
            jSonDirectorResult = jSon.jSonSetParsed();

            mov->addDirector(jSonDirectorResult["name"]);
        }

        //Parsing informations about Cast...

        jSon.setString(jSonResult["abridged_cast"]);

        jSonVectorResult = jSon.jSonArrayParsed();
        actor actr;
        std::vector<QString> jSonVectorRoleResult;

        for(unsigned int i=0;i<jSonVectorResult.size();i++) {

            jSon.setString(jSonVectorResult[i]);

            jSonResult = jSon.jSonSetParsed();

            actr.setName(jSonResult["name"]);

            //The characters (role) section from cast could be missed
            //If so, no role is associated for the actor

            if(jSonResult["characters"] != NULL) {

                jSon.setString(jSonResult["characters"]);
                jSonVectorRoleResult = jSon.jSonArrayParsed();

                actr.setRole(jSonVectorRoleResult[0]);
            }

            mov->addActor(actr);
        }

    /*DEBUGGER TEST
        jSon.setString("[\"sadsa}}{,,,{dsa\",\"\\\"\",\"Romania\\\"[[]]]][[\"]");
        jSonVectorResult = jSon.jSonArrayParsed();
        for(int i=0;i<jSonVectorResult.size();i++)
            qDebug() << jSonVectorResult[i];*/
    }
    catch(...) {
        throw "An error occured while trying to parse the jSon file!";
    }

    emit progress("Parsing completed...");

    //Download the movie poster from Rotten Tomatoes site

    networkclass *net = new networkclass();
    QObject::connect(net, SIGNAL(finished(QImage)), this, SLOT(getPoster(QImage)));
    net->getInternetImage(posterUrl);
}


void movieDownloader::getPoster(QImage image) {

    //Movie poster is in the "image"
    //The poster path is "image/" + ID + .jpg extension
    //The image will be saved at this path
    //If a movie don't have an ID it will don't have a poster either

    emit progress("Downloading poster completed...");

    mov->setPosterPath(DEFAULT_POSTER_FOLDER + ID + DEFAULT_POSTER_TYPE);

    QImageWriter writer(mov->getPosterPath());
    if(!writer.write(image)) {
        throw "The poster \"" + mov->getPosterPath() + "\" could not be saved!";
    }

    //After all is finished 2 signals will be emited
    //(void) signal is for quiting the thread
    //(movie) signal will emit ahead the movie result

    emit finished(mov);
    emit finished();
}
