#ifndef GAME_H
#define GAME_H
#include <string>
#include <vector>
#include <stack>
#include <memory>
#include "view.h"

class Card;
class Minion;
class Player;

class Game {
	std::shared_ptr<Player> p1; //Player 1
	std::shared_ptr<Player> p2; //Player 2
	std::shared_ptr<Player> activePlayer; //current active player
	std::shared_ptr<Player> nonActivePlayer; //other player
	std::unique_ptr<View> view;
	int turns;
	bool testing;
	void startTurn();
	std::stack<std::unique_ptr<Card>> loadDeck(const std::string &dname, const bool &doShuffle, Player * owner) const;
	template <typename T> 
	void shuffleVector(std::vector<T> & v) const;
	void update(); //helper function for checking card/player states after actions
	public:
		Game(const std::string &p1name, const std::string &p2name, const std::string &p1deckname, const std::string &p2deckname, const bool &testing); //starts the game, creating players and decks from player/file names
		Player * getP1() const;
		Player * getP2() const;
		Player * getActivePlayer() const;
		Player * getNonActivePlayer() const;
		int getTurns() const;
		void endTurn(); //ends turn, runs end turn triggers and swaps active players
		void draw();
		void discard(const int &pos);
		void displayHelp() const;
		void displayMinion(const int &pos) const;
		void displayHand() const;
		void displayBoard() const;
		void play(const int &pos); //plays card at hand[pos], no target
		void play(const int &pos, const int &pnum, const char &t); //plays card at hand[pos], targetting t belonging to Player pnum
		void attack(const int &pos);
		void attack(const int &pos, const int &t);
		void buff(Player * player, const int &n);
		void buff(Minion * minion, const int &att, const int &def);
		//TODO implement rest of methods
};

#endif
