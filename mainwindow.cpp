#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "simpledialog.h"
#include "diskwriter.h"
#include "movieform.h"
#include "newmoviedialog.h"

#include <QtXml>
#include <QMessageBox>
#include <QFileDialog>

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
        ui->listWidget->setCurrentItem(ui->listWidget->item(0));
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
            QMessageBox::information(this,"Error","Could not load the xml!");
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
    ui->listWidget->clear();
    ui->listWidget->setIconSize(QSize(50,40));

    for(int i=0;i<movieList.count();i++)
    {
        //QTableWidgetItem *widget = new QTableWidgetItem(movieList[i].getName());
        //ui->tableWidget->insertRow(i);
        //ui->tableWidget->setItem(i,1,widget);
        //ui->tableWidget->setItem(i,0,new QTableWidgetItem(QIcon("1373337397_movie_add.png"),""));
        //ui->tableWidget->setItem(i,1,new QTableWidgetItem(movieList[i].getXMLPath()));
//        QListWidgetItem *item = new QListWidgetItem(movieList[i].getName());
//        item->setSizeHint(QSize(200,64));
      //  QImage *image = new QImage("thegodfather.jpg");
//        QIcon icon(QPixmap(movieList[i].getPosterPath()));
        //if(icon->isNull())
        //    QMessageBox::information(this,"pl","pl");
        //QFile
//        item->setIcon(icon);

//        ui->listWidget->addItem(item);
        //QSize size = new QSize(100,100);
        //QIcon *icon = new QIcon("thegodfather.jpg");
        //ui->listWidget->item(i)->setIcon(QIcon("thegodfather.jpg"));

        addMovieToListWidget(movieList[i]);
    }
}

void MainWindow::addMovieToListWidget(const movie& mov)
{
    QListWidgetItem *item = new QListWidgetItem(mov.getName());
    item->setSizeHint(QSize(200,64));
    QIcon icon(QPixmap(mov.getPosterPath()));
    item->setIcon(icon);

    ui->listWidget->addItem(item);
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
}

movie MainWindow::getMovieByName(const QString& movieName)
{
    foreach(movie mov,movieList)
        if(mov.getName() == movieName)
            return mov;

    throw "Don't find any movie with name " + movieName + " !";
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
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
        ui->listWidget->setIconSize(QSize(50,40));
    }
    else
    {
        ui->listWidget->setIconSize(QSize(0,0));
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
    for(int i=0;i<ui->listWidget->count();i++)
        if(ui->listWidget->item(i)->isSelected())
        {
            for(int j=0;j<movieList.count();j++)
                if(ui->listWidget->item(i)->text() == movieList[j].getName())
                {
                    movieList.removeAt(j);
                    break ;
                }

            ui->listWidget->takeItem(i);
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
    if()
}
