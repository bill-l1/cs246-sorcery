
#include <memory>
#include "effect.h"
#include "ritual.h"

Ritual::Ritual(const std::string &name, const std::string &description, const int &cost, std::unique_ptr<Effect> effect, const int &charges) : 
	Card{name, description, cost, "Ritual"},
	effect{std::move(effect)},
	charges{charges}
{}

Ritual::~Ritual() {};

Effect * Ritual::getEffect() const {
	return effect.get();
}

int Ritual::getCharges() const {
	return charges;
}
void Ritual::setCharges(int chg) {
	this->charges = chg;
}

Effect * Ritual::onTurnStart() {
	return nullptr;
}

Effect * Ritual::onPlay() {
	return nullptr;
}

