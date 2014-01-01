#include "movie.h"
#include "diskwriter.h"

#include <QtCore>

//DiskWriter class use Static methods for every bit written
//There is no need for an actual instance to write a movie
//in a XML file

diskwriter::diskwriter(QObject *parent) :
    QObject(parent)
{
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////XML Writer//////////////////////////////////
///////////////////////////////////////////////////////////////////////////

//Main method write a movie list into a big XML file
//In this way the whole collection will be kept togheter

//This method will call another methods to write blocks of
//information that are redundtant to be written by different
//pieces of code

void diskwriter::XMLCollectionWriter(QString fileName, const QList<movie>& movies)
{
    //This save almost every information about movie in "filename" file
    //as a XML file type

    //Set and open file "filename"
    QFile file(fileName);

    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        throw "An error occured while trying to open " + fileName;
    }

    //Open textstream associated with this file
    QTextStream fileStream(&file);

    //Write the stuff...
    fileStream << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n";
    fileStream << "<movies>\n";

    for(int i=0;i<movies.count();i++)
    {
        fileStream << "\t<movie name=\"" + movies[i].getName() + "\">\n";
        XMLUserInfosWriter(fileStream,movies[i]);
        //If the movie was updated from database
        //The real infos will be written, otherwise not
        if(movies[i].getrtid().isEmpty() == false)
            XMLRealInfosWriter(fileStream,movies[i]);
        fileStream << "\t</movie>\n";
    }

    fileStream << "</movies>";
}

//Informations inputed from the user are written from here...
void diskwriter::XMLUserInfosWriter(QTextStream& fileStream, const movie& mov)
{
    fileStream << "\t\t<user_infos>\n";
    fileStream << "\t\t\t<user_rating>" + mov.getUserRating() + "</user_rating>\n";
    fileStream << "\t\t\t<date day=\"" + QString::number(mov.getUserDate().date().day()) +
                  "\" month=\"" + QString::number(mov.getUserDate().date().month()) +
                  "\" year=\"" + QString::number(mov.getUserDate().date().year()) + "\"/>\n";
    fileStream << "\t\t\t<user_review>" + mov.getUserReview() + "</user_review>\n";
    fileStream << "\t\t</user_infos>\n";
}

//Informations from the Rotten Tomatoes (if exists) are written from here...
void diskwriter::XMLRealInfosWriter(QTextStream& fileStream, const movie& mov)
{
    fileStream << "\t\t<real_infos>\n";

    fileStream << "\t\t\t<name>" + mov.getOriginalName() + "</name>\n";
    fileStream << "\t\t\t<year>" + QString::number(mov.getYear()) + "</year>\n";
    fileStream << "\t\t\t<rtid>" + mov.getrtid() + "</rtid>\n";
    fileStream << "\t\t\t<rating>" + mov.getRating() + "</rating>\n";
    fileStream << "\t\t\t<poster>" + mov.getPosterPath() + "</poster>\n";
    fileStream << "\t\t\t<synopsis>" + mov.getSynopsis() + "</synopsis>\n";
    fileStream << "\t\t\t<runtime>" + mov.getRuntime() + "</runtime>\n";
    if(mov.directorsCount() > 0)
        XMLSetWriter(fileStream,"directors","director",mov.getDirectors());
    if(mov.genreCount() > 0)
        XMLSetWriter(fileStream,"genres","genre",mov.getGenres());
    XMLCastWriter(fileStream,mov);
    fileStream << "\t\t</real_infos>\n";
}

//Informations about movie Cast are written from here...
void diskwriter::XMLCastWriter(QTextStream& fileStream, const movie& mov)
{
    fileStream << "\t\t\t<cast>\n";
    for(int i=0;i<mov.actorCount();i++)
        fileStream << "\t\t\t\t<actor name=\"" + mov.actorAt(i).getName() + "\">" + mov.actorAt(i).getRole() + "</actor>\n";
    fileStream << "\t\t\t</cast>\n";
}

//This generic method write a set of informations (like genres, countries, directors)
//It could be used for sets that contains only Strings
//It need setName ("genres") and setElementsName ("genre") and
//QList<QString> (the set for the output)
void diskwriter::XMLSetWriter(QTextStream& fileStream, QString setName, QString setElementsName, const QList<QString>& set)
{
    fileStream << "\t\t\t<" + setName + ">\n";
    foreach(QString element,set) {
        fileStream << "\t\t\t\t<" + setElementsName + ">";
        fileStream << validateText(element);
        fileStream <<  + "</" + setElementsName + ">\n";
    }
    fileStream << "\t\t\t</" + setName + ">\n";
}

//There is a problem with XML Format as long as it have
//3 invalid characters: "&", "<", ">". First of them will
//appear quite often in "genres" so it need to be converted
//in "&amp;". This method do this
QString diskwriter::validateText(QString string)
{
    return string.replace("&","&amp;");
}
