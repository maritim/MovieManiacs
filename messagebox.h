#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QDialog>
#include <QMessageBox>
#include <QIcon>

namespace Ui {
class MessageBox;
}

class MessageBox : public QObject
{
    Q_OBJECT
    
public:
    static void ErrorMessageBox(const QString&, const QString&);
    static int QuestionMessageBox(const QString&, const QString&);
};

#endif // MESSAGEBOX_H
