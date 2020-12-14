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
		BaseMinion(const std::string &name, const std::string &description, const int &cost, const int &att, const int &def, const int &activateCost=-1);
		virtual ~BaseMinion();
		int getAttack() const override;
		void setAttack(const int &att) override;
		int getDefense() const override;
		void setDefense(const int &def) override;
		int getActions() const override;
		void setActions(const int &n) override;
		int getActivateCost() const override;
		void buff(const int &att, const int &def) override;
		Minion * getBase() override;
};

#endif
