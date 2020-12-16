#ifndef RITUAL_H
#define RITUAL_H
#include <memory>
#include "effect.h"
#include "card.h"

class Ritual : public Card {
	std::unique_ptr<Effect> effect;
	int charges;
	public:
		Ritual(const std::string &name, const std::string &description, const int &cost, std::unique_ptr<Effect> effect, const int &charges);
		virtual ~Ritual();
		Effect * getEffect() const;
		int getCharges() const;
		virtual Effect * onTurnStart();
		virtual Effect * onPlay();
		void setCharges(int chg);
};

#endif
