#include "player.h"
#include <string>
#include <memory>
#include <stack>

using namespace std;

Player::Player(const string &name)
	: name{name},
	life{20},
	magic{3}
{}

string Player::getName() const {
	return name;
}

int Player::getLife() const {
	return life;
}

int Player::getMagic() const {
	return magic;
}
