
#include <memory>
#include "game.h"
#include "player.h"
#include "effect.h"
#include "card.h"
#include "spell.h"

Spell::Spell(const std::string &name, const std::string &description, const int &cost, std::unique_ptr<Effect> eff, Card * tar) : 
	Card{name, description, cost, "Spell"},
	effect{std::move(eff)},
	target{tar}
{}

Spell::~Spell() {};

Effect * Spell::getEffect() const {
	return effect.get();
}

Card * Spell::getTarget() const {
	return target;
}
void Spell::setTarget(Card * tar) {
	this->target = tar;
}

