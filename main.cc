#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include "game.h"
#include "view.h"
#include "exceptions.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

int main(int argc, char *argv[]){
	std::istream * infile = &cin;
	std::string p1deckname = "default.deck";
	std::string p2deckname = "default.deck";
	std::string p1name = "Player";
	std::string p2name = "Player";
	bool testing = false;
	for(int i = 1; i < argc; i++){
		std::string arg{argv[i]};
		if(arg == "-init"){
			if(i == argc-1 || infile != &cin){
				cerr << "Invalid use of -init." << endl;
				return -1;
			} 
			std::string filename{argv[++i]};
			std::ifstream * temp = new std::ifstream;
			temp->exceptions(std::ifstream::failbit | std::ifstream::badbit);
			try{
				temp->open(filename);
				infile = temp;
			} catch (std::ifstream::failure &e){
				delete temp;
				cerr << "Problem opening init file " << filename << endl;
				return -1;
			}
		}else if(arg == "-testing"){
			testing = true;
		}else if(arg == "-deck1"){
			if(i == argc-1){
				cerr << "Invalid use of -deck1." << endl;
				return -1;
			}
			p1deckname = argv[++i];
		}else if(arg == "-deck2"){
			if(i == argc-1){
				cerr << "Invalid use of -deck2." << endl;
				return -1;
			}
			p2deckname = argv[++i];
		}
	}
	
	infile->exceptions(std::ios_base::eofbit);

	try{
		cout << "Enter name of player 1: ";
		*infile >> p1name;
		cout << "Enter name of player 2: ";
		*infile >> p2name;
		infile->ignore(10000, '\n');
	}catch(std::ifstream::failure &e){
		cerr << "Invalid player names. Continuing with defaults:" << endl;
		p1name = "Player 1";
		p2name = "Player 2";
	}

	try{
		Game game{p1name, p2name, p1deckname, p2deckname, testing}; // can fail to load decks
		std::string s;
		while (true){
			try {
				if(infile == &cin){
					cout << "\033[1;32m > ";
				}
				std::getline(*infile, s);	
				if(infile == &cin){
					cout << "\033[0m";
				}
				std::istringstream iss{s};
				std::string cmd;
				iss >> cmd;
				if(cmd == "help"){
					game.displayHelp();			
				}else if(cmd == "end"){
					game.endTurn();
				}else if(cmd == "quit"){
					game.endGame();
				}else if(cmd == "attack"){
					int pos, t;
					if(iss >> pos){
						if(iss >> t){
							game.attack(pos-1, t-1);
						}else{
							game.attack(pos-1);
						}
					}else{
						throw InvalidCommand{};
					}
				}else if(cmd == "play"){
					int pos, pnum;
					char target;
					if(iss >> pos){
						if(iss >> pnum){
							if(iss >> target){
								if(target >= '1' && target <= '5') target--;
								game.play(pos-1, pnum, target);
							}else{
								throw InvalidCommand{};
							}
						}else{
							game.play(pos-1);
						}
					}else{
						throw InvalidCommand{};
					}
				}else if(cmd == "use"){
					int pos, pnum, target;
					if(iss >> pos){
						if(iss >> pnum){
							if(iss >> target){
								game.use(pos-1, pnum, target-1);
							}else{
								throw InvalidCommand{};
							}
						}else{
							game.use(pos-1);
						}
					}else{
						throw InvalidCommand{};
					}
				}else if(cmd == "inspect"){
					int pos;
					if(iss >> pos){
						game.displayMinion(pos-1);
					}else{
						throw InvalidCommand{};
					}
				}else if(cmd == "hand"){
					game.displayHand();
				}else if(cmd == "board"){
					game.displayBoard();
				}else if(cmd == "draw" && testing){
					game.draw();
				}else if(cmd == "discard" && testing){
					int pos;
					if(iss >> pos){
						game.discard(pos-1);
					}else{
						throw InvalidCommand{};
					}
				}else{
					throw InvalidCommand{};
				}
			}catch(GameOver){
				break;
			}catch(GameException &e){
				game.printAlert(e.getErr());
				if(e.getDoExit()){
					break;
				}
			}catch(std::ifstream::failure &e){
				break;
			}
		}
	}catch(DeckError &e){
		if(infile != &cin){
			delete infile;
		}
		cerr << "A deck error has occured." << endl;
		cout << "\033[0m\n";
		return -1;
	}catch(std::exception &e){
		if(infile != &cin){
			delete infile;
		}
		cerr << "An error occured: " << e.what() << endl;
		cout << "\033[0m\n";
		return -1;
	}

	if(infile != &cin){
		delete infile;
	}
	
	cout << "\033[0m\n";
	return 0;
}
