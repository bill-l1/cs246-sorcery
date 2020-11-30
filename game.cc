#include "game.h"
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

Game::Game(const string &p1name, const string &p2name, const string &p1deckname, const string &p2deckname)
{
	p1 = make_shared<Player>(p1name);
	p2 = make_shared<Player>(p2name);
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

void Game::startTurn(){
	view.get()->printStartTurn();
}

void Game::displayHelp() const{
	view.get()->printHelp();
}
