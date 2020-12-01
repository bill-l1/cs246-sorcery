#include <string>
#include <memory>
#include <map>
#include "player.h"
#include "card.h"

using namespace std;

Card::Card() {}

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

unique_ptr<Card> CardFactory::getCard(const string &name){
	unique_ptr<Card> card = make_unique<Card>();
	card.get()->name = name;
	return move(card); //TODO mapping
}
