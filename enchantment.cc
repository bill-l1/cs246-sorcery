#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include "minion.h"
#include "enchantment.h"
#include "player.h"
#include "exceptions.h"

Enchantment::Enchantment(const std::string &name, const std::string &description, const int &cost, const std::string &att, const std::string &def )
    : Minion{name, description, cost, "Enchantment"},
    att_str{att},
    def_str{def}
{}

Enchantment::~Enchantment(){}

int Enchantment::statConvert(const int &in, const std::string &s) const{
    try{
        if (s.length() < 2) return in;
        int val = stoi(s.substr(1));
        if(s[0] == '+'){
            return in + val;
        }else if(s[0] == '-'){
            return in - val;
        }else if(s[0] == '*'){
            return in * val;
        }
        return in;
    }catch(const std::invalid_argument& ia){
        throw IllegalAction{"bad Enchantment string: "+s};
        return in;
    }
}

void Enchantment::verifyComponentNotNull() const{
    if(component.get() == nullptr) {
        throw IllegalAction{"Enchantment null component"};
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

Minion * Enchantment::getComponent(const bool &steal)  {
    if(steal){
        return component.release();
    }else{
        return component.get();
    }
}

void Enchantment::setComponent(Minion * minion){
    component.reset(minion); 
    setParent(component);
}

std::string Enchantment::getAttackStr() const {
    return att_str;
}

int Enchantment::getAttack() const {
    verifyComponentNotNull();
    return statConvert(component->getAttack(), att_str);
}

void Enchantment::setAttack(const int &att) {
    verifyComponentNotNull();
    component->setAttack(att); 
}

std::string Enchantment::getDefenseStr() const {
    return def_str;
}

int Enchantment::getDefense() const {
    verifyComponentNotNull();
    return statConvert(component->getDefense(), def_str); 
}

void Enchantment::setDefense(const int &def) {
    verifyComponentNotNull();
    component->setDefense(def); 
}

int Enchantment::getActions() const {
    verifyComponentNotNull();
    return component->getActions();
}

void Enchantment::setActions(const int &n) {
    verifyComponentNotNull();
    component->setActions(n);
}

int Enchantment::getActivateCost() const {
    verifyComponentNotNull();
    return component->getActivateCost();
}

void Enchantment::buff(const int &att, const int &def) {
    verifyComponentNotNull();
    component->buff(att, def);
}

Minion * Enchantment::getBase(const bool &release){
    verifyComponentNotNull();
    return component->getBase(release);
}

std::vector<std::unique_ptr<Effect>> Enchantment::onDeath() {
	// return std::move(component->onDeath());
    verifyComponentNotNull();
    return component->onDeath();
}

std::vector<std::unique_ptr<Effect>> Enchantment::onEndTurn() {
    // return std::move(component->onEndTurn());
    verifyComponentNotNull();
    return component->onEndTurn();
}

std::vector<std::unique_ptr<Effect>> Enchantment::onPlay() {
    // return std::move(component->onPlay());
    verifyComponentNotNull();
    return component->onPlay();
}

std::vector<std::unique_ptr<Effect>> Enchantment::onActivate(Card * target) {
    // return std::move(component->onActivate(target));
    verifyComponentNotNull();
    return component->onActivate(target);
}

std::unique_ptr<Minion>& Enchantment::getBoardRef() const {
    verifyComponentNotNull();
    return component->getBoardRef();
}

void Enchantment::setBoardRef(std::unique_ptr<Minion>& ref) {
    verifyComponentNotNull();
    component->setBoardRef(ref);
}

void Enchantment::setParent(std::unique_ptr<Minion>& ref) {
    verifyComponentNotNull();
    if(!dynamic_cast<Enchantment *>(component.get())){
        component->setParent(ref);
    }
}
