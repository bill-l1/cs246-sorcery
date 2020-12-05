#include <string>
#include "base_minion.h"
#include "minion.h"

BaseMinion::BaseMinion(const std::string &name, const std::string &description, const int &cost, const int &att, const int &def, const int &activateCost)
	: Minion{name, description, cost, "Minion"},
	attack{att},
	defense{def},
	actions{1},
	activateCost{activateCost}
{}

BaseMinion::~BaseMinion(){}

int BaseMinion::getAttack() const {
	return attack;
}

void BaseMinion::setAttack(const int &att) {
	attack = att;
}

int BaseMinion::getDefense() const {
	return defense;
}

void BaseMinion::setDefense(const int &def) {
	defense = def;
}

int BaseMinion::getActions() const {
	return actions;
}

int BaseMinion::getActivateCost() const {
	return activateCost;
}

void BaseMinion::attackOther(Minion * target){
	this->buff(0, -target->getAttack());
	target->buff(0, -getAttack());
}

void BaseMinion::buff(const int &att, const int &def){
	attack += att;
	defense += def;
}

BaseMinion * BaseMinion::getBase(){
	return this;
}