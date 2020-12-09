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
	turns = 1;
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
	}else{
		std::reverse(cardNames.begin(), cardNames.end());
	}

	for(auto cardName : cardNames){
		deck.push(std::move(CardFactory::getCard(cardName, owner)));
	} 

	return std::move(deck);	
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
	std::vector<Player *> players{p1.get(), p2.get()};
	for(auto &p : players){
		for(auto it = p->board.begin(); it != p->board.end();){
			if((*it)->getDefense() <= 0){
				view->printAlert((*it)->getMinionName() + " was destroyed.", 1);
				(*it)->onDeath();
				Minion * bm = (*it)->getBase();
				it->release();
				it->reset(bm);
				p->graveyard.push(std::move(*it));
				p->board.erase(it);
			}else{
				++it;
			}
		}

		if(p->getLife() <= 0){
			view->printAlert("Game over!", 2);
			//end game
		}
	}
}

Player * Game::getP1() const {
	return p1.get();
}

Player * Game::getP2() const {
	return p2.get();
}

Player * Game::getActivePlayer() const {
	return activePlayer.get();
}

Player * Game::getNonActivePlayer() const {
	return nonActivePlayer.get();
}

int Game::getTurns() const{
	return turns;
}

void Game::endTurn(){
	for(auto && minion : activePlayer.get()->board){
	minion->onEndTurn();
	}
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
	view->printHelp();
}

void Game::displayMinion(const int &pos) const {
	if(pos < activePlayer->getBoardSize()){
		view->printMinion(activePlayer->board[pos].get());
	}else{
		view->printAlert("Invalid selection.");
		//TODO exception
	}
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
		std::unique_ptr<Card> card = std::move(activePlayer->hand[pos]);
		activePlayer->hand.erase(activePlayer->hand.begin()+pos);
		if(auto cast = dynamic_cast<BaseMinion *>(card.get())){
			view->printAlert(activePlayer->getName()+" summons "+card->getName()+"!", 2);
			std::unique_ptr<BaseMinion> cast_card;
			card.get()->setGame(this);
			card.release(); // if this causes a leak im finna lose it
			cast_card.reset(cast); //prob set up a helper function for this.
			activePlayer->playCard(std::move(cast_card));
			for(auto && minion : activePlayer.get()->board){
				minion->onAllyPlay();
			}
			for(auto && minion : nonActivePlayer.get()->board){
				minion->onEnemyPlay();
			}
			if(activePlayer.get()->ritual != nullptr) {
				activePlayer.get()->ritual->onAllyPlay();
			}
			if(nonActivePlayer.get()->ritual != nullptr) {
				nonActivePlayer.get()->ritual->onEnemyPlay();
			}	

		}else if(auto cast = dynamic_cast<Ritual*>(card.get())) {
			std::unique_ptr<Ritual> cast_card;
			card.get()->setGame(this);
			card.release(); // if this causes a leak im finna lose it
			cast_card.reset(cast); //prob set up a helper function for this.
			activePlayer->playCard(move(cast_card));


		}else{ //TODO add other card types
			view->printAlert("Invalid card type.");
			//exception handling
		}
		update(); //TODO move to play effects loop
	}else{
		view->printAlert("Invalid selection.");
		//TODO exception
	}
}

void Game::play(const int &pos, const int &pnum, const char &t){
	int t2 = 9999;
	Card * target = nullptr;
	std::vector<Player *> players{p1.get(), p2.get()};

	if(t >= '0' && t <= '4'){
		t2 = t - 48;
		target = players[pnum-1]->board[t2].get();
	}else if (t == 'r'){
		target = players[pnum-1]->ritual.get();
	}else{
		view->printAlert("Invalid target");
		return;
	}

	if(pos < activePlayer->getHandSize()){
		if((pnum == 1 && p1->board.size() <= t2) || (pnum == 2 && p2->board.size() <= t2) || pnum > 2) {
			view->printAlert("Invalid target");
			return;
		}

		std::unique_ptr<Ritual>& r_target = players[pnum-1]->ritual;
		//create target for ritual TODO

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
		std::unique_ptr<Card> card = std::move(activePlayer->hand[pos]);
		activePlayer->hand.erase(activePlayer->hand.begin()+pos);
		
		if(auto cast = dynamic_cast<Spell *>(card.get())){
			view->printAlert(activePlayer->getName()+" casts "+card->getName()+"!", 2);
			std::unique_ptr<Spell> cast_card;
			card.release(); 
			cast_card.reset(cast); 
			activePlayer->playCard(std::move(cast_card), target);	
		}else if(auto cast = dynamic_cast<Enchantment *>(card.get())){
			//TODO verify minion target
			std::unique_ptr<Minion>& m_target = players[pnum-1]->board[t2];
			view->printAlert(activePlayer->getName()+" enchants "+m_target->getMinionName()+" with "+card->getName()+"!", 2);
			std::unique_ptr<Enchantment> cast_card;
			// std::unique_ptr<Minion> t_ref = (std::unique_ptr<Minion>&) target;
			card.release(); 
			cast_card.reset(cast); 
			activePlayer->playCard(std::move(cast_card), m_target);	
		}else{ 
			view->printAlert("Invalid card type.");
			//exception handling
		}
		
		update(); //TODO move to play effects loop
	}else{
		view->printAlert("Invalid selection.");
		//TODO exception
	}
}


void Game::attack(const int &pos){
	if(pos < activePlayer->getBoardSize()){
		Minion * minion = activePlayer->board[pos].get();
		view->printAlert(minion->getName()+" attacks "+nonActivePlayer->getName()+"!", 1);
		buff(nonActivePlayer.get(), -minion->getAttack());
		update();
	}else{
		view->printAlert("Invalid selection.");
	}
}

void Game::attack(const int &pos, const int &t){
	if(pos < activePlayer->getBoardSize() && t < nonActivePlayer->getBoardSize()){
		Minion * minion = activePlayer->board[pos].get();
		Minion * other = nonActivePlayer->board[t].get();
		view->printAlert(minion->getMinionName() + " attacks " + other->getMinionName()+"!", 1);
		view->printBuff(minion, 0, -other->getAttack());
		view->printBuff(other, 0, -minion->getAttack());
		minion->attackOther(other);
		update();
	}else{
		view->printAlert("Invalid selection.");
	}
}

void Game::buff(Player * player, const int &n){
	player->setLife(player->getLife()+n);
	view->printBuff(player, n);
}

void Game::buff(Minion * minion, const int &att, const int &def){
	minion->buff(att, def);
	view->printBuff(minion, att, def);
}
