#include "game.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <memory>

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
	draw();
}

stack<unique_ptr<Card>> Game::loadDeck(const bool &doShuffle) const {
	
	ifstream f("default.deck"); // TODO make exception safe
	stack<unique_ptr<Card>> deck;
	string s;
	while(getline(f, s)) {
		auto p = make_unique<Card>(s);
		deck.push(move(p));
	}
	return move(deck);	
}
