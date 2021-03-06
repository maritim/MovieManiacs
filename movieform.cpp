#include "movie.h"
#include "movieform.h"
#include "ui_movieform.h"

movieform::movieform(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::movieform)
{
    ui->setupUi(this);
}

movieform::~movieform()
{
    delete ui;
}

void movieform::setMovie(const movie &mov)
{
    this->mov = mov;

    getReady();
}

void movieform::getReady(void)
{
    this->setWindowTitle(this->mov.getName() + " Details");

    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->setFocus();

    ui->label->setText(mov.getName());
    ui->yearInfoLabel->setText(QString::number(mov.getYear()));

    ui->userRatingInfoLabel->setText(mov.getUserRating());
    ui->dateInfoLabel->setText(QString::number(mov.getUserDate().date().day())
                         + "." + QString::number(mov.getUserDate().date().month()) + "." +
                         QString::number(mov.getUserDate().date().year()));

    if(mov.getName() != mov.getOriginalName())
    {
        ui->originalNameInfoLabel->setText(mov.getOriginalName());
        ui->originalNameInfoLabel->setWordWrap(true);
    }
    else
    {
        ui->originalNameInfoLabel->deleteLater();
        ui->originalNameTextLabel->deleteLater();
    }

    ui->runtimeInfoLabel->setText(mov.getRuntime());
    ui->ratingInfoLabel->setText(mov.getRating());

    if(mov.genreCount() >= 1)
    {
        ui->genresInfoLabel->setText(mov.genreAt(0));
        if(mov.genreCount() == 1)
            ui->genresTextLabel->setText("Genre:");
        for(int i=1;i<mov.genreCount();i++)
            ui->genresInfoLabel->setText(ui->genresInfoLabel->text() + " | \n" + mov.genreAt(i));
    }

    if(mov.directorsCount() >= 1)
    {
        ui->directorsInfoLabel->setText(mov.directorAt(0));
        if(mov.directorsCount() == 1)
            ui->directorsTextLabel->setText("Director:");
        for(int i=1;i<mov.directorsCount();i++)
            ui->directorsInfoLabel->setText(ui->directorsInfoLabel->text() + " | \n" + mov.directorAt(i));
    }

    ui->posterLabel->setText("<img width=180 heigth=268 src='" + mov.getPosterPath() + "' />");

    ui->reviewTextBrowser->setText(mov.getUserReview());

    if(mov.getSynopsis().isEmpty() == false)
        ui->synopsisTextBrowser->setText(mov.getSynopsis());
    else
        ui->synopsisGroupBox->setVisible(false);

    loadCastTableWidget(mov);
}

void movieform::loadCastTableWidget(const movie& mov)
{
    ui->castTableWidget->setColumnWidth(0,172);

    for(int i=0;i<mov.actorCount();i++)
    {
        ui->castTableWidget->insertRow(i);
        ui->castTableWidget->setItem(i,0,new QTableWidgetItem(mov.actorAt(i).getName()));
        ui->castTableWidget->setItem(i,1,new QTableWidgetItem(mov.actorAt(i).getRole()));
    }
}

void movieform::on_buttonBox_accepted()
{
    this->close();
}
