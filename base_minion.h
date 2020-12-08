#ifndef BASE_MINION_H
#define BASE_MINION_H
#include <string>
#include "minion.h"
#include <memory>
class BaseMinion : public Minion {
	int attack;
	int defense;
	int actions;
	int activateCost;
	std::unique_ptr<Effect> ability;
	public:
		BaseMinion(const std::string &name, const std::string &description, const int &cost, const int &att, const int &def, const int &activateCost=-1, std::unique_ptr<Effect> ability=nullptr);
		virtual ~BaseMinion();
		int getAttack() const override;
		int getDefense() const override;
		int getActions() const override;
		int getActivateCost() const override;
		void attackOther(Minion * target) override;
		void setAttack(int atk) override;
		void setDefense(int def) override;
		Effect * getAbility() const override;
};

#endif
