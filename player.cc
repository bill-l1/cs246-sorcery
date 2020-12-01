#include "player.h"
#include <string>
#include <memory>
#include <stack>
#include <fstream>

using namespace std;

Player::Player(const string &name, stack<unique_ptr<Card>> deck)
	: name{name},
	life{20},
	magic{3},
	deck{move(deck)}
{
	for(int i = 0; i < 4; i++){
		draw();
	}
}

string Player::getName() const {
	return name;
}

int Player::getLife() const {
	return life;
}

int Player::getMagic() const {
	return magic;
}

int Player::getDeckSize() const {
	return deck.size();
}

int Player::getHandSize() const {
	return hand.size();
}

int Player::getBoardSize() const {
	return board.size();
}

void Player::draw() {
	if(!deck.empty() && hand.size() < 5){
		hand.push_back(move(deck.top()));
		deck.pop();
	}else{
		//TODO add exception
	}
}
