#include "networkclass.h"

#include <QtCore>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMessageBox>
#include <QDebug>
#include <QImage>

networkclass::networkclass()
{
}

networkclass::~networkclass()
{
}

networkclass::networkclass(const networkclass&)
{
}

void networkclass::getSourceCode(QString urlString)
{
    QNetworkAccessManager *nam;
    nam = new QNetworkAccessManager(this);
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(finishedSlot(QNetworkReply*)));

    QUrl url(urlString);
    QNetworkReply* reply = nam->get(QNetworkRequest(url));
}

void networkclass::getInternetImage(QString urlString)
{
    try {
        QNetworkAccessManager *nam;
        nam = new QNetworkAccessManager(this);
        QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
                         this, SLOT(finishedImageSlot(QNetworkReply*)));

        QUrl url(urlString);
        nam->get(QNetworkRequest(url));
    }
    catch(...) {
        qDebug() << "Eroare";
    }
}

void networkclass::finishedSlot(QNetworkReply* reply)
{
    try {
        //qDebug() << "dsadsadas";
        // Reading attributes of the reply
        // e.g. the HTTP status code
        QVariant statusCodeV =
        reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        // Or the target URL if it was a redirect:
        QVariant redirectionTargetUrl =
        reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
        // see CS001432 on how to handle this

        // no error received?
        if (reply->error() == QNetworkReply::NoError)
        {
            // read data from QNetworkReply here

            // Example 1: Creating QImage from the reply
    //        QImageReader imageReader(reply);
    //        QImage pic = imageReader.read();

            // Example 2: Reading bytes form the reply
            //QByteArray bytes = reply->readAll();  // bytes
            qDebug() << "Waw";
            QByteArray rawData = reply->readAll();
            QString textData(rawData);
            //qDebug() << textData;
            emit finished(textData);
        }
        // Some http error received
    }
    catch(...) {
        qDebug() << "Eroare";
        // handle errors here
    }

    // We receive ownership of the reply object
    // and therefore need to handle deletion.
    //delete reply;
}

void networkclass::finishedImageSlot(QNetworkReply* reply)
{
    try {
        QVariant statusCodeV =
        reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        QVariant redirectionTargetUrl =
        reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray jpegData = reply->readAll();
            QImage pic;
            pic.loadFromData(jpegData);

            qDebug() << "dsadas";
            emit finished(pic);
        }
    }
    catch(...) {
        qDebug() << "Eroare";
    }
}

QString networkclass::takeSourceCode(void) const
{
    return sourceCode;
}
