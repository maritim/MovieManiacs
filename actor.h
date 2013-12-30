#ifndef ACTOR_H
#define ACTOR_H

#include <QObject>

class actor : private QObject
{
    Q_OBJECT

protected:
    QString name,role;

public:
    explicit actor(QObject *parent = 0);

    actor(const QString&,const QString&);
    actor(const actor&);

    void setName(const QString&);
    QString getName(void) const;
    void setRole(const QString&);
    QString getRole(void) const;

signals:
    
public slots:
    
};

#endif // ACTOR_H
