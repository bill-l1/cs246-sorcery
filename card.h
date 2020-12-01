#ifndef CARD_H
#define CARD_H

#include <string>
#include <memory>
#include <map>
#include <stack>
#include "player.h"

// may need helper funciton to move from deck to hand to board to etc.

class Player;

class Card  {
	std::string name;
	std::string type;
	std::string description;
	int cost;
	Player * owner;

	public:
		Card(const std::string &name); 
		std::string getName() const;
		std::string getType() const;
		std::string getDescription() const;
		int getCost() const;
		Player getOwner() const;	
};

class CardFactory {

};

#endif
