#include "newmoviedialog.h"
#include "ui_newmoviedialog.h"

#include "movie.h"
#include "idget.h"

#define ID_BUTTON_TEXT "Get ID"
#define ID_BUTTON_TOOL_TIP "Get Movie Specific ID from Rotten Tomatoes"
#define DEFAULT_MOVIE_NAME "Empty Name"

NewMovieDialog::NewMovieDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewMovieDialog) {

    ui->setupUi(this);
    initialise();
}

NewMovieDialog::~NewMovieDialog() {

    delete ui;
}

//This initialise some Widgets from the
//NewMovie Dialog Form Interface

void NewMovieDialog::initialise(void) {

    ui->ratingSpinBox->setRange(1,100);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->toolButton->setText(ID_BUTTON_TEXT);
    ui->toolButton->setToolTip(ID_BUTTON_TOOL_TIP);
}

//If the button 'Ok' was pressed, the informations
//are associtated to actual movie (newMovie)
//This member is kept private and his informations
//are thrown whenever someone ask them

void NewMovieDialog::on_buttonBox_accepted() {

    if(ui->nameEdit->text().isEmpty())
        ui->nameEdit->setText(DEFAULT_MOVIE_NAME);

    newMovie.setName(ui->nameEdit->text());
    newMovie.setUserReview(ui->reviewPlainTextEdit->toPlainText());
    newMovie.setUserDate((QDateTime)ui->dateEdit->date());
    newMovie.setrtid(ui->movieIDEdit->text());
    newMovie.setUserRating(ui->ratingSpinBox->text());

    this->close();
}

//This method get a movie as a attribute and set
//his informations (name, rating, date, Rotten
//Tomatoes ID, review) on the Form

void NewMovieDialog::setMovie(const movie& mov) {

    this->newMovie = mov;

    ui->nameEdit->setText(mov.getName());
    ui->reviewPlainTextEdit->setPlainText(mov.getUserReview());
    ui->dateEdit->setDate(QDate(mov.getUserDate().date().year(),
        mov.getUserDate().date().month(),mov.getUserDate().date().day()));
    ui->movieIDEdit->setText(mov.getrtid());
    ui->ratingSpinBox->setValue(mov.getUserRating().toInt());
}

//This method return the movie who kept the
//informations from the Form

movie NewMovieDialog::getMovie(void) const {

    return newMovie;
}

//This create an IDGet Window Form to get the
//actual ID of the movie from the Rotten
//Tomatoes API

void NewMovieDialog::on_toolButton_clicked() {

    IDGet idGetWindow(this,ui->nameEdit->text());

    int x = idGetWindow.exec();
    qDebug() << x;

    if(x == QDialog::Accepted)
        ui->movieIDEdit->setText(idGetWindow.getMovieID());
}
