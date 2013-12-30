#ifndef SIMPLEDIALOG_H
#define SIMPLEDIALOG_H

#include "networkclass.h"

#include <QDialog>
#include <QNetworkAccessManager>

namespace Ui {
class simpleDialog;
}

class simpleDialog : public QDialog
{
    Q_OBJECT

    networkclass *net;

public:
    explicit simpleDialog(QWidget *parent = 0);
    ~simpleDialog();
    
private slots:
    void on_pushButton_clicked();
    void putSourceCode(QString);

private:
    Ui::simpleDialog *ui;
};

#endif // SIMPLEDIALOG_H
