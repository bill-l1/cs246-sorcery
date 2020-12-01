#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "game.h"

using namespace std;


int main(int argc, char *argv[]){
	
	cin.exceptions(ios_base::eofbit);
	istream * infile = &cin;
	string p1deckname = "default.deck";
	string p2deckname = "default.deck";
	string p1name = "Player";
	string p2name = "Player";
	bool testing = false;
	for(int i = 1; i < argc; i++){
		string arg{argv[i]};
		if(arg == "-init"){
			if(i == argc-1 || infile != &cin){
				throw;
			}

			string filename{argv[++i]};
			ifstream * temp = new ifstream;
			temp->exceptions(ifstream::failbit | ifstream::badbit);

			try{
				temp->open(filename);
				infile = temp;
			} catch (ifstream::failure e){
				delete temp;
				cerr << "Problem opening file " << filename << endl;
			}
		}else if(arg == "-testing"){
			testing = true;
		}
	}
	

	string s;
	try{
		cout << "Enter name of player 1: ";
		cin >> p1name;
		cout << "Enter name of player 2: ";
		cin >> p2name;
		cin.ignore(1000, '\n');	
		Game game{p1name, p2name, p1deckname, p2deckname, testing};
		while (true){
			cout << "\033[1;32m > ";
			getline(*infile, s);	
			cout << "\033[0m";
			istringstream iss{s};
			
			string cmd;
			iss >> cmd;
			if(cmd == "help"){
				game.displayHelp();			
			}else if(cmd == "end"){
				game.endTurn();
			}else if(cmd == "quit"){
				break;
			}else if(cmd == "attack"){
			}else if(cmd == "play"){
			}else if(cmd == "use"){
			}else if(cmd == "inspect"){
			}else if(cmd == "hand"){
				game.displayHand();
			}else if(cmd == "board"){
			}else if(cmd == "draw" && testing){
				game.draw();
			}else if(cmd == "discard" && testing){
				int pos;
				iss >> pos;
				game.discard(pos);
			}else if(cmd == ""){
			}else{
				cerr << "Unrecognized command " << cmd << "!" << endl;
			}
		}
	}catch (...){
		if(infile != &cin){
			delete infile;
		}
	}
	
	cout << "\033[0m\n";
	return 0;
}
