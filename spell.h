#ifndef SPELL_H
#define SPELL_H
#include <memory>
#include "card.h"
#include "effect.h"

class Spell : public Card {
	public:
		Spell(const std::string &name, const std::string &description, const int &cost);
		virtual ~Spell();
		virtual std::vector<std::unique_ptr<Effect>> onPlay();
};

class TargettedSpell : public Spell {
	public:
		TargettedSpell(const std::string &name, const std::string &description, const int &cost);
		virtual ~TargettedSpell();
		virtual std::vector<std::unique_ptr<Effect>> onPlay(std::unique_ptr<Minion>& target);
		virtual std::vector<std::unique_ptr<Effect>> onPlay(std::unique_ptr<Ritual>& target);
};

#endif
