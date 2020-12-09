
#include <memory>
#include "game.h"
#include "player.h"
#include "effect.h"
#include "card.h"
#include "ritual.h"

Ritual::Ritual(const std::string &name, const std::string &description, const int &cost, std::unique_ptr<Effect> eff, int chg) : 
	Card{name, description, cost, "Ritual"},
	effect{std::move(eff)},
	charges{chg}
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

void Ritual::onTurnStart() {
return;
}
void Ritual::onAllyPlay() {
return;
}
void Ritual::onEnemyPlay() {
return;
}

