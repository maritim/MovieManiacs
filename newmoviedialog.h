#ifndef NEWMOVIEDIALOG_H
#define NEWMOVIEDIALOG_H

#include <QDialog>

#include "movie.h"

namespace Ui {
class NewMovieDialog;
}

class NewMovieDialog : public QDialog
{
    Q_OBJECT
    
    movie newMovie;

public:
    explicit NewMovieDialog(QWidget *parent = 0);
    ~NewMovieDialog();
    void setMovie(const movie&);
    movie getMovie(void) const;

private slots:
    void on_buttonBox_accepted();
    void on_toolButton_clicked();

private:
    Ui::NewMovieDialog *ui;
    void initialise(void);
};

#endif // NEWMOVIEDIALOG_H
