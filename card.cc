#include <string>
#include <memory>
#include <map>
#include "card.h"

using namespace std;

Card::Card(const string &name, const string &description, const int &cost, const string &type)
	: name{name},
	description{description},
	cost{cost},
	type{type}
{}

Card::~Card() {}

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

