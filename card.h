#ifndef CARD_H
#define CARD_H

#include <string>
#include <memory>
#include <map>
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
		Card();
		std::string getName() const;
		std::string getType() const;
		std::string getDescription() const;
		int getCost() const;
		Player * getOwner() const;
		void setOwner(Player * player);	
	
	friend class CardFactory;
};

class CardFactory {
	public:
		static std::unique_ptr<Card> getCard(const std::string &name);
};

#endif
