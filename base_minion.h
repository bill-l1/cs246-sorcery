#ifndef BASE_MINION_H
#define BASE_MINION_H
#include "minion.h"

class BaseMinion : public Minion {
	int attack;
	int defense;
	int actions;
	int activateCost;
	public:
		BaseMinion(const std::string &name, const std::string &description, const int &cost, const int &att, const int &def, const int &activateCost=-1);
		virtual ~BaseMinion();
		int getAttack() const override;
		int getDefense() const override;
		int getActions() const override;
		int getActivateCost() const override;
		void attackOther(Minion * target) override;
};

#endif
