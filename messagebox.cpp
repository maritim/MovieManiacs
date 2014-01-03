#include "messagebox.h"

#define ERROR_ICON ":/images/film_error.png"
#define QUESTION_ICON ":/images/film_question.png"

void MessageBox::ErrorMessageBox(const QString& title, const QString& text) {

    QMessageBox *box = new QMessageBox();

    box->setIconPixmap(QPixmap(ERROR_ICON));
    box->setWindowTitle(title);
    box->setText(text);
    box->setStandardButtons(QMessageBox::Ok);
    box->setModal(true);

    box->show();
}

int MessageBox::QuestionMessageBox(const QString& title, const QString& question) {

    QMessageBox *box = new QMessageBox();

    box->setIconPixmap(QPixmap(QUESTION_ICON));
    box->setWindowTitle(title);
    box->setText(question);
    box->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    box->setModal(true);

    return box->exec();
}
