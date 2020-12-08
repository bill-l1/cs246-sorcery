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
	2, 1, 3,0,std::make_unique<SampleEffect>(nullptr,nullptr,0,1)}
{}

void MinionList::PotionSeller::onEndTurn() {
for(int i = 0; i < this->getOwner()->getBoardSize(); i++) {
this->getAbility()->setTarget(this->getGame()->getActivePlayer().get()->getBoardNum(i));
this->getAbility()->run();
}
return;

}

MinionList::NovicePyromancer::NovicePyromancer()
	: BaseMinion{
	"Novice Pyromancer",
	"Deal 1 damage to target minion",
	1, 0, 1, 1}
{}

MinionList::ApprenticeSummoner::ApprenticeSummoner()
	: BaseMinion{
	"Apprentice Summoner",
	"Summon a 1/1 air elemental",
	1, 1, 1, 1}
{}

MinionList::MasterSummoner::MasterSummoner()
	: BaseMinion{
	"Master Summoner",
	"Summon up to three 1/1 air elementals",
	3, 2, 2, 2}
{}


SpellList::Banish::Banish()
	:Spell {
	"Banish",
	"Destroy Target Minion or Ritual", 2, 
	std::make_unique<BanishEffect>(nullptr,nullptr), nullptr}
{}

RitualList::auraOfPower::auraOfPower()
	:Ritual {
	"Aura of Power",
	"Whenever a minion enters play under your control, it gains +1/+1", 1,
	std::make_unique<SampleEffect>(nullptr,nullptr,1,1),4}

{}

void RitualList::auraOfPower::onAllyPlay() {
this->setCharges(this->getCharges()-1);
this->getEffect()->setTarget(this->getGame()->getActivePlayer().get()->getBoardNum(this->getOwner()->getBoardSize()-1));
this->getEffect()->run();
return;

}

