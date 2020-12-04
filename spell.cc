
#include "game.h"
#include "player.h"
#include "effect.h"
#include "card.h"
#include "spell.h"

Spell::Spell(const std::string &name, const std::string &description, const int &cost, Effect  * eff, Card * tar) : 
	Card{name, description, cost, "Spell"},
effect{eff},
target{tar}
{}
	Effect * Spell::getEffect() const {
	return effect;
	}
	Card * Spell::getTarget() const {
	return target;
	}
	void Spell::setTarget(Card * tar) {
	this->target = tar;

	}

