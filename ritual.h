#ifndef RITUAL_H
#define RITUAL_H
#include <memory>
#include "effect.h"
#include "card.h"

class Ritual : public Card {
	std::unique_ptr<Effect> effect;
	int charges;
	int activateCost;
	public:
		Ritual(const std::string &name, const std::string &description, const int &cost, std::unique_ptr<Effect> effect, const int &charges, const int &activateCost=1);
		virtual ~Ritual();
		Effect * getEffect() const;
		int getCharges() const;
		void setCharges(const int &chg);
		int getActivateCost() const;
		virtual Effect * onTurnStart();
		virtual Effect * onPlay();
};

#endif
