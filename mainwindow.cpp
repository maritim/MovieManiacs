#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "simpledialog.h"
#include "diskwriter.h"
#include "movieform.h"
#include "newmoviedialog.h"
#include "moviedownloader.h"
#include "movie.h"
#include "messagebox.h"

#include <QtXml>
#include <QMessageBox>
#include <QFileDialog>
#include <QProgressBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    try
    {
        collectionFile = "example.xml";
        loadMovieList(collectionFile);
        loadMovieListWidget(movieList);
        ui->movieListWidget->setCurrentItem(ui->movieListWidget->item(0));
    }
    catch(char *error)
    {
        QMessageBox::information(this,"Error",error);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_Window_triggered()
{
    NewMovieDialog dialog(this);

    if(dialog.exec())
    {
        movie mov = dialog.getMovie();
        movieList.push_back(mov);
        addMovieToListWidget(mov);
    }
}

void MainWindow::loadMovieList(QString filename)
{
    movieList.clear();

    QDomDocument document;

    QFile file(filename);

    //qDebug() << file.fileName();

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(this,"Error","Could not load " + filename);
        return ;
    }
    else
    {
        if(!document.setContent(&file))
        {
            //QPixmap pixmap();
            //pixmap.load(":/images/film_error.png");

            MessageBox::ErrorMessageBox("Error","Could not load \"" + filename + "\" !");
/*            QMessageBox *box = new QMessageBox();
            box->setIconPixmap(QPixmap(":/images/film_error.png"));
            box->setWindowTitle("Error");
            box->setText();
            box->setStandardButtons(QMessageBox::Ok);
            box->setDefaultButton(QMessageBox::Ok);
            box->setModal(true);
            box->show();
*/
            //QMessageBox::information(this,"Error","Could not load the xml!");
            return ;
        }
        file.close();
    }

    QDomElement root = document.firstChildElement();

    QDomNodeList movies = root.elementsByTagName("movie");
    for(int i=0;i<movies.count();i++)
    {
        QDomNode movienode = movies.at(i);

        if(movienode.isElement())
        {
            movie mov(movienode.toElement());

            movieList.push_back(mov);
        }
    }
}

void MainWindow::loadMovieListWidget(const QList<movie>& movieList)
{
    ui->movieListWidget->clear();
    ui->movieListWidget->setIconSize(QSize(50,40));

    for(int i=0;i<movieList.count();i++)
    {
        //QTableWidgetItem *widget = new QTableWidgetItem(movieList[i].getName());
        //ui->tableWidget->insertRow(i);
        //ui->tableWidget->setItem(i,1,widget);
        //ui->tableWidget->setItem(i,0,new QTableWidgetItem(QIcon("1373337397_movie_add.png"),""));
        //ui->tableWidget->setItem(i,1,new QTableWidgetItem(movieList[i].getXMLPath()));
//        QmovieListWidgetItem *item = new QmovieListWidgetItem(movieList[i].getName());
//        item->setSizeHint(QSize(200,64));
      //  QImage *image = new QImage("thegodfather.jpg");
//        QIcon icon(QPixmap(movieList[i].getPosterPath()));
        //if(icon->isNull())
        //    QMessageBox::information(this,"pl","pl");
        //QFile
//        item->setIcon(icon);

//        ui->movieListWidget->addItem(item);
        //QSize size = new QSize(100,100);
        //QIcon *icon = new QIcon("thegodfather.jpg");
        //ui->movieListWidget->item(i)->setIcon(QIcon("thegodfather.jpg"));

        addMovieToListWidget(movieList[i]);
    }
}

void MainWindow::addMovieToListWidget(const movie& mov)
{
    QListWidgetItem *item = new QListWidgetItem(mov.getName());
    item->setSizeHint(QSize(200,64));
    QIcon icon(QPixmap(mov.getPosterPath()));
    item->setIcon(icon);

    ui->movieListWidget->addItem(item);
}

int MainWindow::getIndexByName(const QString& movieName)
{
    for(int i=0;i<movieList.size();i++)
        if(movieList[i].getName() == movieName)
            return i;

    throw "Don't find any movie with name " + movieName + " !";
}

