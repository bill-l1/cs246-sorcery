#include "cardlist.h"
#include "base_minion.h"
#include "spell.h"


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

MinionList::FireElemental::FireElemental()
	: BaseMinion{
	"Fire Elemental",
	"Whenever an opponent's minion enters play, deal 1 damage to it",
	2, 2, 2}
{}

MinionList::PotionSeller::PotionSeller()
	: BaseMinion{
	"Potion Seller",
	"At the end of your turn, all your minions gain +0/+1",
	2, 1, 3,-1}
{}

std::unique_ptr<Effect> MinionList::PotionSeller::onEndTurn() {
	std::unique_ptr<Effect> eff = std::make_unique<TeamBuff>(nullptr,this->getGame()->getActivePlayer()->getBoardNum(0),0,1);
	if (this->getOwner() != this->getGame()->getActivePlayer()) {
	return nullptr;
	}
	eff.get()->setGame(this->getGame());
	return eff;
}

MinionList::NovicePyromancer::NovicePyromancer()
	: BaseMinion{
	"Novice Pyromancer",
	"Deal 1 damage to target minion",
	1, 0, 1, 1}
{}


std::unique_ptr<Effect> MinionList::NovicePyromancer::onActivate(Card * target) {
	std::unique_ptr<Effect> eff = std::make_unique<SampleEffect>(nullptr,target,0,-1);
	eff.get()->setGame(this->getGame());
	return std::move(eff);

}

MinionList::ApprenticeSummoner::ApprenticeSummoner()
	: BaseMinion{
	"Apprentice Summoner",
	"Summon a 1/1 air elemental",
	1, 1, 1, 1}
{}


std::unique_ptr<Effect> MinionList::ApprenticeSummoner::onActivate(Card * target) {
	std::unique_ptr<Effect> eff = std::make_unique<SummonEffect>(nullptr,nullptr,1);
	eff.get()->setGame(this->getGame());
	return std::move(eff);

}

MinionList::MasterSummoner::MasterSummoner()
	: BaseMinion{
	"Master Summoner",
	"Summon up to three 1/1 air elementals",
	3, 2, 2, 2}
{}

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
	toDestroy{false},
	effect{std::make_unique<DisenchantEffect>(nullptr, nullptr, this)}
{}

Effect * EnchantmentList::Delay::onEndTurn(){
	if(toDestroy){
		return effect.get();
	}else{
		toDestroy = true;
		return component->onEndTurn();
	}
}

int EnchantmentList::Delay::getActions() const{
	if(toDestroy){
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

Effect * EnchantmentList::Silence::getAbility() const {
	return nullptr;
}

int EnchantmentList::Silence::getActivateCost() const {
	return -1;
}

SpellList::Banish::Banish()
	:Spell {
	"Banish",
	"Destroy Target Minion or Ritual", 2, 
	std::make_unique<BanishEffect>(nullptr,nullptr),nullptr}
{}


SpellList::Blizzard::Blizzard()
	:Spell {
	"Blizzard",
	"Deal 2 damage to all minions", 3, 
	std::make_unique<AllBoard>(nullptr,nullptr,0,-2),nullptr}
{}

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

