#include <memory>
#include "effect.h"
#include "ritual.h"

Ritual::Ritual(const std::string &name, const std::string &description, const int &cost, std::unique_ptr<Effect> effect, const int &charges, const int &activateCost) : 
	Card{name, description, cost, "Ritual"},
	effect{std::move(effect)},
	charges{charges},
	activateCost{activateCost}
{}

Ritual::~Ritual() {};

Effect * Ritual::getEffect() const {
	return effect.get();
}

int Ritual::getCharges() const {
	return charges;
}
void Ritual::setCharges(const int &chg) {
	this->charges = chg;
}

int Ritual::getActivateCost() const {
	return activateCost;
}

Effect * Ritual::onTurnStart() {
	return nullptr;
}

Effect * Ritual::onPlay() {
	return nullptr;
}

