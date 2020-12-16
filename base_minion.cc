#include <string>
#include <iostream>
#include "base_minion.h"
#include "minion.h"
#include "exceptions.h"

RefObj::RefObj(std::unique_ptr<Minion>& ref) : ref{ref} {}

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

Minion * BaseMinion::getBase(const bool &release) {
	if(p_ref.get() != nullptr && release){
		p_ref->ref.release();
		p_ref.reset();
	}else if(release){
		b_ref->ref.release();
	}
	return this;
}

std::unique_ptr<Minion>& BaseMinion::getBoardRef() const {
	if(b_ref.get() == nullptr) throw IllegalAction{"b_ref not defined"};
	return b_ref->ref;
}

void BaseMinion::setBoardRef(std::unique_ptr<Minion>& ref){
	if(ref.get() != nullptr){
		b_ref.reset(new RefObj(ref));
	}
}

void BaseMinion::resetBoardRef() {
	b_ref.reset();
}

void BaseMinion::setParent(std::unique_ptr<Minion>& ref) {
	if(ref.get() != nullptr){
		p_ref.reset(new RefObj(ref));
	}
}