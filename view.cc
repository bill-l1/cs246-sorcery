#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <vector>
#include "view.h"
#include "game.h"
#include "card.h"
#include "player.h"
#include "minion.h"
#include "base_minion.h"
#include "enchantment.h"
#include "spell.h"
#include "ritual.h"
#include "ascii_graphics.h"

using std::cout;
using std::cerr;
using std::endl;

View::View(Game * game) : game{game}
{}

static std::string operator * (const std::string &s, const int &x);
std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& v);
std::ostream& operator<<(std::ostream& os, const std::vector<card_template_t>& temps);
static card_template_t display_any_card(Card * card);
static card_template_t display_any_minion(Minion * minion);
static card_template_t display_any_enchantment(Enchantment * enc);

void View::seperator() const {
	#if COOL_DRAWINGS == 1
		cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT * 168 << endl;
	#else
		cout << "" << std::setfill('=') << std::setw(167) << "=" << endl;
	#endif
}

void View::printFromFile(const std::string &filename) const {
	std::ifstream infile;
	infile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	
	try{
		infile.open(filename);
	} catch (std::ifstream::failure e){
		cerr << _RED << "Problem opening file " << filename << _RESET << endl;
	}

	try{	
		std::string s;
		while(std::getline(infile, s)){
			cout << s << endl;
		}
	} catch (...){}
}

void View::printAlert(const std::string &s, const int &type) const {
	if(type == 0){
		cerr << _RED_BG << "!  " << s << "  !"<< _RESET << endl;
	}else if(type == 1){
		cout << _YELLOW_BG << " " << s << " " << _RESET << endl;
	}else if(type == 2){
		cout << _GREEN_BG << " " << s << " " << _RESET << endl;
	}else{
		cout << s << endl;
	}
}

void View::printInit() const {
	seperator();
	cout << _YELLOW;
	printFromFile("sorceryLogo.txt");
	cout << _RESET << endl;
}

void View::printHelp() const {
	seperator();
	cout << "Commands:" << endl;
	for(auto vec : _COMMANDS){
		cout << _GREEN << "\t" << vec[0] << _RESET << " -- " << vec[1] << endl;
	}
	seperator();
}

void View::printStartTurn() const {
	seperator();
	cout << _BLUE_BG <<"- Turn #" << game->getTurns() << " -" << _RESET << endl;
	cout << _WHITE << "Current player: " << game->getActivePlayer()->getName() << _RESET << endl;
	cout << "Type " << _GREEN << "help" << _RESET << " for a list of commands" << endl;
	seperator();
}

void View::printMinion(Minion * minion) const {
	#if COOL_DRAWINGS == 1
		cout << display_any_minion(minion);
		Minion * curr_card = minion;
		std::vector<card_template_t> enchants;
		while(curr_card != nullptr && dynamic_cast<Enchantment *>(curr_card)){
			enchants.push_back(display_any_card(curr_card));
			curr_card = curr_card->getComponent();
		}
		std::vector<card_template_t> print_vec;
		while(!enchants.empty()){
			print_vec.push_back(enchants.back());
			enchants.pop_back();
			if(print_vec.size() == 5 || enchants.empty()){
				cout << print_vec;
				print_vec.clear();
			}
		}
	#else
		
	#endif
}

void View::printHand() const {
	#if COOL_DRAWINGS == 1
		if(!game->getActivePlayer()->hand.empty()){
			std::vector<card_template_t> hand;
			for(auto && card : game->getActivePlayer()->hand){
				hand.push_back(display_any_card(card.get()));
			}
			cout << hand;
		}else{
			printAlert("Your hand is empty.", 1);
		}
	#else
		seperator();
		for(auto && card : game->getActivePlayer()->hand){
			cout << "Card: " << card->getName() << endl;
		}
		seperator();
	#endif
}

