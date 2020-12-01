#include "game.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <memory>
#include <algorithm>
#include <random>
#include <chrono>
#include <stdexcept>

using namespace std;

Game::Game(const string &p1name, const string &p2name, const string &p1deckname, const string &p2deckname, const bool &testing)
{
	p1 = make_shared<Player>(p1name, loadDeck(testing));
	p2 = make_shared<Player>(p2name, loadDeck(testing));
	view = make_unique<View>(this);
	activePlayer = p1;
	nonActivePlayer = p2;
	turns = 0;

	view->printInit();
	startTurn();
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
	//TODO exception handling
	activePlayer.get()->draw();
}

void Game::discard(const int &pos){
	if(pos < activePlayer->getHandSize()){
		activePlayer->hand.erase(activePlayer->hand.begin()+pos);
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
}

stack<unique_ptr<Card>> Game::loadDeck(const bool &doShuffle) const {
	ifstream f("default.deck"); // TODO make exception safe
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
		deck.push(CardFactory::getCard(cardName));
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
