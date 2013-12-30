#include "idget.h"
#include "ui_idget.h"
#include "networkclass.h"
#include "samplemovie.h"
#include "partialmoviedownloader.h"
#include "jsonparser.h"

#define PAGELIMIT 20

IDGet::IDGet(QWidget *parent, QString searchParam) :
    QDialog(parent),
    ui(new Ui::IDGet)
{
    ui->setupUi(this);

    ui->movieList->setIconSize(QSize(50,40));

    ui->movieSearchText->setText(searchParam);

    updateList(searchParam);
}

IDGet::~IDGet()
{
    delete ui;
}

void IDGet::fillMoviesList(QString jSon)
{
    jSonParser jSonParse(this,jSon);
    std::map<QString,QString> result = jSonParse.jSonParsed();

    //qDebug() << result["movies"];

    jSonParse.setString(result["movies"]);
    std::vector<QString> vresult = jSonParse.jSonVectorOfSetsParsed();

    try {
        for(int i=0;i<vresult.size();i++)
        {
            //qDebug() << jSons.at(i);
            partialMovieDownloader *threadChild = new partialMovieDownloader(vresult[i]);
            QThread *thread = new QThread();
            threadChild->moveToThread(thread);
            QObject::connect(threadChild, SIGNAL(finished(samplemovie)), this, SLOT(addMovieToListWidget(samplemovie)));
            QObject::connect(thread, SIGNAL(started()), threadChild, SLOT(run()), Qt::DirectConnection);
            connect(threadChild, SIGNAL(finished()),thread, SLOT(quit()), Qt::DirectConnection);

            thread->start();
        }
    }
    catch(...) {
        qDebug() << "eroare :|";
    }
}

void IDGet::addMovieToListWidget(samplemovie smplMovie)
{
    try {
        QListWidgetItem *item = new QListWidgetItem(smplMovie.getName());
        item->setSizeHint(QSize(200,64));
        QIcon icon(QPixmap::fromImage(smplMovie.getMoviePoster()));
        item->setIcon(icon);

        if(ui->movieList->count() == 0) {
            item->setSelected(true);
        }

        //smplMovieList.push_back(smplMovie);
        item->setToolTip(smplMovie.getrtid());

        ui->movieList->addItem(item);
    }
    catch(...) {
        qDebug() << "Error";
    }
}

void IDGet::updateList(QString searchParam) {

    ui->movieList->clear();

    try {

        net = new networkclass;
        qRegisterMetaType<samplemovie>("samplemovie");
        QObject::connect(net,SIGNAL(finished(QString)),this,SLOT(fillMoviesList(QString)));

        urlString = "http://api.rottentomatoes.com/api/public/v1.0/movies.json?apikey=haak3yvy8dsw4gfxu8vprvnv";
        urlString += "&q=" + searchParam.replace(" ","+");
        urlString += "&page_limit=" + QString::number(PAGELIMIT);

        net->getSourceCode(urlString);
    }
    catch (...) {
        qDebug() << "Eroare";
    }
}

void IDGet::on_pushButton_clicked() {
    updateList(ui->movieSearchText->text());
}

QString IDGet::getMovieID() {
    return ui->movieList->selectedItems().at(0)->toolTip();
}

void IDGet::on_buttonBox_accepted()
{
    this->close();
}
