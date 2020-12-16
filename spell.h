#ifndef SPELL_H
#define SPELL_H
#include <memory>
#include "card.h"
#include "effect.h"

class Spell : public Card {
	Card * target;
	public:
		Spell(const std::string &name, const std::string &description, const int &cost, Card * target);
		virtual ~Spell();
		Card * getTarget() const;
		void setTarget(Card * tar);
		virtual std::unique_ptr<Effect> onPlay();
		virtual std::unique_ptr<Effect> onPlay(std::unique_ptr<Minion>& target);
		virtual std::unique_ptr<Effect> onPlay(std::unique_ptr<Ritual>& target);
};

#endif
