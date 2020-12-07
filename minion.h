#ifndef MINION_H
#define MINION_H
#include "card.h"

class Minion : public Card {
	public:
		Minion(const std::string &name, const std::string &description, const int &cost, const std::string &type);
		virtual ~Minion();
		virtual Minion * getComponent() const;
		virtual std::string getMinionName() const;
		virtual std::string getMinionDescription() const;
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
};

#endif
