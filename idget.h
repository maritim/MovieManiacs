#ifndef IDGET_H
#define IDGET_H

#include <QDialog>
#include "networkclass.h"
#include "samplemovie.h"

namespace Ui {
class IDGet;
}

class IDGet : public QDialog
{
    Q_OBJECT

    networkclass *net;
    QString urlString;
    QList<samplemovie> smplMovieList;

private:
    void updateList(QString);

public:
    explicit IDGet(QWidget *parent = 0, QString searchParam = NULL);
    ~IDGet();
    
private:
    Ui::IDGet *ui;

private slots:
    void fillMoviesList(QString);
    void addMovieToListWidget(samplemovie);
    void on_pushButton_clicked();

    void on_buttonBox_accepted();

public:
    QString getMovieID();

};

#endif // IDGET_H
