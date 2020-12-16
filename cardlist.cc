#include <vector>
#include "cardlist.h"
#include "base_minion.h"
#include "spell.h"
#include "effectlist.h"

MinionList::AirElemental::AirElemental()
	: BaseMinion{
	"Air Elemental",
	"",
	0, 1, 1}
{}

MinionList::EarthElemental::EarthElemental()
	: BaseMinion{
	"Earth Elemental",
	"",
	3, 4, 4}
{}

MinionList::Bomb::Bomb()
	: BaseMinion{
	"Bomb",
	"Deals damage to all the opponent's minions equal to its attack value when it dies",
	2, 1, 2}
{}

std::vector<std::unique_ptr<Effect>> MinionList::Bomb::onDeath() {
if(this->getOwner() == this->getGame()->getNonActivePlayer()) {
std::unique_ptr<Effect> eff = std::make_unique<TeamBuff>(nullptr,this->getGame()->getActivePlayer()->getBoardNum(0),0,-this->getAttack());
		std::vector<std::unique_ptr<Effect>> base;
		base.push_back(std::move(eff));
		return base;
// return std::move(eff);
}

std::unique_ptr<Effect> eff2 = std::make_unique<TeamBuff>(nullptr,this->getGame()->getNonActivePlayer()->getBoardNum(0),0,-this->getAttack());
// return std::move(eff2);
std::vector<std::unique_ptr<Effect>> base;
		base.push_back(std::move(eff2));
		return base;


}

MinionList::FireElemental::FireElemental()
	: BaseMinion{
	"Fire Elemental",
	"Whenever an opponent's minion enters play, deal 1 damage to it",
	2, 2, 2}
{}


std::vector<std::unique_ptr<Effect>> MinionList::FireElemental::onPlay() {
	std::vector<std::unique_ptr<Effect>> base;
if(this->getOwner() == this->getGame()->getNonActivePlayer()) {
std::unique_ptr<Effect> eff = std::make_unique<SampleEffect>(nullptr,this->getGame()->getActivePlayer()->getBoardNum(this->getGame()->getActivePlayer()->getBoardSize()-1),0,-1);
// return std::move(eff);
		
		base.push_back(std::move(eff));
		return base;
}
return base;
// return nullptr;

}

MinionList::PotionSeller::PotionSeller()
	: BaseMinion{
	"Potion Seller",
	"At the end of your turn, all your minions gain +0/+1",
	2, 1, 3,-1}
{}

std::vector<std::unique_ptr<Effect>> MinionList::PotionSeller::onEndTurn() {
	std::unique_ptr<Effect> eff = std::make_unique<TeamBuff>(nullptr,this->getGame()->getActivePlayer()->getBoardNum(0),0,1);
			std::vector<std::unique_ptr<Effect>> base;

	if (this->getOwner() != this->getGame()->getActivePlayer()) {
	// return nullptr;
		return base;
	}
	eff.get()->setGame(this->getGame());
	base.push_back(std::move(eff));
	return base;
	// return std::move(eff);
}

MinionList::NovicePyromancer::NovicePyromancer()
	: BaseMinion{
	"Novice Pyromancer",
	"Deal 1 damage to target minion",
	1, 0, 1, 1}
{}


std::vector<std::unique_ptr<Effect>> MinionList::NovicePyromancer::onActivate(Card * target) {
	std::unique_ptr<Effect> eff = std::make_unique<SampleEffect>(nullptr,target,0,-1);
	eff.get()->setGame(this->getGame());
	std::vector<std::unique_ptr<Effect>> base;
	base.push_back(std::move(eff));
	return base;
	// return std::move(eff);

}

MinionList::ApprenticeSummoner::ApprenticeSummoner()
	: BaseMinion{
	"Apprentice Summoner",
	"Summon a 1/1 air elemental",
	1, 1, 1, 1}
{}


std::vector<std::unique_ptr<Effect>> MinionList::ApprenticeSummoner::onActivate(Card * target) {
	std::unique_ptr<Effect> eff = std::make_unique<SummonEffect>(nullptr,nullptr,1);
	eff.get()->setGame(this->getGame());
	std::vector<std::unique_ptr<Effect>> base;
	base.push_back(std::move(eff));
	return base;
	// return std::move(eff);

}

MinionList::MasterSummoner::MasterSummoner()
	: BaseMinion{
	"Master Summoner",
	"Summon up to three 1/1 air elementals",
	3, 2, 2, 2}
{}

std::vector<std::unique_ptr<Effect>> MinionList::MasterSummoner::onActivate(Card * target) {
	std::unique_ptr<Effect> eff = std::make_unique<SummonEffect>(nullptr,nullptr,3);
	eff.get()->setGame(this->getGame());
	std::vector<std::unique_ptr<Effect>> base;
	base.push_back(std::move(eff));
	return base;
	// return std::move(eff);

}



EnchantmentList::GiantStrength::GiantStrength()
	: Enchantment{
	"Giant Strength",
	"",
	1, "+2", "+2"}
{}

EnchantmentList::Enrage::Enrage()
	: Enchantment{
	"Enrage",
	"",
	1, "*2", "-2"}
{}

EnchantmentList::Delay::Delay()
	: Enchantment{
	"Delay",
	"Enchanted minion does not gain an action on their next turn. This enchantment is automatically destroyed after 1 turn",
	2},
	toDestroy{false}
{}

