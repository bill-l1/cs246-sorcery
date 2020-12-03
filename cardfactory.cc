#include <memory>
#include <iostream>
#include "cardfactory.h"
#include "base_minion.h"

//build card based off input class
template<class T>
std::unique_ptr<Card> CardFactory::buildCard(){ 
	return std::make_unique<T>();
}

// return a std::unique_ptr of a card from a card name and owner
// uses FUNC_MAP to map strings to cards
std::unique_ptr<Card> CardFactory::getCard(const std::string &name, Player * owner){	
	std::unique_ptr<Card> card;
	if(FUNC_MAP.count(name)){
		card = FUNC_MAP[name]();
	}else{
		std::cerr << "Card " << name << " not found." << std::endl;
		card = std::make_unique<BaseMinion>("???", "Invalid card", 4, 7, 7);
		// TODO possibly throw exception later
	}
	card->setOwner(owner);
	return move(card); //TODO mapping
}

//map strings from deck file to template method
std::map<std::string, build_ptr> CardFactory::FUNC_MAP{
	// Minions
	{"Air Elemental", &CardFactory::buildCard<MinionList::AirElemental>},
	{"Earth Elemental", &CardFactory::buildCard<MinionList::EarthElemental>},
	{"Bomb", &CardFactory::buildCard<MinionList::Bomb>},
	{"Fire Elemental", &CardFactory::buildCard<MinionList::FireElemental>},
	{"Potion Seller", &CardFactory::buildCard<MinionList::PotionSeller>},
	{"Novice Pyromancer", &CardFactory::buildCard<MinionList::NovicePyromancer>},
	{"Apprentice Summoner", &CardFactory::buildCard<MinionList::ApprenticeSummoner>},
	{"Master Summoner", &CardFactory::buildCard<MinionList::MasterSummoner>},

	// Spells

	// Enchantments

	// Rituals

};