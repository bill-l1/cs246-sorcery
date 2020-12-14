#ifndef MINION_H
#define MINION_H
#include "card.h"
#include "effect.h"
#include <memory>

class Minion : public Card {
	public:
		Minion(const std::string &name, const std::string &description, const int &cost, const std::string &type);
		virtual ~Minion();
		virtual Minion * getComponent() const;
		virtual std::string getMinionName() const;
		virtual std::string getMinionDescription() const;
		virtual int getMinionCost() const;
		virtual int getAttack() const;
		virtual void setAttack(const int &att);
		virtual int getDefense() const;
		virtual void setDefense(const int &def);
		virtual int getActions() const;
		virtual void setActions(const int &n);
		virtual int getActivateCost() const;
		virtual void attackOther(Minion * target);
		virtual void buff(const int &att, const int &def);
		virtual Minion * getBase();
		virtual std::unique_ptr<Effect> onEndTurn();
		virtual std::unique_ptr<Effect> onDeath();
		virtual std::unique_ptr<Effect> onPlay();
		virtual std::unique_ptr<Effect> onActivate(Card * target = nullptr);
	
};

#endif
