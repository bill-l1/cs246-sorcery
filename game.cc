#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <memory>
#include <algorithm>
#include <random>
#include <chrono>
#include <stdexcept>
#include "game.h"
#include "player.h"
#include "view.h"
#include "card.h"
#include "minion.h"
#include "base_minion.h"
#include "cardfactory.h"

Game::Game(const std::string &p1name, const std::string &p2name, const std::string &p1deckname, const std::string &p2deckname, const bool &testing)
{
	p1 = std::make_shared<Player>(p1name);
	p1->setDeck(std::move(loadDeck(p1deckname, !testing, p1.get())));
	p2 = std::make_shared<Player>(p2name);
	p2->setDeck(std::move(loadDeck(p2deckname, !testing, p2.get())));

	for(int i = 0; i < 4; i++){
		p1->draw();
		p2->draw();
	}

	view = std::make_unique<View>(this);
	activePlayer = p1;
	nonActivePlayer = p2;
	turns = 0;
	this->testing = testing;

	view->printInit();
	startTurn();
}

void Game::startTurn(){
	view.get()->printStartTurn();
	draw();
	activePlayer->setMagic(activePlayer->getMagic() + 1);
}

std::stack<std::unique_ptr<Card>> Game::loadDeck(const std::string &dname, const bool &doShuffle, Player * owner) const {
	std::ifstream f(dname); // TODO make exception safe
	std::stack<std::unique_ptr<Card>> deck;
	std::vector<std::string> cardNames;
	std::string s;

	while(std::getline(f, s)) {
		cardNames.push_back(s);	
	}
	if(doShuffle){
		shuffleVector<std::string>(cardNames);
	}
	for(auto cardName : cardNames){
		deck.push(move(CardFactory::getCard(cardName, owner)));
	} 
	return move(deck);	
}

template <typename T>
void Game::shuffleVector(std::vector<T> & v) const {
	  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    for ( int i = 0; i < 1000; i++ ) {
        std::shuffle( v.begin(), v.end(), rng );
    }
}

void Game::update() {
	for(auto && minion : p1->board){
		if(minion->getDefense() <= 0){
			int index = &minion - &p1->board[0];
			p1->graveyard.push(std::move(minion)); //TODO account for enchantments later
			p1->board.erase(p1->board.begin()+index);
		}
	}

	for(auto && minion : p2->board){
		if(minion->getDefense() <= 0){
			int index = &minion - &p2->board[0];
			p2->graveyard.push(std::move(minion)); //TODO account for enchantments later
			p2->board.erase(p2->board.begin()+index);
		}
	}

	if(p1->getLife() <= 0){
		//end game
	}else if(p2->getLife() <= 0){
		//end game
	}
}

std::shared_ptr<Player> Game::getP1() const {
	return p1;
}

std::shared_ptr<Player> Game::getP2() const {
	return p2;
}

std::shared_ptr<Player> Game::getActivePlayer() const {
	return activePlayer;
}

std::shared_ptr<Player> Game::getNonActivePlayer() const {
	return nonActivePlayer;
}

int Game::getTurns() const{
	return turns;
}

void Game::endTurn(){
	std::swap(activePlayer, nonActivePlayer);
	turns++;
	startTurn();
}

void Game::draw(){
	//TODO exception handling thru verification functions
	activePlayer.get()->draw();
}

void Game::discard(const int &pos){
	if(pos < activePlayer->getHandSize()){
		activePlayer->hand.erase(activePlayer->hand.begin()+pos);
	}else{
		//TODO exception
	}
}
void Game::displayHelp() const{
	view->printHelp();
}

void Game::displayHand() const{
	view->printHand();
}

void Game::displayBoard() const {
	view->printBoard();
}

void Game::play(const int &pos){
	if(pos < activePlayer->getHandSize()){
		if(activePlayer->getMagic() < activePlayer->hand[pos]->getCost()){
			if(testing){
				activePlayer->setMagic(activePlayer->hand[pos]->getCost());
			}else{
				view->printAlert("Not enough magic to play.");
				return;
			}
			//TODO
		}

		activePlayer->setMagic(activePlayer->getMagic() - activePlayer->hand[pos]->getCost());
		
		std::unique_ptr<Card> card = move(activePlayer->hand[pos]);
		activePlayer->hand.erase(activePlayer->hand.begin()+pos);
		if(auto cast = dynamic_cast<BaseMinion *>(card.get())){
			std::unique_ptr<BaseMinion> cast_card;
			card.release(); // if this causes a leak im finna lose it
			cast_card.reset(cast); //prob set up a helper function for this.
			activePlayer->playCard(move(cast_card));	
		}
		else{ //TODO add other card types
			view->printAlert("Invalid card type.");
			//exception handling
		}
	}else{
		view->printAlert("Invalid selection.");
		//TODO exception
	}
}

