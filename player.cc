#include <string>
#include <memory>
#include <stack>
#include <iostream>
#include "player.h"
#include "minion.h"
#include "base_minion.h"
#include "enchantment.h"
#include "spell.h"
#include "ritual.h"
#include "exceptions.h"

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

Ritual * Player::getRitual() const {
	return ritual.get();
}

void Player::draw() {
	if(!deck.empty() && hand.size() < MAX_HAND_SIZE){
		hand.push_back(std::move(deck.top()));
		deck.pop();
	}else{
		throw HandIsFull{};
	}
}

void Player::playCard(std::unique_ptr<BaseMinion> card){
	if(board.size() < MAX_BOARD_SIZE){
		board.push_back(std::move(card));
	}else{
		throw BoardIsFull{};
	}
}

void Player::playCard(std::unique_ptr<Enchantment> card, std::unique_ptr<Minion> &target){
	Enchantment * enchant = card.release();
	enchant->setComponent(target.get()); // attach minion to enchant
	target.release();
	target.reset(enchant);
}

void Player::playCard(std::unique_ptr<Spell> card, Card * target) {
	card->getEffect()->setTarget(target);	
	card->getEffect()->run();
}

void Player::playCard(std::unique_ptr<Spell> card) {	
	card->getEffect()->run();
}

void Player::playCard(std::unique_ptr<Ritual> card) {
	this->ritual=std::move(card);
	this->ritual.get()->setOwner(this);
}

Minion * Player::getBoardNum(int num) const {
if(num >= this->getBoardSize()) {
return nullptr;
}	
return board[num].get();

}
