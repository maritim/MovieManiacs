#include "movie.h"
#include "diskwriter.h"

diskwriter::diskwriter(QObject *parent) :
    QObject(parent)
{
}

void diskwriter::XMLCollectionWriter(QString fileName, const QList<movie>& movies)
{
    QFile file(fileName);

    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        throw "An error occured while trying to open " + fileName;
    }

    QTextStream fileStream(&file);

    fileStream << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n";
    fileStream << "<movies>\n";

    for(int i=0;i<movies.count();i++)
    {
        fileStream << "\t<movie name=\"" + movies[i].getName() + "\">\n";
        XMLUserInfosWriter(fileStream,movies[i]);
        XMLRealInfosWriter(fileStream,movies[i]);
        fileStream << "\t</movie>\n";
    }

    fileStream << "</movies>";
}

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

void diskwriter::XMLRealInfosWriter(QTextStream& fileStream, const movie& mov)
{
    fileStream << "\t\t<real_infos>\n";

    fileStream << "\t\t\t<name>" + mov.getOriginalName() + "</name>\n";
    fileStream << "\t\t\t<year>" + QString::number(mov.getYear()) + "</year>\n";
    fileStream << "\t\t\t<rating>" + mov.getRating() + "</rating>\n";
    fileStream << "\t\t\t<poster>" + mov.getPosterPath() + "</poster>\n";
    fileStream << "\t\t\t<director>" + mov.getDirector() + "</director>\n";
    fileStream << "\t\t\t<synopsis>" + mov.getSynopsis() + "</synopsis>\n";
    fileStream << "\t\t\t<runtime>" + mov.getRuntime() + "</runtime>\n";
    XMLCastWriter(fileStream,mov);
    fileStream << "\t\t</real_infos>\n";
}

void diskwriter::XMLCastWriter(QTextStream& fileStream, const movie& mov)
{
    fileStream << "\t\t\t<cast>\n";
    for(int i=0;i<mov.actorCount();i++)
        fileStream << "\t\t\t\t<actor name=\"" + mov.actorAt(i).getName() + "\">" + mov.actorAt(i).getRole() + "</actor>\n";
    fileStream << "\t\t\t</cast>\n";
}
