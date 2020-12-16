#ifndef GAME_H
#define GAME_H
#include <string>
#include <vector>
#include <stack>
#include <memory>
#include "view.h"

extern const unsigned MAX_HAND_SIZE;
extern const unsigned MAX_BOARD_SIZE;
extern const unsigned INTIAL_HAND_SIZE;

class Card;
class Minion;
class Player;
class Enchantment;
class Effect;

class Game {
	std::shared_ptr<Player> p1; //Player 1
	std::shared_ptr<Player> p2; //Player 2
	std::shared_ptr<Player> activePlayer; //current active player
	std::shared_ptr<Player> nonActivePlayer; //other player
	std::unique_ptr<View> view; // View object
	int turns; // stores # of turns
	bool testing; // -testing
	void startTurn(); // helper function for running start of turn actions
	std::stack<std::unique_ptr<Card>> loadDeck(const std::string &dname, const bool &doShuffle, Player * owner) const; // creates a deck for a player from file dname, optionally shuffling it
	template <typename T> 
		void shuffleVector(std::vector<T> & v) const; // shuffles a vector
	void update(); //helper function for checking card/player states after actions
	std::unique_ptr<Card> takeCardFromHand(Player * player, const int &pos); // helper function that moves card at hand[pos] from a player
	void runEffects(std::vector<std::unique_ptr<Effect>> v); // helper function that runs effects sequentially in a vector
	template <class From, class To>
		std::unique_ptr<To> castUnique(std::unique_ptr<From> u_ptr);
	public:
		Game(const std::string &p1name, const std::string &p2name, const std::string &p1deckname, const std::string &p2deckname, const bool &testing); //starts the game, creating players and decks from player/file names
		Player * getP1() const;
		Player * getP2() const;
		Player * getActivePlayer() const;
		Player * getNonActivePlayer() const;
		int getTurns() const;
		void endTurn(); //ends turn, runs end turn triggers and swaps active players
		void draw(); // can throw HandIsFull exception
		void discard(const int &pos); // discards active player's card at pos
		void displayHelp() const; // displays help
		void displayMinion(const int &pos) const; // inspects a minion
		void displayHand() const; //displays hand
		void displayBoard() const; //displays board
		void play(const int &pos); //plays card at hand[pos], no target
		void play(const int &pos, const int &pnum, const char &t); //plays card at hand[pos], targetting t belonging to Player pnum
		void use (const int &pos); // activates minion
		void use (const int &pos,const int &pnum, const int &t); // activates minion, targetting t belong to Player pnum
		void attack(const int &pos); // uses minion at pos to attack other player
		void attack(const int &pos, const int &t); // uses minion at pos to attack other player's minion at t
		void buff(Player * player, const int &n); // add or subtract player health
		void buff(Minion * minion, const int &att, const int &def); // add or subtract minion attack and defense
		void endGame(Player * winner = nullptr); // end the game

		void verifyHandPosition(Player * player, const int &pos) const; //throws if position is outside of player's hand
		void verifyBoardPosition(Player * player, const int &pos) const; //throws if position is outside of player's board
		void verifyBoardNotFull(Player * player) const; //throws if board is full
		int verifyMagicCost(Player * player, const int &n) const; //throws if n is greater than player's magic (unless testing is true); additionally returns the new magic amount.
		int verifyActionCost(Minion * minion, const int &n) const; //throws if n is greater than minion's actions (unless testing is true); additionally returns the new actions amount.

		void printAlert(const std::string &s, const int &type = 0) const; // prints an alert
};

#endif
