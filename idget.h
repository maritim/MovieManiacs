#ifndef IDGET_H
#define IDGET_H

#include "networkclass.h"
#include "samplemovie.h"

#include <QDialog>

namespace Ui {
class IDGet;
}

class IDGet : public QDialog
{
    Q_OBJECT

    networkclass *net;
    QString urlString;

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
    void on_okButton_clicked();

public:
    QString getMovieID();

};

#endif // IDGET_H
