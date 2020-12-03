#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <memory>
#include <vector>
#include <stack>

// may need helper funciton to move from deck to hand to board to etc.
class Card;
class Minion;
class BaseMinion;

class Player  {
	std::string name;
	int life;
	int magic;
	std::stack<std::unique_ptr<Card> > deck;
	std::vector<std::unique_ptr<Card> > hand;
	std::vector<std::unique_ptr<Minion>> board;
	std::stack<std::unique_ptr<Minion>> graveyard;
	//std::unique_ptr<Card> ritual;
	public:
		Player(const std::string &name);
		std::string getName() const;
		int getLife() const;
		void setLife(const int &n);
		int getMagic() const;
		void setMagic(const int &n);
		int getDeckSize() const;
		void setDeck(std::stack<std::unique_ptr<Card>> d);
		int getHandSize() const;
		int getBoardSize() const;
		void draw();
		void playCard(std::unique_ptr<BaseMinion> card);
		//void playCard(std::unique_ptr<Card> card); this shouldn't ever be called !!
		//void runOnPlay(); //iterate through all board/rituals for onPlay effects
		//void runOnStartTurn(); 
		//void runOnEndTurn();
		friend class Game;
		friend class View;
};

#endif
