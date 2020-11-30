#ifndef VIEW_H
#define VIEW_H

#include <vector>
#include "game.h"

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
const std::string _GREEN = "\033[32m";
const std::string _YELLOW = "\033[33m";
const std::string _RESET = "\033[0m";

const std::string _YELLOWBG = "\033[43m";
const std::string _WHITEBG = "\033[47m";

class View {
	Game * game;
	void seperator() const;
	public:
		View(Game * game);
		void printFromFile(const std::string &filename) const;
		void printInit() const;
		void printHelp() const;
		void printStartTurn() const;
//		void printBoard() const;
//		void printHand() const;
//		void printMinion() const; TODO
};

#endif
