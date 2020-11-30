#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <memory>
#include <stack>

// may need helper funciton to move from deck to hand to board to etc.

class Player  {
	std::string name;
	int life;
	int magic;
	//std::stack<std::unique_ptr<Card>> deck;
	//std::vector<std::unique_ptr<Card>> hand;
	//std::vector<std::unique_ptr<Card>> board;
	//std::stack<std::unique_ptr<Card>> graveyard;
	//std::unique_ptr<Card> ritual;

	public:
		Player(const std::string &name); //TODO add deck as argument, then fill hand
		std::string getName() const;
		int getLife() const;
		int getMagic() const;
		//void runOnPlay(); //iterate through all board/rituals for onPlay effects
		//void runOnStartTurn(); 
		//void runOnEndTurn();
	friend class Game;
};

#endif
