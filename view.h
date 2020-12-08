#ifndef VIEW_H
#define VIEW_H
#include <string>
#include <vector>
#include "ascii_graphics.h"

#define COOL_DRAWINGS 1

class Game;

const std::vector<std::vector<std::string> > _COMMANDS = 
	{{"help", "Display this message."},
	{"end", "End the current player's turn."},
	{"quit", "End the game."},
	{"attack minion other-minion", "Orders minion to attack other-minion."},
	{"attack minion", "Orders minion to attack the opponent."},
	{"play card [target-player target-card]", "Play card, optionally targeting target-card owned by target-player."},
	{"use minion [target-player target-card]", "Use minion's special ability, optionally targeting target-card."},
	{"inspect minion", "View a minion's card and all enchantments on that minion."},
	{"hand", "Describe all cards in your hand."},
	{"board", "Describe all cards on the board."}};

const std::string _RED = "\033[31m";
const std::string _RED_BG = "\033[1;41m";
const std::string _GREEN = "\033[32m";
const std::string _GREEN_BG = "\033[1;42m";
const std::string _YELLOW = "\033[33m";
const std::string _YELLOW_BG = "\033[1;30m\033[1;43m";
const std::string _BLUE = "\033[34m";
const std::string _BLUE_BG = "\033[1;44m";
const std::string _WHITE = "\033[1;37m";
const std::string _RESET = "\033[0m";

class Player;
class Minion;

class View {
	Game * game;
	void seperator() const;
	public:
		View(Game * game);
		void printFromFile(const std::string &filename) const; // print from txt file
		void printAlert(const std::string &s, const int &type = 0) const; // 0 - red (error), 1 - yellow (damage/neutral), 2 - green (good stuff like healing)
		void printInit() const; // print at beginning of the game
		void printHelp() const; // print help
		void printStartTurn() const; // print at start of turn
		void printMinion(Minion * minion) const; // print minion
		void printHand() const; // print the hand
		void printBoard() const; // print the board
		void printBuff(Player * player, const int &n) const;
		void printBuff(Minion * minion, const int &att, const int &def) const;

	friend std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& v);
	friend std::ostream& operator<<(std::ostream& os, const std::vector<card_template_t>& temps);
};

std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& v);
std::ostream& operator<<(std::ostream& os, const std::vector<card_template_t>& temps);

#endif
