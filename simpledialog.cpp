#include "simpledialog.h"
#include "ui_simpledialog.h"
#include "networkclass.h"

simpleDialog::simpleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::simpleDialog)
{
    ui->setupUi(this);
}

simpleDialog::~simpleDialog()
{
    delete ui;
}

void simpleDialog::on_pushButton_clicked()
{
    QString urlString = ui->lineEdit->text();

    try
    {
        net = new networkclass;
        QObject::connect(net,SIGNAL(finished(QString)),this,SLOT(putSourceCode(QString)));
        net->getSourceCode(urlString);
        //ui->plainTextEdit->appendPlainText(net->takeSourceCode());
    }
    catch(...)
    {
        qDebug() << "eroare :|";
    }
}

void simpleDialog::putSourceCode(QString string)
{
    qDebug() << string;
    ui->plainTextEdit->appendPlainText(string);
}
