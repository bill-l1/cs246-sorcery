#include <string>
#include <iostream>
#include "minion.h"
#include "card.h"


Minion::Minion(const std::string &name, const std::string &description, const int &cost, const std::string &type) : Card{name, description, cost, type}
{}

Minion::~Minion(){}

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

int Minion::getActivateCost() const {
    std::cerr << "Illegal function call from minion" << std::endl;
    return -999;
}

void Minion::attackOther(Minion * target){
    std::cerr << "Illegal function call from minion" << std::endl;
    return;
}

void Minion::buff(const int &att, const int &def){
    std::cerr << "Illegal function call from minion" << std::endl;
    return;
}

Minion * Minion::getBase(){
    std::cerr << "Illegal function call from minion" << std::endl;
    return nullptr;
}