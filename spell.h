#ifndef SPELL_H
#define SPELL_H
#include <memory>
#include "game.h"
#include "player.h"
#include "effect.h"
#include "card.h"
class Spell : public Card {
	std::unique_ptr<Effect> effect;
	Card * target;
	public:
		Spell(const std::string &name, const std::string &description, const int &cost, std::unique_ptr<Effect> effect, Card * target);
		virtual ~Spell();
		Effect * getEffect() const;
		Card * getTarget() const;
		void setTarget(Card * tar);

};

#endif
