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
#include "exceptions.h"

extern const unsigned MAX_HAND_SIZE = 5;
extern const unsigned MAX_BOARD_SIZE = 5;
extern const unsigned INTIAL_HAND_SIZE = 4;
extern const unsigned MAX_ACTIONS = 1;

Game::Game(const std::string &p1name, const std::string &p2name, const std::string &p1deckname, const std::string &p2deckname, const bool &testing)
{
	p1 = std::make_shared<Player>(p1name);
	p1->setDeck(std::move(loadDeck(p1deckname, !testing, p1.get())));
	p2 = std::make_shared<Player>(p2name);
	p2->setDeck(std::move(loadDeck(p2deckname, !testing, p2.get())));

	try{
		for(unsigned i = 0; i < INTIAL_HAND_SIZE; i++){
			p1->draw();
		}
	}catch(HandIsFull){}

	try{
		for(unsigned i = 0; i < INTIAL_HAND_SIZE; i++){
			p2->draw();
		}
	}catch(HandIsFull){}

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
	try{
		draw();
	}catch(HandIsFull){
		printAlert("Can't draw card: hand is too full!");
	}
	activePlayer->setMagic(activePlayer->getMagic() + 1);

	for(auto && minion : activePlayer->board){
		minion->setActions(MAX_ACTIONS);
	}

	update();
}

std::stack<std::unique_ptr<Card>> Game::loadDeck(const std::string &dname, const bool &doShuffle, Player * owner) const {
	std::stack<std::unique_ptr<Card>> deck;
	std::vector<std::string> cardNames;
	try{
		std::ifstream f(dname);
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
	}catch (InvalidCard &e){
		if(dname == "default.deck"){
			printAlert("Cards not found in default deck. (this shouldn't be happening!!)");
			throw DeckError{};
		}else{
			printAlert("Deck "+dname+" contained invalid cards, trying default deck:");
			return std::move(loadDeck("default.deck", doShuffle, owner));
		}
	}catch (std::ifstream::failure &e){
		if(dname == "default.deck"){
			printAlert("Default deck couldn't be loaded (permissions error?)");
			throw DeckError{};
		}else{
			printAlert("Deck "+dname+" couldn't be loaded, trying default deck:");
			return std::move(loadDeck("default.deck", doShuffle, owner));
		}
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
				printAlert((*it)->getMinionName() + " was destroyed.", 1);
				if((*it)->onDeath() != nullptr) {
				(*it)->onDeath().get()->run();
				}
				Minion * bm = (*it)->getBase();
				it->release();
				it->reset(bm);
				bm->resetBoardRef();
				p->graveyard.push(std::move(*it));
				p->board.erase(it);
			}else{
				++it;
			}
		}

		if(p->getLife() <= 0){
			endGame(p);
		}
	}
}

// assumes pos is valid card in player's hand
std::unique_ptr<Card> Game::takeCardFromHand(Player * player, const int &pos) {
	std::unique_ptr<Card> card = std::move(activePlayer->hand[pos]);
	activePlayer->hand.erase(activePlayer->hand.begin()+pos);
	return std::move(card);
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
	for(auto && minion : activePlayer->board){
		if(minion->onEndTurn().get() != nullptr) {
			minion->onEndTurn().get()->run();
		}
		minion->setActions(0);
	}
	update();
	swap(activePlayer, nonActivePlayer);
	turns++;
	startTurn();
}

void Game::draw(){
	activePlayer.get()->draw();
}

void Game::discard(const int &pos){
	verifyHandPosition(activePlayer.get(), pos);
	activePlayer->hand.erase(activePlayer->hand.begin()+pos);
}
void Game::displayHelp() const{
	view->printHelp();
}

void Game::displayMinion(const int &pos) const {
	verifyBoardPosition(activePlayer.get(), pos);
	view->printMinion(activePlayer->board[pos].get());
}

void Game::displayHand() const{
	view->printHand();
}

void Game::displayBoard() const {
	view->printBoard();
}

