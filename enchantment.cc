#include <string>
#include <iostream>
#include "minion.h"
#include "enchantment.h"
#include "player.h"

Enchantment::Enchantment(const std::string &name, const std::string &description, const int &cost, const std::string &att, const std::string &def )
    : Minion{name, description, cost, "Enchantment"},
    att_str{att},
    def_str{def}
{}

Enchantment::~Enchantment(){}

int Enchantment::statConvert(const int &in, const std::string &s) const{
    try{
        if (s.length() < 2) throw std::exception();
        int val = stoi(s.substr(1));
        if(s[0] == '+'){
            return in + val;
        }else if(s[0] == '-'){
            return in - val;
        }else if(s[0] == '*'){
            return in * val;
        }
        return val;
    } catch(...) {
        //TODO
        return in;
    }
}

std::string Enchantment::getMinionName() const {
    if(component == nullptr){
        return getName();
    }else{
        return component->getMinionName();
    }
}

std::string Enchantment::getMinionDescription() const {
    if(component == nullptr){
        return getDescription();
    }else{
        return component->getMinionDescription();
    }
}

int Enchantment::getMinionCost() const {
    if(component == nullptr){
        return getCost();
    }else{
        return component->getMinionCost();
    }
}

Minion * Enchantment::getComponent() const {
    return component.get(); //TODO exception for nullptr, same goes for the rest of the methods
}

void Enchantment::setComponent(Minion * minion){
    component.release();
    component.reset(minion); 
}

std::string Enchantment::getAttackStr() const {
    return att_str;
}

int Enchantment::getAttack() const {
    return statConvert(component->getAttack(), att_str);
}

void Enchantment::setAttack(const int &att) {
    component->setAttack(att); 
}

std::string Enchantment::getDefenseStr() const {
    return def_str;
}

int Enchantment::getDefense() const {
    return statConvert(component->getDefense(), def_str); 
}

void Enchantment::setDefense(const int &def) {
    component->setDefense(def); 
}

int Enchantment::getActions() const {
    return component->getActions();
}

void Enchantment::setActions(const int &n) {
    component->setActions(n);
}

int Enchantment::getActivateCost() const {
    return component->getActivateCost();
}

void Enchantment::buff(const int &att, const int &def) {
    component->buff(att, def);
}

Minion * Enchantment::getBase(){
    return component->getBase();
}

Effect * Enchantment::getAbility() const {
	return component->getAbility();
}

Effect * Enchantment::onDeath() {
	return component->onDeath();
}

Effect * Enchantment::onEndTurn() {
    return component->onEndTurn();
}

Effect * Enchantment::onPlay() {
    return component->onPlay();
}

std::unique_ptr<Minion>& Enchantment::getBoardRef() const {
    return component->getBoardRef();
}

void Enchantment::setBoardRef(std::unique_ptr<Minion>& ref) {
    component->setBoardRef(ref);
}