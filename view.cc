#include <iostream>
#include <iomanip>
#include <fstream>
#include "view.h"
#include "game.h"
#include "card.h"
#include "player.h"
#include "minion.h"

using namespace std;

View::View(Game * game) : game{game}
{}

void View::seperator() const {
	cout << "\n" << setfill('=') << setw(80) << "=\n" << endl;
}

void View::printFromFile(const string &filename) const {
	ifstream infile;
	infile.exceptions(ifstream::failbit | ifstream::badbit);
	
	try{
		infile.open(filename);
	} catch (ifstream::failure e){
		cerr << _RED << "Problem opening file " << filename << _RESET << endl;
	}

	try{	
		string s;
		while(getline(infile, s)){
			cout << s << endl;
		}
	} catch (...){}
}

void View::printAlert(const string &s) const {
	cerr << _RED_BG << " !  " << s << "  ! "<< _RESET << endl;
}

void View::printInit() const {
	seperator();
	cout << _YELLOW;
	printFromFile("sorceryLogo.txt");
	cout << _RESET << endl;
}

void View::printHelp() const {
	seperator();
	cout << "Commands:" << endl;
	for(auto vec : _COMMANDS){
		cout << _GREEN << "\t" << vec[0] << _RESET << " -- " << vec[1] << endl;
	}
	seperator();
}

void View::printStartTurn() const {
	seperator();
	cout << "Turn #" << game->getTurns() << endl;
	cout << "Active player:" << game->getActivePlayer()->getName() << endl;
	seperator();
}

void View::printHand() const {
	seperator();
	
	for(auto && card : game->getActivePlayer()->hand){
		cout << "Card: " << card->getName() << endl;
	}
	seperator();
}

void View::printBoard() const {
	seperator();
	cout << "Player 1: " << game->getP1()->getName() << endl;
	cout << _RED <<  game->getP1()->getLife() << " HP " << _BLUE <<  game->getP1()->getMagic() << " MP" << _RESET << endl << endl;
	for(auto && card : game->getP1()->board){
		cout << (&card - &game->getP1()->board[0]) << " - Minion: " << card->getName() << "\t" << _GREEN << card->getAttack() << _RESET << "/" << _YELLOW << card->getDefense() << _RESET << "\t" << card->getDescription().substr(0, 40) << endl;
	}
	cout << "\nPlayer 2: " << game->getP2()->getName() << endl;
	cout << _RED << game->getP2()->getLife() << " HP " << _BLUE <<  game->getP2()->getMagic() << " MP" << _RESET <<  endl << endl;
	for(auto && card : game->getP2()->board){
		cout << (&card - &game->getP2()->board[0]) << " - Minion: " << card->getName() << "\t" << _GREEN << card->getAttack() << _RESET << "/" << _YELLOW << card->getDefense() << _RESET << "\t" << card->getDescription().substr(0, 40) << endl;
	}
	seperator();
}
