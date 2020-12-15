#ifndef SPELL_H
#define SPELL_H
#include <memory>
#include "game.h"
#include "player.h"
#include "effect.h"
#include "card.h"
class Spell : public Card {
	Card * target;
	public:
		Spell(const std::string &name, const std::string &description, const int &cost, Card * target);
		virtual ~Spell();
		Card * getTarget() const;
		void setTarget(Card * tar);
		virtual std::unique_ptr<Effect> onPlay(Card * target);

};

#endif
