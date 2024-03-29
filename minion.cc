#include <string>
#include <iostream>
#include <memory>
#include <vector>
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
}

int Minion::getDefense() const {
    std::cerr << "Illegal function call from minion" << std::endl;
    return -999;
}

void Minion::setDefense(const int &def) {
    std::cerr << "Illegal function call from minion" << std::endl;
}

int Minion::getActions() const {
    std::cerr << "Illegal function call from minion" << std::endl;
    return -999;
}

void Minion::setActions(const int &n) {
    std::cerr << "Illegal function call from minion" << std::endl;
}

int Minion::getActivateCost() const {
    std::cerr << "Illegal function call from minion" << std::endl;
    return -999;
}

void Minion::buff(const int &att, const int &def){
    std::cerr << "Illegal function call from minion" << std::endl;
}

Minion * Minion::getBase(const bool &release) {
    std::cerr << "Illegal function call from minion" << std::endl;
    return nullptr;
}

std::vector<std::unique_ptr<Effect>> Minion::onDeath() {
    // return std::move(nullptr);
    std::vector<std::unique_ptr<Effect>> empty;
    return empty;
}

std::vector<std::unique_ptr<Effect>> Minion::onEndTurn() {
    // return std::move(nullptr);
    std::vector<std::unique_ptr<Effect>> empty;
    return empty;
}

std::vector<std::unique_ptr<Effect>> Minion::onPlay() {
    // return std::move(nullptr);
    std::vector<std::unique_ptr<Effect>> empty;
    return empty;
}

std::vector<std::unique_ptr<Effect>> Minion::onActivate(Card * target) {
    // return std::move(nullptr);
    std::vector<std::unique_ptr<Effect>> empty;
    return empty;
}

void Minion::setBoardRef(std::unique_ptr<Minion>& ref) {
    std::cerr << "Illegal function call from minion" << std::endl;
}

void Minion::setParent(std::unique_ptr<Minion>& ref) {
    std::cerr << "Illegal function call from minion" << std::endl;
}
