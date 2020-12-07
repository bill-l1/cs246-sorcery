#include <string>
#include "card.h"

Card::Card(const std::string &name, const std::string &description, const int &cost, const std::string &type)
	: name{name},
	description{description},
	cost{cost},
	type{type}
{}

Card::~Card() {}

std::string Card::getName() const {
	return name;
}
std::string Card::getType() const {
	return type;
}
std::string Card::getDescription() const {
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

