#include "idget.h"
#include "ui_idget.h"

#include "networkclass.h"
#include "samplemovie.h"
#include "partialmoviedownloader.h"
#include "jsonparser.h"
#include "messagebox.h"

#define PAGE_LIMIT 20

IDGet::IDGet(QWidget *parent, QString searchParam) :
    QDialog(parent),
    ui(new Ui::IDGet) {

    ui->setupUi(this);

    ui->movieList->setIconSize(QSize(50,40));
    ui->movieSearchText->setText(searchParam);

    updateList(searchParam);

    QObject::connect(ui->cancelButton, SIGNAL(clicked(bool)),\
                     this, SLOT(reject()));
}

IDGet::~IDGet() {
    delete ui;
}

//This method get the jSon string and parse every it
//movie by movie

void IDGet::fillMoviesList(QString jSon) {

    jSonParser jSonParse(jSon);
    std::map<QString,QString> result = jSonParse.jSonSetParsed();

    jSonParse.setString(result["movies"]);
    std::vector<QString> vresult = jSonParse.jSonArrayParsed();

    try {

        for(unsigned int i=0;i<vresult.size();i++) {

            partialMovieDownloader *threadChild = new partialMovieDownloader(vresult[i]);
            QThread *thread = new QThread();
            threadChild->moveToThread(thread);
            QObject::connect(threadChild, SIGNAL(finished(samplemovie)),\
                             this, SLOT(addMovieToListWidget(samplemovie)));
            QObject::connect(thread, SIGNAL(started()), threadChild,\
                             SLOT(run()), Qt::DirectConnection);
            QObject::connect(threadChild, SIGNAL(finished()),\
                             thread, SLOT(quit()), Qt::DirectConnection);

            thread->start();
        }
    }
    catch(...) {
        throw "An error occured while trying to get the movie list";
    }
}

//This method push the specified move (smplMovie) to List Widget

void IDGet::addMovieToListWidget(samplemovie smplMovie) {

    try {

        QListWidgetItem *item = new QListWidgetItem(smplMovie.getName());
        item->setSizeHint(QSize(200,64));
        QIcon icon(QPixmap::fromImage(smplMovie.getMoviePoster()));
        item->setIcon(icon);

        if(ui->movieList->count() == 0) {
            item->setSelected(true);
        }

        item->setToolTip(smplMovie.getrtid());

        ui->movieList->addItem(item);
    }
    catch(...) {
        throw "An error occured while trying to update the list";
    }
}

//This is the main method for List Widget Update

void IDGet::updateList(QString searchParam) {

    ui->movieList->clear();

    try {

        net = new networkclass;

        //This method do some voodoo (actually it's pretty weird)
        //Keeping thing simply, this method add the "samplemovie" data
        //type to a specified queue that keep values of this type
        //when are send (by multi threading) to the same method

        qRegisterMetaType<samplemovie>("samplemovie");

        //Here is created the movie's URL for Rotten Tomatoes API

        QObject::connect(net,SIGNAL(finished(QString)),this,\
                         SLOT(fillMoviesList(QString)));

        urlString = "http://api.rottentomatoes.com/api/public/v1.0/movies.json?";
        urlString += "apikey=haak3yvy8dsw4gfxu8vprvnv";
        urlString += "&q=" + searchParam.replace(" ","+");
        urlString += "&page_limit=" + QString::number(PAGE_LIMIT);

        net->getSourceCode(urlString);
    }
    catch (...) {
        throw "An error occured while trying to get the movie list";
    }
}

//The Slot (method) associated to Search Button click

void IDGet::on_pushButton_clicked() {
    updateList(ui->movieSearchText->text());
}

//Actually, here is some tricky part. The movie ID is kept
//as Tool Tip for List Widget Item. When a movie is selected
//and accepted as the wanted movie, his Tool Tip text is returned
//as the movie's Rotten Tomatoes ID. This is a good idea because in
//this way no more memory, for another list of IDs, will be kept.
//Even more, this is not a source for future bugs.

QString IDGet::getMovieID() {
    return ui->movieList->selectedItems().at(0)->toolTip();
}

//When the 'Ok' button is pressed, it is verified one more
//time if an actual movie is selected. If not, it will appear
//a question message box asking if the window will be closed
//without a selected movie

void IDGet::on_okButton_clicked() {

    const QString QUESTION_TITLE = "Are you sure you want to exit?";
    const QString QUESTION_TEXT = \
        "You don't select any movie. Are you sure you want to exit without an ID?";

    if(ui->movieList->selectedItems().isEmpty() == true) {

        if(MessageBox::QuestionMessageBox(QUESTION_TITLE,QUESTION_TEXT) \
              == QMessageBox::Yes)
                QDialog::reject();
        else
            return ;
    }
    else
        QDialog::accept();
}
