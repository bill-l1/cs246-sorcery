#ifndef MINION_H
#define MINION_H
#include <vector>
#include <memory>
#include <string>
#include "card.h"
#include "effect.h"

class Minion : public Card {
	public:
		Minion(const std::string &name, const std::string &description, const int &cost, const std::string &type);
		virtual ~Minion();
		virtual Minion * getComponent(const bool &steal = false);
		virtual std::string getMinionName() const;
		virtual std::string getMinionDescription() const;

		// - relies heavily on use of "virtual" to make sure the following don't get called 
		// - Minion card should ALWAYS inherit either Enchantment or BaseMinion first, shouldn't need to worry about type safety (depends on CardFactory and CardList)
		// - makes calling minion methods A LOT easier without needing to constantly cast between those two

		virtual int getMinionCost() const;
		virtual int getAttack() const;
		virtual void setAttack(const int &att);
		virtual int getDefense() const;
		virtual void setDefense(const int &def);
		virtual int getActions() const;
		virtual void setActions(const int &n);
		virtual int getActivateCost() const;
		virtual void buff(const int &att, const int &def);
		virtual Minion * getBase();
		virtual std::vector<std::unique_ptr<Effect>> onEndTurn();
		virtual std::vector<std::unique_ptr<Effect>> onDeath();
		virtual std::vector<std::unique_ptr<Effect>> onPlay();
		virtual std::vector<std::unique_ptr<Effect>> onActivate(Card * target = nullptr);
		virtual std::unique_ptr<Minion>& getBoardRef() const = 0;
		virtual void setBoardRef(std::unique_ptr<Minion>& ref);
		virtual void resetBoardRef();
};

#endif
