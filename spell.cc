
#include <memory>
#include "spell.h"

Spell::Spell(const std::string &name, const std::string &description, const int &cost, Card * tar) : 
	Card{name, description, cost, "Spell"},
	target{tar}
{}

Spell::~Spell() {};

Card * Spell::getTarget() const {
	return target;
}
void Spell::setTarget(Card * tar) {
	this->target = tar;
}

std::unique_ptr<Effect> Spell::onPlay() {
	return nullptr; //TODO should throw InvalidPlay
}

std::unique_ptr<Effect> Spell::onPlay(std::unique_ptr<Minion>& target) {
	return nullptr; //TODO should throw InvalidPlay
}

std::unique_ptr<Effect> Spell::onPlay(std::unique_ptr<Ritual>& target) {
	return nullptr; //TODO should throw InvalidPlay
}