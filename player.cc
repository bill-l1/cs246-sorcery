#include <string>
#include <memory>
#include <stack>
#include <iostream>
#include "player.h"
#include "minion.h"
#include "base_minion.h"
#include "enchantment.h"

Player::Player(const std::string &name)
	: name{name},
	life{20},
	magic{3}
{}

std::string Player::getName() const {
	return name;
}

int Player::getLife() const {
	return life;
}

void Player::setLife(const int &n){
	life = n;
}

int Player::getMagic() const {
	return magic;
}

void Player::setMagic(const int &n){
	magic = n;
}

int Player::getDeckSize() const {
	return deck.size();
}

void Player::setDeck(std::stack<std::unique_ptr<Card>> d){
	deck = std::move(d);
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

void Player::playCard(std::unique_ptr<BaseMinion> card){
	if(board.size() < 5){
		board.push_back(std::move(card));
	}else{
		//TODO exception
	}
}

void Player::playCard(std::unique_ptr<Enchantment> card, std::unique_ptr<Minion> &target){
	Enchantment * enchant = card.release();
	enchant->setComponent(target.get()); // attach minion to enchant
	target.release();
	target.reset(enchant);
}

/*
void Player::playCard(unique_ptr<Card> card){
	cout << "wrong func" << endl;
}
*/
