#include <string>
#include <iostream>
#include "minion.h"
#include "card.h"


Minion::Minion(const std::string &name, const std::string &description, const int &cost, const std::string &type) : Card{name, description, cost, type}
{}

Minion::~Minion(){}

Minion * Minion::getComponent(const bool &steal) {
    return nullptr;
}

std::string Minion::getMinionName() const {
    return getName();
}

std::string Minion::getMinionDescription() const {
    return getDescription();
}

int Minion::getMinionCost() const {
    return getCost();
}

int Minion::getAttack() const {
    std::cerr << "Illegal function call from minion" << std::endl;
    return -999;
}

void Minion::setAttack(const int &att){
    std::cerr << "Illegal function call from minion" << std::endl;
    return;
}

int Minion::getDefense() const {
    std::cerr << "Illegal function call from minion" << std::endl;
    return -999;
}

void Minion::setDefense(const int &def) {
    std::cerr << "Illegal function call from minion" << std::endl;
    return;   
}

int Minion::getActions() const {
    std::cerr << "Illegal function call from minion" << std::endl;
    return -999;
}

void Minion::setActions(const int &n) {
    std::cerr << "Illegal function call from minion" << std::endl;
    return;
}

int Minion::getActivateCost() const {
    std::cerr << "Illegal function call from minion" << std::endl;
    return -999;
}

void Minion::buff(const int &att, const int &def){
    std::cerr << "Illegal function call from minion" << std::endl;
    return;
}

Minion * Minion::getBase() {
    std::cerr << "Illegal function call from minion" << std::endl;
    return std::move(nullptr);
}

std::unique_ptr<Effect> Minion::onDeath() {
return std::move(nullptr);
}

std::unique_ptr<Effect> Minion::onEndTurn() {
return std::move(nullptr);
}

 std::unique_ptr<Effect> Minion::onPlay() {
return std::move(nullptr);
}

std::unique_ptr<Effect> Minion::onActivate(Card * target) {
return std::move(nullptr);
}

std::unique_ptr<Minion>& Minion::getBoardRef() const {
    std::unique_ptr<Minion> m = std::make_unique<Minion>("invalid", "", 1, "invalid");
    return m;
}

void Minion::setBoardRef(std::unique_ptr<Minion>& ref) {}

void Minion::resetBoardRef() {}