movie MainWindow::getMovieByName(const QString& movieName)
{
    foreach(movie mov,movieList)
        if(mov.getName() == movieName)
            return mov;

    throw "Don't find any movie with name " + movieName + " !";
}

void MainWindow::on_movieListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    movieform *movForm = new movieform(this);

    movForm->setMovie(getMovieByName(item->text()));

    movForm->show();
}

void MainWindow::on_actionToolbar_changed()
{
    if(ui->actionToolbar->isChecked())
        ui->mainToolBar->setVisible(true);
    else
        ui->mainToolBar->setVisible(false);
}

void MainWindow::on_actionThumbnails_changed()
{
    if(ui->actionThumbnails->isChecked())
    {
        ui->movieListWidget->setIconSize(QSize(50,40));
    }
    else
    {
        ui->movieListWidget->setIconSize(QSize(0,0));
    }
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionSave_Collection_triggered()
{
    diskwriter::XMLCollectionWriter(collectionFile,movieList);
}

void MainWindow::on_actionDelete_Movie_triggered()
{
    for(int i=0;i<ui->movieListWidget->count();i++)
        if(ui->movieListWidget->item(i)->isSelected())
        {
            for(int j=0;j<movieList.count();j++)
                if(ui->movieListWidget->item(i)->text() == movieList[j].getName())
                {
                    movieList.removeAt(j);
                    break ;
                }

            ui->movieListWidget->takeItem(i);
        }
}

void MainWindow::on_actionOpen_Collection_triggered()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("XML files (*.xml)"));

    if(dialog.exec())
    {
        collectionFile = dialog.selectedFiles()[0];
        loadMovieList(collectionFile);
        loadMovieListWidget(movieList);
    }
}

void MainWindow::on_actionNew_Collection_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("New collection"),"New Collection.xml",tr("XML files(*.xml)"));
    if(fileName != NULL) {
        movieList.clear();
        loadMovieListWidget(movieList);
        diskwriter::XMLCollectionWriter(fileName,movieList);
        collectionFile = fileName;
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save file as"),"New Collection.xml",tr("XML files (*.xml)"));

    if(fileName != NULL) {
        collectionFile = fileName;
        diskwriter::XMLCollectionWriter(collectionFile,movieList);
    }
}

void MainWindow::on_actionUpdate_Movie_triggered()
{
    //QProgressBar *progressBar = new QProgressBar(ui->statusBar);
    //progressBar->setMaximumSize(170,19);
    //ui->statusBar->addWidget(progressBar);

    QString selectedMovieName = ui->movieListWidget->selectedItems().at(0)->text();

    try {

        int selectedIndex = getIndexByName(selectedMovieName);

        if(getMovieByName(selectedMovieName).getrtid().size() == 0) {

            QMessageBox::information(this,"Error","Could not update " + selectedMovieName + " without specific ID");

            return ;
        }

        movieDownloader *movDownloader = new movieDownloader(movieList.at(selectedIndex).getrtid());

        QThread *thread = new QThread();
        movDownloader->moveToThread(thread);
        QObject::connect(movDownloader, SIGNAL(finished(movie*)), this, SLOT(updateMovie(movie*)));
        QObject::connect(thread, SIGNAL(started()), movDownloader, SLOT(run()), Qt::DirectConnection);
        QObject::connect(movDownloader, SIGNAL(finished()),thread, SLOT(quit()), Qt::DirectConnection);
        QObject::connect(movDownloader, SIGNAL(progress(QString)), this, SLOT(progressUpdate(QString)));

        thread->start();

        //ui->statusBar->showMessage("Downloading...");
    }
    catch(...) {
    }
}

void MainWindow::updateMovie(movie* mov)
{
    ui->statusBar->clearMessage();
    ui->statusBar->showMessage("Finished update: " + mov->getOriginalName());

    QIcon icon(QPixmap(mov->getPosterPath()));

    for(int i=0;i<movieList.size();i++)
        if(movieList.at(i).getrtid() == mov->getrtid()) {

            movieList[i].updateDBInformations(mov);

            ui->movieListWidget->item(i)->setIcon(icon);
        }
}

void MainWindow::progressUpdate(QString progressInformations)
{
    ui->statusBar->clearMessage();
    ui->statusBar->showMessage("Progress: " + progressInformations);
}

