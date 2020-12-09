#ifndef CARD_H
#define CARD_H
#include <string>
#include "game.h"
// may need helper funciton to move from deck to hand to board to etc.

class Player;

class Card  {
	std::string name;
	std::string description;
	int cost;
	Player * owner;
	std::string type;
	Game * game;

	public:
		Card(const std::string &name, const std::string &description, const int &cost, const std::string &type);
		virtual ~Card();
		virtual std::string getName() const;
		virtual std::string getDescription() const;
		int getCost() const;
		Player * getOwner() const;
		void setOwner(Player * player);	
		std::string getType() const;
		Game * getGame() const;
		void setGame(Game * game);

	friend class CardFactory;
};

#endif
