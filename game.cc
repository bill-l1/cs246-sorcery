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

using namespace std;

Game::Game(const string &p1name, const string &p2name, const string &p1deckname, const string &p2deckname, const bool &testing)
{
	p1 = make_shared<Player>(p1name);
	p1->setDeck(move(loadDeck(p1deckname, !testing, p1.get())));
	p2 = make_shared<Player>(p2name);
	p2->setDeck(move(loadDeck(p2deckname, !testing, p2.get())));

	for(int i = 0; i < 4; i++){
		p1->draw();
		p2->draw();
	}

	view = make_unique<View>(this);
	activePlayer = p1;
	nonActivePlayer = p2;
	turns = 0;
	this->testing = testing;

	view->printInit();
	startTurn();
}

void Game::startTurn(){
	view.get()->printStartTurn();
}

stack<unique_ptr<Card>> Game::loadDeck(const string &dname, const bool &doShuffle, Player * owner) const {
	ifstream f(dname); // TODO make exception safe
	stack<unique_ptr<Card>> deck;
	vector<string> cardNames;
	string s;

	while(getline(f, s)) {
		cardNames.push_back(s);	
	}
	if(doShuffle){
		shuffleVector<string>(cardNames);
	}
	for(auto cardName : cardNames){
		deck.push(move(CardFactory::getCard(cardName, owner)));
	} 
	return move(deck);	
}

template <typename T>
void Game::shuffleVector(vector<T> & v) const {
	  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine rng{seed};
    for ( int i = 0; i < 1000; i++ ) {
        std::shuffle( v.begin(), v.end(), rng );
    }
}

void Game::update() {
	for(auto && minion : p1->board){
		if(minion->getDefense() <= 0){
			int index = &minion - &p1->board[0];
			p1->graveyard.push(move(minion)); //TODO account for enchantments later
			p1->board.erase(p1->board.begin()+index);
		}
	}

	for(auto && minion : p2->board){
		if(minion->getDefense() <= 0){
			int index = &minion - &p2->board[0];
			p2->graveyard.push(move(minion)); //TODO account for enchantments later
			p2->board.erase(p2->board.begin()+index);
		}
	}

	if(p1->getLife() <= 0){
		//end game
	}else if(p2->getLife() <= 0){
		//end game
	}
}

shared_ptr<Player> Game::getP1() const {
	return p1;
}

shared_ptr<Player> Game::getP2() const {
	return p2;
}

shared_ptr<Player> Game::getActivePlayer() const {
	return activePlayer;
}

shared_ptr<Player> Game::getNonActivePlayer() const {
	return nonActivePlayer;
}

int Game::getTurns() const{
	return turns;
}

void Game::endTurn(){
	swap(activePlayer, nonActivePlayer);
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
	view.get()->printHelp();
}

void Game::displayHand() const{
	view.get()->printHand();
}

void Game::startTurn(){
	view.get()->printStartTurn();
	draw();
	activePlayer->setMagic(activePlayer->getMagic() + 1);
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
		
		unique_ptr<Card> card = move(activePlayer->hand[pos]);
		activePlayer->hand.erase(activePlayer->hand.begin()+pos);
		if(auto cast = dynamic_cast<BaseMinion *>(card.get())){
			unique_ptr<BaseMinion> cast_card;
			card.release(); // if this causes a leak im finna lose it
			cast_card.reset(cast); //prob set up a helper function for this.
			activePlayer->playCard(move(cast_card));	
		}else{ //TODO add other card types
			view->printAlert("Invalid card type.");
			//exception handling
		}
	}else{
		view->printAlert("Invalid selection.");
		//TODO exception
	}
}

void Game::play(const int &pos, const int &pnum, const char &t){
	//TODO
}

void Game::attack(const int &pos){
	if(pos < activePlayer->getHandSize()){
		Minion * minion = activePlayer->board[pos].get();
		nonActivePlayer->setLife(nonActivePlayer->getLife() - minion->getAttack());
		update();
	}else{
		view->printAlert("Invalid selection.");
	}
}

void Game::attack(const int &pos, const int &t){
	//TODO
}
