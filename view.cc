#include <iostream>
#include <iomanip>
#include <fstream>
#include "view.h"

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