std::vector<std::unique_ptr<Effect>> EnchantmentList::Delay::onEndTurn(){
	if(toDestroy){
		std::vector<std::unique_ptr<Effect>> v = component->onEndTurn();
		v.push_back(std::make_unique<DisenchantEffect>(getOwner(), getBoardRef(), this));
		return v;
		// return std::make_unique<DisenchantEffect>(getOwner(), getBoardRef(), this);
	}else{
		toDestroy = true;
		// return std::move(component->onEndTurn());
		return component->onEndTurn();
	}
}

int EnchantmentList::Delay::getActions() const{
	if(!toDestroy){
		return component->getActions();
	}else{
		return 0;
	}
}

EnchantmentList::MagicFatigue::MagicFatigue()
	: Enchantment{
	"Magic Fatigue",
	"Enchanted minion's activated ability costs 2 more",
	0}
{}

int EnchantmentList::MagicFatigue::getActivateCost() const {
	return component->getActivateCost() + 2;
}

EnchantmentList::Silence::Silence()
	: Enchantment{
	"Silence",
	"Enchanted minion cannot use abilities",
	1}
{}


int EnchantmentList::Silence::getActivateCost() const {
	return -1;
}

std::vector<std::unique_ptr<Effect>> EnchantmentList::Silence::onActivate(Card * target)  {
	std::vector<std::unique_ptr<Effect>> empty;
	return empty;
}

SpellList::Banish::Banish()
	:Spell {
	"Banish",
	"Destroy Target Minion or Ritual", 2, nullptr}
{}

std::vector<std::unique_ptr<Effect>> SpellList::Banish::onPlay(Card * target) {
	std::unique_ptr<Effect> eff = std::make_unique<BanishEffect>(nullptr,target);
	// return eff;
	std::vector<std::unique_ptr<Effect>> base;
	base.push_back(std::move(eff));
	return base;
	
}

SpellList::Blizzard::Blizzard()
	:Spell {
	"Blizzard",
	"Deal 2 damage to all minions", 3, nullptr}
{}


std::vector<std::unique_ptr<Effect>> SpellList::Blizzard::onPlay(Card* target) {
	std::unique_ptr<Effect> eff = std::make_unique<AllBoard>(nullptr,nullptr,0,-2);
	eff.get()->setGame(this->getGame());
	// return eff;
	std::vector<std::unique_ptr<Effect>> base;
	base.push_back(std::move(eff));
	return base;
}

/*

SpellList::Disenchant::Disenchant()
	:Spell {
	"Disenchant",
	"Destroy the top enchantment on target minion", 1, nullptr}
{}

std::vector<std::unique_ptr<Effect>> SpellList::Disenchant::onPlay(Card * target) {
	std::unique_ptr<Effect> eff = std::make_unique<DisenchantEffect>(nullptr,target);
	return eff;
}

*/
SpellList::Recharge::Recharge()
	:Spell {
	"Recharge",
	"Your ritual gains 3 charges", 1, nullptr}
{}

std::vector<std::unique_ptr<Effect>> SpellList::Recharge::onPlay(Card * target) {
	std::unique_ptr<Effect> eff = std::make_unique<RitualEffect>(nullptr,nullptr,3);
	// return eff;
	std::vector<std::unique_ptr<Effect>> base;
	base.push_back(std::move(eff));
	return base;
}


SpellList::RaiseDead::RaiseDead()
	:Spell {
	"Raise Dead",
	"Resurrect the top minion in your graveyard and set its defense to 1", 1, nullptr}
{}

std::vector<std::unique_ptr<Effect>> SpellList::RaiseDead::onPlay(Card * target) {
	std::unique_ptr<Effect> eff = std::make_unique<ResEffect>(nullptr,nullptr);
	// return eff;
	std::vector<std::unique_ptr<Effect>> base;
	base.push_back(std::move(eff));
	return base;
}



SpellList::Unsummon::Unsummon()
	:Spell {
	"Unsummon",
	"Return target minion to its owners hand", 1, nullptr}
{}

std::vector<std::unique_ptr<Effect>> SpellList::Unsummon::onPlay(Card * target) {
	std::unique_ptr<Effect> eff = std::make_unique<HandEffect>(nullptr,target);
	// return eff;
	std::vector<std::unique_ptr<Effect>> base;
	base.push_back(std::move(eff));
	return base;
}



RitualList::auraOfPower::auraOfPower()
	:Ritual {
	"Aura of Power",
	"Whenever a minion enters play under your control, it gains +1/+1", 1,
	std::make_unique<SampleEffect>(nullptr,nullptr,1,1),4}
{}




Effect * RitualList::auraOfPower::onPlay() {
if(this->getOwner() != this->getGame()->getActivePlayer()) {
return nullptr;
}
this->setCharges(this->getCharges()-1);
this->getEffect()->setTarget(this->getGame()->getActivePlayer()->getBoardNum(this->getOwner()->getBoardSize()-1));
return this->getEffect();

}



RitualList::Standstill::Standstill()
	:Ritual {
	"Standstill",
	"Whenever a minion enters play, destroy it",3,
	std::make_unique<BanishEffect>(nullptr,nullptr),4}

{}

Effect * RitualList::Standstill::onPlay() {
this->setCharges(this->getCharges()-1);
this->getEffect()->setTarget(this->getGame()->getActivePlayer()->getBoardNum(this->getGame()->getActivePlayer()->getBoardSize()-1));
return this->getEffect();

}


RitualList::DarkRitual::DarkRitual()
	:Ritual {
	"Dark ritual",
	"At the start of your turn gain 1 mana", 0,
	std::make_unique<ManaEffect>(nullptr,nullptr),5}

{}

Effect * RitualList::DarkRitual::onTurnStart() {
if(this->getOwner() != this->getGame()->getActivePlayer()) {
return nullptr;
}
this->setCharges(this->getCharges()-1);
return this->getEffect();

}





