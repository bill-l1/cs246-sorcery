#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <string>
#include <memory>
#include <map>
//#include "base_minion.h"
//#include "minion.h"
// may need helper funciton to move from deck to hand to board to etc.
//#include "player.h"
//#include "minion.h"
//#include "base_minion.h"

class Player;
//class Minion;
//class BaseMinion;
//class MinionList;

class Card  {
	std::string name;
	std::string description;
	int cost;
	Player * owner;
	std::string type;

	public:
		Card(const std::string &name, const std::string &description, const int &cost, const std::string &type);
		virtual ~Card();
		std::string getName() const;
		std::string getDescription() const;
		int getCost() const;
		Player * getOwner() const;
		void setOwner(Player * player);	
		std::string getType() const;

	friend class CardFactory;
};

#endif
