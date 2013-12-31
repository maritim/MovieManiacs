#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "movie.h"
#include "networkclass.h"

#include <QMainWindow>
#include <QList>
#include <QListWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QList<movie> movieList;
    QString collectionFile;
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void loadMovieList(QString);
    void loadMovieListWidget(const QList<movie>&);
    void addMovieToListWidget(const movie&);
    movie getMovieByName(const QString&);
    int getIndexByName(const QString&);

private slots:
    void on_actionNew_Window_triggered();
    void on_movieListWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_actionToolbar_changed();
    void on_actionThumbnails_changed();
    void on_actionExit_triggered();
    void on_actionSave_Collection_triggered();
    void on_actionDelete_Movie_triggered();
    void on_actionOpen_Collection_triggered();
    void on_actionNew_Collection_triggered();
    void on_actionSave_As_triggered();
    void on_actionUpdate_Movie_triggered();

    void updateMovie(movie*);
    void progressUpdate(int);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