void Game::play(const int &pos){
	verifyHandPosition(activePlayer.get(), pos);
	int newMagic = verifyMagicCost(activePlayer.get(), activePlayer->hand[pos]->getCost());
	std::unique_ptr<Card> &c_ref = activePlayer->hand[pos];

	if(auto cast = dynamic_cast<BaseMinion *>(c_ref.get())){
		verifyBoardNotFull(activePlayer.get());
		std::unique_ptr<Card> card = takeCardFromHand(activePlayer.get(), pos);
		activePlayer->setMagic(newMagic);
		printAlert(activePlayer->getName()+" summons "+card->getName()+"!", 2);
		std::unique_ptr<BaseMinion> cast_card;
		card->setGame(this);
		card.release(); // if this causes a leak im finna lose it
		cast_card.reset(cast); //prob set up a helper function for this.
		activePlayer->playCard(std::move(cast_card));
		for(auto && minion : activePlayer.get()->board){
			if(minion->onPlay() != nullptr) {
			minion->onPlay().get()->run();
			}
		}
		for(auto && minion : nonActivePlayer.get()->board){
			if(minion->onPlay() != nullptr) {
			minion->onPlay().get()->run();
			}
		}
		if(activePlayer.get()->ritual != nullptr) {
			if (activePlayer.get()->ritual->onPlay() != nullptr) {
			activePlayer.get()->ritual->onPlay()->run();
			}
		}
		if(nonActivePlayer.get()->ritual != nullptr) {
			if (nonActivePlayer.get()->ritual->onPlay() != nullptr) {
			nonActivePlayer.get()->ritual->onPlay()->run();
			}
		}	
	}else if(auto cast = dynamic_cast<Ritual*>(c_ref.get())) {
		std::unique_ptr<Card> card = takeCardFromHand(activePlayer.get(), pos);
		activePlayer->setMagic(newMagic);
		printAlert(activePlayer->getName()+" casts "+card->getName()+"!", 2);
		std::unique_ptr<Ritual> cast_card;
		card.get()->setGame(this);
		card.get()->setOwner(this->getActivePlayer());
		cast->getEffect()->setGame(this);
		card.release(); // if this causes a leak im finna lose it
		cast_card.reset(cast); //prob set up a helper function for this.
		activePlayer->playCard(std::move(cast_card));
	}
	else if(auto cast = dynamic_cast<Spell*>(c_ref.get())) {
		std::unique_ptr<Card> card = takeCardFromHand(activePlayer.get(), pos);
		activePlayer->setMagic(newMagic);
		printAlert(activePlayer->getName()+" casts "+card->getName()+"!", 2);
		std::unique_ptr<Spell> cast_card;
		card.get()->setGame(this);
		card.release(); // if this causes a leak im finna lose it
		cast_card.reset(cast); //prob set up a helper function for this.
		activePlayer->playCard(std::move(cast_card));
	}	
	
	else{ //TODO add non-targeted spells
		throw InvalidPlay{};
	}

	update();
}

void Game::play(const int &pos, const int &pnum, const char &t){
	int bt = t-48;
	Card * target = nullptr;
	std::vector<Player *> players{p1.get(), p2.get()};

	if(pnum != 1 && pnum != 2) throw InvalidPlayer{}; //validate pnum
	Player *pt = players[pnum-1]; 
	verifyHandPosition(activePlayer.get(), pos);

	if(t >= '0' && t <= '4'){
		verifyBoardPosition(pt, bt);
		target = pt->board[bt].get();
	}else if (t == 'r'){
		target = pt->ritual.get();
	}else{
		throw InvalidTarget{};
	}

	int newMagic = verifyMagicCost(activePlayer.get(), activePlayer->hand[pos]->getCost());
	std::unique_ptr<Card> &c_ref = activePlayer->hand[pos];

	if(auto cast = dynamic_cast<Spell *>(c_ref.get())){
		std::unique_ptr<Card> card = takeCardFromHand(activePlayer.get(), pos);
		activePlayer->setMagic(newMagic);
		card.get()->setGame(this);
		printAlert(activePlayer->getName()+" casts "+card->getName()+"!", 2);
		std::unique_ptr<Spell> cast_card;
		card.release(); 
		cast_card.reset(cast); 
		activePlayer->playCard(std::move(cast_card), target);
	}else if(auto cast = dynamic_cast<Enchantment *>(c_ref.get())){
		if (!dynamic_cast<Minion *>(target)) throw InvalidTarget{}; //validate target is a minion
		std::unique_ptr<Card> card = takeCardFromHand(activePlayer.get(), pos);
		activePlayer->setMagic(newMagic);
		std::unique_ptr<Minion>& m_target = pt->board[bt];
		printAlert(activePlayer->getName()+" enchants "+m_target->getMinionName()+" with "+card->getName()+"!", 2);
		std::unique_ptr<Enchantment> cast_card;
		card.release(); 
		cast_card.reset(cast); 
		activePlayer->playCard(std::move(cast_card), m_target);	
	}else{ 
		throw InvalidPlay{};
	}
	
	update();
}

