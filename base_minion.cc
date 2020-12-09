#include <string>
#include <iostream>
#include "base_minion.h"
#include "minion.h"

BaseMinion::BaseMinion(const std::string &name, const std::string &description, const int &cost, const int &att, const int &def, const int &activateCost, std::unique_ptr<Effect> eff)
	: Minion{name, description, cost, "Minion"},
	attack{att},
	defense{def},
	actions{0},
	activateCost{activateCost},
	ability{std::move(eff)}
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

Effect * BaseMinion::getAbility() const {
return ability.get();
}

