#include <memory>
#include <iostream>
#include "cardfactory.h"
#include "base_minion.h"
#include "exceptions.h"

//build card based off input class
template<class T>
std::unique_ptr<Card> CardFactory::buildCard(){ 
	return std::make_unique<T>();
}

// return a std::unique_ptr of a card from a card name and owner
// uses FUNC_MAP to map strings to cards
// throws InvalidCard if card is not found in FUNC_MAP
std::unique_ptr<Card> CardFactory::getCard(const std::string &name, Player * owner){	
	std::unique_ptr<Card> card;
	if(FUNC_MAP.count(name)){
		card = FUNC_MAP[name]();
	}else{
		// card = std::make_unique<BaseMinion>("???", "Invalid card", 4, 7, 7);
		throw InvalidCard{name};
	}
	card->setOwner(owner);
	return std::move(card);
}

//map strings from a deck file to template method buildCard and return its associated class
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
	{"Banish", &CardFactory::buildCard<SpellList::Banish>},
	{"Blizzard", &CardFactory::buildCard<SpellList::Blizzard>},
	{"Disenchant", &CardFactory::buildCard<SpellList::Disenchant>},
	{"Recharge", &CardFactory::buildCard<SpellList::Recharge>},
	{"Raise Dead", &CardFactory::buildCard<SpellList::RaiseDead>},
	{"Unsummon", &CardFactory::buildCard<SpellList::Unsummon>},
	
	// Enchantments
	{"Giant Strength", &CardFactory::buildCard<EnchantmentList::GiantStrength>},
	{"Enrage", &CardFactory::buildCard<EnchantmentList::Enrage>},
	{"Delay", &CardFactory::buildCard<EnchantmentList::Delay>},
	{"Magic Fatigue", &CardFactory::buildCard<EnchantmentList::MagicFatigue>},
	{"Silence", &CardFactory::buildCard<EnchantmentList::Silence>},
	
	// Rituals
	{"Aura of Power", &CardFactory::buildCard<RitualList::AuraOfPower>},
	{"Standstill", &CardFactory::buildCard<RitualList::Standstill>},
	{"Dark Ritual", &CardFactory::buildCard<RitualList::DarkRitual>}

};
