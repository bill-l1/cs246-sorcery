#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "game.h"

#define MAX_HAND_SIZE 5
#define MAX_BOARD_SIZE 5

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
			if(i == argc-1 || infile != &cin) throw;

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
		}else if(arg == "-deck1"){
			if(i == argc-1) throw;
			p1deckname = argv[++i];
		}else if(arg == "-deck2"){
			if(i == argc-1) throw;
			p2deckname = argv[++i];
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
				int pos, t;
				iss >> pos;
				if(iss >> t){
					game.attack(pos, t);
				}else{
					game.attack(pos);
				}		
			}else if(cmd == "play"){
				int pos, pnum;
				iss >> pos;
				if(iss >> pnum){
					char target;
					iss >> target;
					game.play(pos, pnum, target);
				}else{
					game.play(pos);
				}
				//}catch(...){
					//TODO exception if play is invalid
					// -invalid target
					// -invalid placement
					// -invalid card played
					// -invalid way to play card (ex. no target on enchantment)
			//	}
			}else if(cmd == "use"){
			}else if(cmd == "inspect"){
			}else if(cmd == "hand"){
				game.displayHand();
			}else if(cmd == "board"){
				game.displayBoard();
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
