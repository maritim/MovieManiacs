#ifndef MOVIEFORM_H
#define MOVIEFORM_H

#include "movie.h"

#include <QDialog>

namespace Ui {
class movieform;
}

class movieform : public QDialog
{
    Q_OBJECT

    movie mov;
    
public:
    explicit movieform(QWidget *parent = 0);
    ~movieform();
    
private:
    Ui::movieform *ui;

public:
    void setMovie(const movie&);
    void getReady(void);
    void loadCastTableWidget(const movie&);
private slots:
    void on_buttonBox_accepted();
};

#endif // MOVIEFORM_H
