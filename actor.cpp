#include "actor.h"

actor::actor(QObject *parent) :
    QObject(parent)
{
    name = role = "";
}

actor::actor(const QString& name, const QString& role)
{
    this->name = name;
    this->role = role;
}

actor::actor(const actor& act) : QObject() {
    this->name = act.name;
    this->role = act.role;
}

void actor::setName(const QString& name) {
    this->name = name;
}

QString actor::getName(void) const {
    return this->name;
}

void actor::setRole(const QString& role) {
    this->role = role;
}

QString actor::getRole(void) const {
    return this->role;
}
