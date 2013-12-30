#include <QMessageBox>

#include "newmoviedialog.h"
#include "ui_newmoviedialog.h"
#include "movie.h"
#include "idget.h"

NewMovieDialog::NewMovieDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewMovieDialog)
{
    ui->setupUi(this);
    initialise();
}

NewMovieDialog::~NewMovieDialog()
{
    delete ui;
}

void NewMovieDialog::initialise(void)
{
    ui->spinBox->setRange(1,10);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->toolButton->setText("Get ID");
    ui->movieIDEdit->setReadOnly(true);
    ui->movieIDEdit->setEnabled(false);
}

void NewMovieDialog::on_buttonBox_accepted()
{
    if(ui->nameEdit->text().isEmpty())
        ui->nameEdit->setText("Empty Name");

    newMovie.setName(ui->nameEdit->text());
    newMovie.setUserReview(ui->reviewPlainTextEdit->toPlainText());
    newMovie.setUserDate((QDateTime)ui->dateEdit->date());
    newMovie.setrtid(ui->movieIDEdit->text());
}

movie NewMovieDialog::getMovie(void)
{
    return newMovie;
}

void NewMovieDialog::on_toolButton_clicked()
{
    IDGet idGetWindow(this,ui->nameEdit->text());

    if(idGetWindow.exec())
        ui->movieIDEdit->setText(idGetWindow.getMovieID());
}