void Game::attack(const int &pos){
	verifyBoardPosition(activePlayer.get(), pos);
	Minion * minion = activePlayer->board[pos].get();
	int cost = verifyActionCost(minion, 1);
	minion->setActions(cost);
	printAlert(minion->getMinionName()+" attacks "+nonActivePlayer->getName()+"!", 1);
	buff(nonActivePlayer.get(), -minion->getAttack());
	update();
}

void Game::attack(const int &pos, const int &t){
	verifyBoardPosition(activePlayer.get(), pos);
	verifyBoardPosition(nonActivePlayer.get(), t);
	Minion * minion = activePlayer->board[pos].get();
	Minion * other = nonActivePlayer->board[t].get();
	int cost = verifyActionCost(minion, 1);
	minion->setActions(cost);
	printAlert(minion->getMinionName() + " attacks " + other->getMinionName()+"!", 1);
	minion->buff(0, other->getAttack());
	other->buff(0, minion->getAttack());
	update();

}

void Game::use(const int &pos) {
	if(pos < activePlayer->getBoardSize()) {
	Minion * minion = activePlayer->board[pos].get();
	if(minion->getActivateCost() >= 0) {
		if(activePlayer->getMagic() >= minion->getActivateCost()) {
			int cost = verifyActionCost(minion, 1);
			minion->setActions(cost);
			minion->onActivate().get()->run();
			update();
		}
		else {
		view->printAlert("Not enough mana");
		}
	}
	else {
	view->printAlert("Invalid selection");
	}

	}
	else {
	view->printAlert("Invalid selection.");
	}

}


void Game::use(const int &pos, const int &pnum, const char &t){
	int bt = t-48;
	Card * target = nullptr;
	std::vector<Player *> players{p1.get(), p2.get()};

	if(pnum != 1 && pnum != 2) throw InvalidPlayer{}; //validate pnum
	Player *pt = players[pnum-1]; 
	verifyBoardPosition(activePlayer.get(), pos);

	if(t >= '0' && t <= '4'){
		verifyBoardPosition(pt, bt);
		target = pt->board[bt].get();
	}else if (t == 'r'){
		target = pt->ritual.get();
	}else{
		throw InvalidTarget{};
	}
	Minion * minion = activePlayer->board[pos].get();
	if(minion->getActivateCost() >= 0) {
		if(activePlayer->getMagic() >= minion->getActivateCost()) {
			int cost = verifyActionCost(minion, 1);
			minion->setActions(cost);
			minion->onActivate(target).get()->run();
			update();
		}
		else {
		view->printAlert("Not enough mana");
		}
	}
	else {
	view->printAlert("Invalid selection");
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

void Game::endGame(Player * winner){
	printAlert("Game over!", 2);
	if(winner == p1.get()){
		//TODO possible end screen improvements
		printAlert("** "+p1->getName()+" WINS! **", 2);
		throw GameOver{1};
	}else if(winner == p2.get()){
		printAlert("** "+p2->getName()+" WINS! **", 2);
		throw GameOver{2};
	}else{
		printAlert("No contest.", 1);
		throw GameOver{};
	}
}

void Game::verifyHandPosition(Player * player, const int &pos) const {
	if(pos >= player->getHandSize() || pos < 0){
		throw InvalidSelection{};
	}
}

void Game::verifyBoardPosition(Player * player, const int &pos) const {
	if(pos >= player->getBoardSize() || pos < 0){
		throw InvalidSelection{};
	}
}

void Game::verifyBoardNotFull(Player * player) const {
	if(player->getBoardSize() >= MAX_BOARD_SIZE){
		throw BoardIsFull{};
	}
}

int Game::verifyMagicCost(Player * player, const int &n) const {
	if(player->getMagic() < n){
		if(testing){
			return 0;
		}else{
			throw InsufficientMagic{};
		}
	}else{
		return player->getMagic() - n;
	}
}

int Game::verifyActionCost(Minion * minion, const int &n) const {
	if(minion->getActions() < n){
		if(testing){
			return 0;
		}else{
			throw InsufficientActions{};
		}
	}else{
		return minion->getActions() - n;
	}
}

void Game::printAlert(const std::string &s, const int &type) const {
	view->printAlert(s, type);
}

// void Game::disenchant(Player * player, Minion * target, Enchantment * e_target) {
// 	for(auto & minion : player->board){
// 		if(minion.get() == target){
// 			if(target == e_target){
// 				minion.release();
// 				minion.reset(target->getComponent());
// 			}else{
// 				//TODO
// 				// Minion * curr_minion = target;
// 				// while(curr_minion->getComponent() != nullptr){

// 				// }
// 			}
// 		}
// 	}
// }
