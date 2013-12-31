#include "moviedownloader.h"
#include "networkclass.h"
#include "movie.h"
#include "jsonparser.h"
#include "actor.h"

#include <QtCore>
#include <QImageWriter>

movieDownloader::movieDownloader(QObject *parent, QString ID) :
    QObject(parent)
{
    this->ID = ID;
}

movieDownloader::movieDownloader(const QString& ID)
{
    this->ID = ID;
    mov = new movie();
    mov->setrtid(ID);
}

void movieDownloader::run(void) {

    QString urlString = "http://api.rottentomatoes.com/api/public/v1.0/movies/" + ID + ".json?apikey=haak3yvy8dsw4gfxu8vprvnv";

    try {
        networkclass *net = new networkclass();
        QObject::connect(net, SIGNAL(finished(QString)), this, SLOT(getMovie(QString)));
        net->getSourceCode(urlString);
    }
    catch(...) {
        qDebug() << "Eroare!";
        return ;
    }

    emit progress(10);
}

void movieDownloader::getMovie(QString jSonString) {

    QString posterUrl = "";

    emit progress(20);

    try {
        jSonParser jSon;
        jSon.setString(jSonString);

        std::map<QString,QString> jSonResult = jSon.jSonParsed();

        mov->setOriginalName(jSonResult["title"]);
        mov->setYear(jSonResult["year"].toInt());
        mov->setRuntime(jSonResult["runtime"]);
        qDebug() << mov->getRuntime();
        mov->setSynopsis(jSonResult["synopsis"]);

        jSon.setString(jSonResult["genres"]);

        std::vector<QString> jSonCastResult = jSon.jSonVectorOfElementsParsed();

        for(int i=0;i<jSonCastResult.size();i++) {
            mov->addGenre(jSonCastResult[i]);
        }

        jSon.setString(jSonResult["posters"]);
        posterUrl = jSon.jSonParsed()["detailed"];

        emit progress(40);

        jSon.setString(jSonResult["abridged_cast"]);
        std::vector<QString> jSonVectorResult = jSon.jSonVectorOfSetsParsed();

        qDebug() << jSonVectorResult.size();

        actor actr;
        std::vector<QString> jSonVectorRoleResult;

        for(int i=0;i<jSonVectorResult.size();i++) {

            jSon.setString(jSonVectorResult[i]);

            jSonResult = jSon.jSonParsed();

            actr.setName(jSonResult["name"]);

            jSon.setString(jSonResult["characters"]);
            jSonVectorRoleResult = jSon.jSonVectorOfElementsParsed();

            actr.setRole(jSonVectorRoleResult[0]);
            mov->addActor(actr);
        }
    }
    catch(...) {
        qDebug() << "Eroare 2";
        return ;
    }

    emit progress(50);

    networkclass *net = new networkclass();
    QObject::connect(net, SIGNAL(finished(QImage)), this, SLOT(getPoster(QImage)));
    net->getInternetImage(posterUrl);
}

void movieDownloader::getPoster(QImage image)
{
    emit progress(90);

    mov->setPosterPath("images/" + ID + ".jpg");

    QImageWriter writer(mov->getPosterPath());
    if(!writer.write(image)) {
        qDebug() << "Eroare";
    }

    emit finished(mov);
    emit finished();
}
