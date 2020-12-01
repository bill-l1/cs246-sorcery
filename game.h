#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "card.h"
#include "view.h"
#include <vector>
#include <memory>

class View;

class Game {
	std::shared_ptr<Player> p1; //Player 1
	std::shared_ptr<Player> p2; //Player 2
	std::shared_ptr<Player> activePlayer; //current active player
	std::shared_ptr<Player> nonActivePlayer; //other player
	std::unique_ptr<View> view;
	int turns;
	void startTurn();
	std::stack<std::unique_ptr<Card>> loadDeck(const bool &doShuffle) const;

	public:
		Game(const std::string &p1name, const std::string &p2name, const std::string &p1deckname, const std::string &p2deckname, const bool &testing); //starts the game, creating players and decks from player/file names
		std::shared_ptr<Player> getP1() const;
		std::shared_ptr<Player> getP2() const;
		std::shared_ptr<Player> getActivePlayer() const;
		std::shared_ptr<Player> getNonActivePlayer() const;
		int getTurns() const;
		void endTurn(); //ends turn, runs end turn triggers and swaps active players
		void draw();
		void discard(const int &pos);
		void displayHelp() const;
		void displayHand() const;
		//TODO implement rest of methods
};

#endif
