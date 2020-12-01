#ifndef CARD_H
#define CARD_H

#include <map>
#include <string>
#include "player.h"

class Player;

class Card {
	std::string name;
	std::string type;
	std::string description;
	int cost;
	Player * owner;

	public:
		
};

class CardFactory {

};

#endif
