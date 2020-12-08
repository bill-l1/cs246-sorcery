#ifndef MINION_H
#define MINION_H
#include "card.h"
#include "effect.h"

class Minion : public Card {
	public:
		Minion(const std::string &name, const std::string &description, const int &cost, const std::string &type);
		virtual ~Minion();
		virtual int getAttack() const;
		virtual int getDefense() const;
		virtual int getActions() const;
		virtual int getActivateCost() const;
		virtual Effect * getAbility() const;
		virtual void attackOther(Minion * target);
		virtual void setAttack (int attack);
		virtual void setDefense(int defense);
		virtual void onEndTurn();
		virtual void onDeath();
		virtual void onAllyPlay();
		virtual void onEnemyPlay();
	
};

#endif