void View::printBoard() const {
	#if COOL_DRAWINGS == 1
		std::vector<std::string> BD;
		for(unsigned i = 0; i < CARD_TEMPLATE_BORDER.size(); i++){
			BD.push_back(EXTERNAL_BORDER_CHAR_UP_DOWN);
		}

		card_template_t p1_card = display_player_card(1, game->getP1()->getName(), game->getP1()->getLife(), game->getP1()->getMagic());
		Ritual * p1_rptr = game->getP1()->getRitual();
		card_template_t p1_ritual = (p1_rptr != nullptr) ? 
			display_ritual(
				p1_rptr->getName(),
				p1_rptr->getCost(),
				0, //TODO
				p1_rptr->getDescription(),
				p1_rptr->getCharges()
			)
			: CARD_TEMPLATE_BORDER;
		card_template_t p1_graveyard = (game->getP1()->graveyard.size()) 
			? display_any_minion(game->getP1()->graveyard.top().get()) : CARD_TEMPLATE_BORDER;
		std::vector<card_template_t> r1 {BD, p1_ritual, CARD_TEMPLATE_EMPTY, p1_card, CARD_TEMPLATE_EMPTY, p1_graveyard, BD};
		std::vector<card_template_t> p1_board {BD};
		for(unsigned i = 0; i < 5; i++){
			if(i < game->getP1()->board.size()){
				Minion * m = game->getP1()->board[i].get();
				card_template_t m_temp = display_any_minion(m);
				if(m->getActions() > 0){
					for(auto & row : m_temp){
						row = _GREEN + row;
					}
				}
				p1_board.push_back(m_temp);
			}else{
				p1_board.push_back(CARD_TEMPLATE_BORDER);
			}
		}
		p1_board.push_back(BD);

		card_template_t p2_card = display_player_card(2, game->getP2()->getName(), game->getP2()->getLife(), game->getP2()->getMagic());
		Ritual * p2_rptr = game->getP2()->getRitual();
		card_template_t p2_ritual = (p2_rptr != nullptr) ? 
			display_ritual(
				p2_rptr->getName(),
				p2_rptr->getCost(),
				0, //TODO
				p2_rptr->getDescription(),
				p2_rptr->getCharges()
			) 
			: CARD_TEMPLATE_BORDER;
		card_template_t p2_graveyard = (game->getP2()->graveyard.size()) 
			? display_any_minion(game->getP2()->graveyard.top().get()) : CARD_TEMPLATE_BORDER;
		std::vector<card_template_t> r2 {BD, p2_ritual, CARD_TEMPLATE_EMPTY, p2_card, CARD_TEMPLATE_EMPTY, p2_graveyard, BD};
		
		std::vector<card_template_t> p2_board{BD};
		for(unsigned i = 0; i < 5; i++){
			if(i < game->getP2()->board.size()){
				Minion * m = game->getP2()->board[i].get();
				card_template_t m_temp = display_any_minion(m);
				if(m->getActions() > 0){
					for(auto & row : m_temp){
						row = _GREEN + row;
					}
				}
				p2_board.push_back(m_temp);
			}else{
				p2_board.push_back(CARD_TEMPLATE_BORDER);
			}
		}
		p2_board.push_back(BD);

		cout << EXTERNAL_BORDER_CHAR_TOP_LEFT << EXTERNAL_BORDER_CHAR_LEFT_RIGHT * 165 << EXTERNAL_BORDER_CHAR_TOP_RIGHT << endl;
		cout << r1 << p1_board << CENTRE_GRAPHIC << p2_board << r2;
		cout << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT << EXTERNAL_BORDER_CHAR_LEFT_RIGHT * 165 << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << endl;

	#else
		seperator();
		cout << "Player 1: " << game->getP1()->getName() << endl;
		cout << _RED <<  game->getP1()->getLife() << " HP " << _BLUE <<  game->getP1()->getMagic() << " MP" << _RESET << endl << endl;
		for(auto && card : game->getP1()->board){
			cout << (&card - &game->getP1()->board[0]) << " - Minion: " << ((card->getActions()>0) ? _WHITE : "") << card->getMinionName() << "\t" << _GREEN << card->getAttack() << _RESET << "/" << _YELLOW << card->getDefense() << _RESET << "\t" << card->getMinionDescription().substr(0, 40) << endl;
		}
		cout << "\nPlayer 2: " << game->getP2()->getName() << endl;
		cout << _RED << game->getP2()->getLife() << " HP " << _BLUE <<  game->getP2()->getMagic() << " MP" << _RESET <<  endl << endl;
		for(auto && card : game->getP2()->board){
			cout << (&card - &game->getP2()->board[0]) << " - Minion: " << ((card->getActions()>0) ? _WHITE : "") << card->getMinionName() << "\t" << _GREEN << card->getAttack() << _RESET << "/" << _YELLOW << card->getDefense() << _RESET << "\t" << card->getMinionDescription().substr(0, 40) << endl;
		}
		seperator();
	#endif
	
}

