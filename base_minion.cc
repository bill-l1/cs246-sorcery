#include <string>
#include "base_minion.h"
#include "minion.h"

BaseMinion::BaseMinion(const std::string &name, const std::string &description, const int &cost, const int &att, const int &def, const int &activateCost, std::unique_ptr<Effect> eff)
	: Minion{name, description, cost, "Minion"},
	attack{att},
	defense{def},
	actions{1},
	activateCost{activateCost},
	ability{std::move(eff)}
{}

BaseMinion::~BaseMinion(){}

int BaseMinion::getAttack() const {
	return attack;
}

int BaseMinion::getDefense() const {
	return defense;
}

int BaseMinion::getActions() const {
	return actions;
}

int BaseMinion::getActivateCost() const {
	return activateCost;
}

void BaseMinion::attackOther(Minion * target){
	//TODO
}

void BaseMinion::setAttack(int atk) {
	attack = atk;
}

void BaseMinion::setDefense(int def) {
	defense = def;
}

Effect * BaseMinion::getAbility() const {
return ability.get();
}

