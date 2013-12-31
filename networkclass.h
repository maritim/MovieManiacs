#include <QtCore>
#include <QNetworkAccessManager>
#include <QImage>

#ifndef NETWORKCLASS_H
#define NETWORKCLASS_H

namespace Ui {
    class networkclass;
}

class networkclass : public QObject
{
    Q_OBJECT

private:
    QString sourceCode;

public:
    networkclass();
    ~networkclass();

public:
    void getSourceCode(QString urlString);
    QString takeSourceCode(void) const;
    void sourceCodeTaken(void) const;
    void setSourceCode(QString);
    void getInternetImage(QString);

signals:
    void finished(QString);
    void finished(QImage);

public slots:
    void finishedSlot(QNetworkReply *replay);
    void finishedImageSlot(QNetworkReply *replay);
};

#endif // NETWORKCLASS_H