void Game::play(const int &pos, const int &pnum, const char &t){
		int t2 = 9999;
		Card * target = nullptr;
		switch(t) {
		case '0':
			t2 = 0;
			break;
		case '1':
			t2 = 1;
			break;
		case '2':
			t2 = 2;
			break;
		case '3':
			t2 = 3;
			break;
		case '4':
			t2 = 4;
			break;
		}
		if(pos < activePlayer->getHandSize()){
		if(pnum == 1 && p1->board.size() > t2) {
		target = dynamic_cast<Card *>(p1->board[t2].get());

		}
		else if (pnum == 2 && p2->board.size() > t2) {
		target = dynamic_cast<Card *>(p2->board[t2].get());
		}
		else {
		view->printAlert("Invalid target");
		return;
		}
		if(activePlayer->getMagic() < activePlayer->hand[pos]->getCost()){
			if(testing){
				activePlayer->setMagic(activePlayer->hand[pos]->getCost());
			}else{
				view->printAlert("Not enough magic to play.");
				return;
			}
			//TODO
		}
		activePlayer->setMagic(activePlayer->getMagic() - activePlayer->hand[pos]->getCost());
		unique_ptr<Card> card = move(activePlayer->hand[pos]);
		activePlayer->hand.erase(activePlayer->hand.begin()+pos);
		if(auto cast = dynamic_cast<Spell *>(card.get())){
			unique_ptr<Spell> cast_card;
			card.release(); // if this causes a leak im finna lose it
			cast_card.reset(cast); //prob set up a helper function for this.
			activePlayer->castSpell(move(cast_card),target);	
		}
		else{ //TODO add other card types
			view->printAlert("Invalid card type.");
			//exception handling
		}
	}else{
		view->printAlert("Invalid selection.");
		//TODO exception
	}
}


void Game::attack(const int &pos){
	if(pos < activePlayer->getHandSize()){
		Minion * minion = activePlayer->board[pos].get();
		view->printAlert(minion->getName()+" attacks "+nonActivePlayer->getName()+"!", 1);
		buff(nonActivePlayer.get(), -minion->getAttack());
		
		update();
	}else{
		view->printAlert("Invalid selection.");
	}
}

void Game::attack(const int &pos, const int &t){
	//TODO
}

void Game::buff(Player * player, const int &n){
	std::string name = player->getName();
	player->setLife(player->getLife()+n);
	if(n > 0){
		view->printAlert(name+" healed "+ std::to_string(abs(n)) +" damage!", 2);
	}else if (n < 0){
		view->printAlert(name+" took "+ std::to_string(abs(n)) +" damage!", 1);
	}else{
		view->printAlert(name+" took no damage.", 1);
	}
}

void Game::buff(Minion * minion, const int &att, const int &def){
	std::string owner = minion->getOwner()->getName();
	std::string name = minion->getName();
	if(att > 0){
		view->printAlert(owner+"'s "+name+" gained "+ std::to_string(abs(att)) +" attack!", 2);
	}else if (att < 0){
		view->printAlert(owner+"'s "+name+" lost "+ std::to_string(abs(att)) +" attack!", 1);
	}else{
		//view->printAlert(owner+"'s "+name+" took no damage.");
	}
	if(def > 0){
		view->printAlert(owner+"'s "+name+" gained "+ std::to_string(abs(def)) +" defense!", 2);
	}else if (att == 0 && def < 0){
		view->printAlert(owner+"'s "+name+" took "+ std::to_string(abs(def)) +" damage!", 1);
	}else if (def < 0){
		view->printAlert(owner+"'s "+name+" lost "+ std::to_string(abs(def)) +" defense!", 1);
	}else if (att == 0) {
		view->printAlert(owner+"'s "+name+" took no damage.", 1);
	}else{
		//
	}
}