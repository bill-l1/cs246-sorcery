#ifndef SPELL_H
#define SPELL_H
#include "game.h"
#include "player.h"
#include "effect.h"
#include "card.h"
class Spell : public Card {
	Effect * effect;
	Card * target;
	public:
		Spell(const std::string &name, const std::string &description, const int &cost, Effect  * effect, Card * target);
	//	~Spell();
		Effect * getEffect() const;
		Card * getTarget() const;
		void setTarget(Card * tar);

};

#endif
