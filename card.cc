#include <string>
#include <memory>
#include <map>
#include "player.h"
#include "card.h"

using namespace std;

Card::Card(const string &name)
	: name{name}
{}
string Card::getName() const {
	return name;
}
string Card::getType() const {
	return type;
}
string Card::getDescription() const {
	return description;
}
int Card::getCost() const {
	return cost;
}
Player * Card::getOwner() const {
	return owner;
}
void Card::setOwner(Player * player) {
	owner = player;
}

