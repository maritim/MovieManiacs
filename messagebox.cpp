#include "messagebox.h"

#define ERROR_ICON ":/images/film_error.png"

void MessageBox::ErrorMessageBox(const QString& title, const QString& text)
{
    QMessageBox *box = new QMessageBox();

    box->setIconPixmap(QPixmap(ERROR_ICON));
    box->setWindowTitle(title);
    box->setText(text);
    box->setStandardButtons(QMessageBox::Ok);
    box->setDefaultButton(QMessageBox::Ok);
    //box->setParent(parent);
    box->setModal(true);

    box->show();
}

MessageBox::~MessageBox()
{
}