void View::printBuff(Player * player, const int &n) const {
	std::string name = player->getName();
	if(n > 0){
		printAlert(name+" healed "+ std::to_string(abs(n)) +" damage!", 2);
	}else if (n < 0){
		printAlert(name+" took "+ std::to_string(abs(n)) +" damage!", 1);
	}else{
		printAlert(name+" took no damage.", 1);
	}
}

void View::printBuff(Minion * minion, const int &att, const int &def) const {
	std::string owner = minion->getOwner()->getName();
	std::string name = minion->getMinionName();
	if(att > 0){
		printAlert(owner+"'s "+name+" gained "+ std::to_string(abs(att)) +" attack!", 2);
	}else if (att < 0){
		printAlert(owner+"'s "+name+" lost "+ std::to_string(abs(att)) +" attack!", 1);
	}

	if(def > 0){
		printAlert(owner+"'s "+name+" gained "+ std::to_string(abs(def)) +" defense!", 2);
	}else if (att == 0 && def < 0){
		printAlert(owner+"'s "+name+" took "+ std::to_string(abs(def)) +" damage!", 1);
	}else if (def < 0){
		printAlert(owner+"'s "+name+" lost "+ std::to_string(abs(def)) +" defense!", 1);
	}else if (att == 0) {
		printAlert(owner+"'s "+name+" took no damage.", 1);
	}
}

static std::string operator * (const std::string &s, const int &x){
	std::string new_s = "";
	for(int i = 0; i < x; i++){
		new_s += s;
	}
	return new_s;
}

std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& v){
	for(auto & row : v){
		os << row << endl;
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<card_template_t>& temps){
	std::vector<std::string> print_vec;
	for(auto & temp : temps){
		for(unsigned i = 0; i < temp.size(); i++){
			if(i >= print_vec.size()){
				print_vec.push_back(temp[i]);
			}else{
				print_vec[i] += temp[i];
			}
		}
	}

	return os << print_vec;
}

static card_template_t display_any_card(Card * card) {
	if(BaseMinion * cast = dynamic_cast<BaseMinion *>(card)){
		return display_any_minion(cast);
	}else if(Enchantment * cast = dynamic_cast<Enchantment *>(card)){
		return display_any_enchantment(cast);
	}else if(Spell * cast = dynamic_cast<Spell *>(card)){
		return display_spell(cast->getName(), cast->getCost(), cast->getDescription());
	}else if(Ritual * cast = dynamic_cast<Ritual *>(card)){
		//TODO FIX 0
		return display_ritual(cast->getName(), cast->getCost(), 0, cast->getDescription(), cast->getCharges());
	}else {
		return CARD_TEMPLATE_BORDER;
	}
	//TODO other card types
}

static card_template_t display_any_minion(Minion * minion){
	if(minion->getMinionDescription() != ""){
		if(minion->getActivateCost() < 0){
			return display_minion_triggered_ability(
				minion->getMinionName(),
				minion->getMinionCost(),
				minion->getAttack(),
				minion->getDefense(),
				minion->getMinionDescription()
			);
		}else{
			return display_minion_activated_ability(
				minion->getMinionName(),
				minion->getMinionCost(),
				minion->getAttack(),
				minion->getDefense(),
				minion->getActivateCost(),
				minion->getMinionDescription()
			);
		}
	}else{
		return display_minion_no_ability(
			minion->getMinionName(),
			minion->getMinionCost(),
			minion->getAttack(),
			minion->getDefense()
		);
	}
}

static card_template_t display_any_enchantment(Enchantment * enc){
	if(enc->getAttackStr() == "" && enc->getDefenseStr() == ""){
		return display_enchantment(
			enc->getName(), 
			enc->getCost(),
			enc->getDescription()
		);
	}else{
		return display_enchantment_attack_defence(
			enc->getName(), 
			enc->getCost(),
			enc->getDescription(),
			enc->getAttackStr(),
			enc->getDefenseStr()
		);
	}
}