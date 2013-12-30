#include "moviedownloader.h"
#include "networkclass.h"
#include "movie.h"
#include "jsonparser.h"
#include "actor.h"

movieDownloader::movieDownloader(QObject *parent, QString ID) :
    QObject(parent)
{
    this->ID = ID;
}

void movieDownloader::run(void) {

    QString urlString = "http://api.rottentomatoes.com/api/public/v1.0/movies/" + ID + ".json?apikey=haak3yvy8dsw4gfxu8vprvnv";

    networkclass *net = new networkclass();
    QObject::connect(net, SIGNAL(finished(QString)), this, SLOT(getMovie(QString)));
    net->getSourceCode(urlString);
}

void movieDownloader::getMovie(QString jSonString) {

    jSonParser jSon;
    jSon.setString(jSonString);

    std::map<QString,QString> jSonResult = jSon.jSonParsed();

    mov.setOriginalName(jSonResult["title"]);
    mov.setYear(jSonResult["year"].toInt());
    mov.setRuntime(jSonResult["runtime"]);
    mov.setSynopsis(jSonResult["synopsis"]);

    jSon.setString(jSonResult["genres"]);

    std::vector<QString> jSonCastResult = jSon.jSonVectorOfElementsParsed();

    for(int i=0;i<jSonCastResult.size();i++) {
        mov.addGenre(jSonCastResult[i]);
    }

    jSon.setString(jSonResult["abridged_cast"]);
    std::vector<QString> jSonVectorResult = jSon.jSonVectorOfSetsParsed();

    actor actr;

    for(int i=0;i<jSonVectorResult.size();i++) {

        jSon.setString(jSonVectorResult[i]);

        jSonResult = jSon.jSonParsed();

        actr.setName(jSonResult["name"]);

        jSon.setString(jSonResult["characters"]);
        jSonVectorResult = jSon.jSonVectorOfElementsParsed();

        actr.setRole(jSonVectorResult[0]);
        mov.addActor(actr);
    }

    emit finished(mov);
    emit finished();
}
