#include <string>
#include <iostream>
#include "base_minion.h"
#include "minion.h"

RefObj::RefObj(std::unique_ptr<Minion>& b_ref) : b_ref{b_ref} {}

BaseMinion::BaseMinion(const std::string &name, const std::string &description, const int &cost, const int &att, const int &def, const int &activateCost)
	: Minion{name, description, cost, "Minion"},
	attack{att},
	defense{def},
	actions{0},
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

void BaseMinion::setActions(const int &n) {
	actions = n;
}

int BaseMinion::getActivateCost() const {
	return activateCost;
}

void BaseMinion::buff(const int &att, const int &def){
	attack += att;
	defense += def;
}

Minion * BaseMinion::getBase() {
	return this;
}

std::unique_ptr<Minion>& BaseMinion::getBoardRef() const {
    return b_ref->b_ref;
}

void BaseMinion::setBoardRef(std::unique_ptr<Minion>& ref){
    b_ref.release();
    b_ref.reset(new RefObj(ref));
}
