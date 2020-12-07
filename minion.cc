#include <string>
#include "minion.h"
#include "card.h"


Minion::Minion(const std::string &name, const std::string &description, const int &cost, const std::string &type) : Card{name, description, cost, type}
{}

Minion::~Minion(){}

int Minion::getAttack() const {
    return -999;
}
int Minion::getDefense() const {
    return -999;
}
int Minion::getActions() const {
    return -999;
}
int Minion::getActivateCost() const {
    return -999;
}
void Minion::attackOther(Minion * target){
    return;
}

void Minion::setAttack(int atk) {
return;
}

void Minion::setDefense(int def) {
return;
}

void Minion::onDeath() {
return;
}

void Minion::onEndTurn() {

return;
}

void Minion::onAllyPlay() {

return;
}

void Minion::onEnemyPlay() {

return;
}
