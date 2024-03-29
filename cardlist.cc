#include <vector>
#include <memory>
#include "cardlist.h"
#include "base_minion.h"
#include "spell.h"
#include "effectlist.h"
#include "exceptions.h"

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
		std::unique_ptr<Effect> eff = std::make_unique<TeamBuff>(getOwner(),this->getGame()->getActivePlayer()->getBoardNum(0),0,-this->getAttack());
		std::vector<std::unique_ptr<Effect>> base;
		base.push_back(std::move(eff));
		return base;
		// return std::move(eff);
	}

	std::unique_ptr<Effect> eff2 = std::make_unique<TeamBuff>(getOwner(),this->getGame()->getNonActivePlayer()->getBoardNum(0),0,-this->getAttack());
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
		std::unique_ptr<Effect> eff = std::make_unique<SampleEffect>(getOwner(),this->getGame()->getActivePlayer()->getBoardNum(this->getGame()->getActivePlayer()->getBoardSize()-1),0,-1);
		// return std::move(eff);
		eff.get()->setGame(this->getGame());
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
	std::unique_ptr<Effect> eff = std::make_unique<TeamBuff>(getOwner(),this->getGame()->getActivePlayer()->getBoardNum(0),0,1);
	std::vector<std::unique_ptr<Effect>> base;
	if (this->getOwner() != this->getGame()->getActivePlayer()) {
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
	std::unique_ptr<Effect> eff = std::make_unique<SampleEffect>(target->getOwner(), target,0,-1);
	eff.get()->setGame(this->getGame());
	std::vector<std::unique_ptr<Effect>> base;
	base.push_back(std::move(eff));
	return base;
	// return std::move(eff);
}

MinionList::DrillSergeant::DrillSergeant()
        : BaseMinion{
        "Drill Sergeant",
        "Give target minion +2 attack and -1 defense",
        2, 2, 1, 2}
{}


std::vector<std::unique_ptr<Effect>> MinionList::DrillSergeant::onActivate(Card * target) {
        std::unique_ptr<Effect> eff = std::make_unique<SampleEffect>(target->getOwner(), target,2,-1);
        eff.get()->setGame(this->getGame());
        std::vector<std::unique_ptr<Effect>> base;
        base.push_back(std::move(eff));
        return base;
}


MinionList::ClumsyGunner::ClumsyGunner()
        : BaseMinion{
        "Clumsy Gunner",
        "At the end of your turn, deal 2 damage to a random enemy",
        2, 1, 3, -1}
{}

std::vector<std::unique_ptr<Effect>> MinionList::ClumsyGunner::onEndTurn() {
	std::vector<std::unique_ptr<Effect>> base;
	int target = this->getGame()->getNonActivePlayer()->getBoardSize();
	int target2 = 0;
	if(target != 0) {
	target2 = rand() % target;
	}

std::unique_ptr<Effect> eff = std::make_unique<SampleEffect>(this->getGame()->getActivePlayer(),this->getGame()->getNonActivePlayer()->getBoardNum(target2),0,-2);
eff.get()->setGame(this->getGame());


if (this->getOwner() != this->getGame()->getActivePlayer()) {
		return base;
}

base.push_back(std::move(eff));
return base;


}


MinionList::ApprenticeSummoner::ApprenticeSummoner()
	: BaseMinion{
	"Apprentice Summoner",
	"Summon a 1/1 air elemental",
	1, 1, 1, 1}
{}


std::vector<std::unique_ptr<Effect>> MinionList::ApprenticeSummoner::onActivate(Card * target) {
	std::unique_ptr<Effect> eff = std::make_unique<SummonEffect>(getOwner(), nullptr,1);
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
	std::unique_ptr<Effect> eff = std::make_unique<SummonEffect>(getOwner(),nullptr,3);
	eff.get()->setGame(this->getGame());
	std::vector<std::unique_ptr<Effect>> base;
	base.push_back(std::move(eff));
	return base;
	// return std::move(eff);

}

MinionList::StormElemental::StormElemental()
	: BaseMinion{
	"Storm Elemental",
	"Summon up to two 1/1 air elementals when this dies",
	3, 2, 2, -1}
{}

std::vector<std::unique_ptr<Effect>> MinionList::StormElemental::onDeath() {
	std::unique_ptr<Effect> eff = std::make_unique<SummonEffect>(getOwner(),nullptr,2);
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

EnchantmentList::Steadfast::Steadfast()
	: Enchantment{
	"Steadfast",
	"Give a minion: At the end of your turn, gain 2 attack",
	1}
{}

std::vector<std::unique_ptr<Effect>> EnchantmentList::Steadfast::onEndTurn(){
		std::vector<std::unique_ptr<Effect>> v = component.get()->onEndTurn();
		if(this->getOwner() == this->getComponent()->getGame()->getActivePlayer()) {
		std::unique_ptr<Effect> eff = std::make_unique<SampleEffect>(this->getOwner(), this->getComponent(), 1,0);
		eff.get()->setGame(this->getComponent()->getGame());
		v.push_back(std::move(eff));
		}		
		return v;
}


EnchantmentList::Retaliate::Retaliate()
	: Enchantment{
	"Retaliate",
	"Give a minion \"When this minion dies, give all your minions +2/+2\"",
	1}
{}

std::vector<std::unique_ptr<Effect>> EnchantmentList::Retaliate::onDeath(){
		std::vector<std::unique_ptr<Effect>> v = component->onDeath();
		std::unique_ptr<Effect> eff = std::make_unique<TeamBuff>(getOwner(), getComponent(), 2,2);
		eff.get()->setGame(this->getComponent()->getGame());
		v.push_back(std::move(eff));
		return v;
}


EnchantmentList::Bolster::Bolster()
	: Enchantment{
	"Bolster",
	"Give a minion \"When an opponents minion enters play, this gains 1 defense\"",
	1}
{}

std::vector<std::unique_ptr<Effect>> EnchantmentList::Bolster::onPlay(){
		std::vector<std::unique_ptr<Effect>> v = component->onPlay();
		if (this->getOwner() == this->getComponent()->getGame()->getNonActivePlayer()) {
		std::unique_ptr<Effect> eff = std::make_unique<SampleEffect>(getOwner(), getComponent(), 0,1);	
		eff.get()->setGame(this->getComponent()->getGame());
		v.push_back(std::move(eff));
	
		}
		return v;
}



SpellList::Wipe::Wipe()
	: Spell {
	"Wipe",
	"Destroy all minions and resurrect the last minion destroyed for each player.", 3}
{}


std::vector<std::unique_ptr<Effect>> SpellList::Wipe::onPlay() {
	std::unique_ptr<Effect> eff = std::make_unique<AllBoard>(nullptr,nullptr,0,-999);
	eff.get()->setGame(this->getGame());
	std::unique_ptr<Effect> eff2 = std::make_unique<ResEffect>(this->getGame()->getActivePlayer(),nullptr);
	eff2.get()->setGame(this->getGame());
	std::unique_ptr<Effect> eff3 = std::make_unique<ResEffect>(this->getGame()->getNonActivePlayer(),nullptr);
	eff3.get()->setGame(this->getGame());
	std::vector<std::unique_ptr<Effect>> base;
	base.push_back(std::move(eff));
	base.push_back(std::move(eff2));
	base.push_back(std::move(eff3));
	return base;
}



SpellList::Banish::Banish()
	:TargettedSpell {
	"Banish",
	"Destroy target minion or ritual", 2}
{}

std::vector<std::unique_ptr<Effect>> SpellList::Banish::onPlay(std::unique_ptr<Minion>& target) {
	std::unique_ptr<Effect> eff = std::make_unique<BanishEffect>(target->getOwner(), target.get());
	std::vector<std::unique_ptr<Effect>> base;
	base.push_back(std::move(eff));
	return base;
	// return eff;
}

std::vector<std::unique_ptr<Effect>> SpellList::Banish::onPlay(std::unique_ptr<Ritual>& target) {
	std::unique_ptr<Effect> eff = std::make_unique<BanishEffect>(target->getOwner(), target.get());
	std::vector<std::unique_ptr<Effect>> base;
	base.push_back(std::move(eff));
	return base;
	// return eff;
}

SpellList::Blizzard::Blizzard()
	: Spell {
	"Blizzard",
	"Deal 2 damage to all minions", 3}
{}


std::vector<std::unique_ptr<Effect>> SpellList::Blizzard::onPlay() {
	std::unique_ptr<Effect> eff = std::make_unique<AllBoard>(nullptr,nullptr,0,-2);
	eff.get()->setGame(this->getGame());
	// return eff;
	std::vector<std::unique_ptr<Effect>> base;
	base.push_back(std::move(eff));
	return base;
}

SpellList::Disenchant::Disenchant()
	:TargettedSpell {
	"Disenchant",
	"Destroy the top enchantment on target minion", 1}
{}

std::vector<std::unique_ptr<Effect>> SpellList::Disenchant::onPlay(std::unique_ptr<Minion>& target) {
	std::vector<std::unique_ptr<Effect>> base;
	if(Enchantment * cast = dynamic_cast<Enchantment * >(target.get())){
		std::unique_ptr<Effect> eff = std::make_unique<DisenchantEffect>(nullptr, target, cast);
		base.push_back(std::move(eff));
		return base;
	}else{
		throw InvalidTarget{};
		return base;
	}
}

SpellList::Recharge::Recharge()
	:Spell {
	"Recharge",
	"Your ritual gains 3 charges", 1}
{}

std::vector<std::unique_ptr<Effect>> SpellList::Recharge::onPlay() {
	std::unique_ptr<Effect> eff = std::make_unique<RitualEffect>(getOwner(),nullptr,3);
	// return eff;
	std::vector<std::unique_ptr<Effect>> base;
	base.push_back(std::move(eff));
	return base;
}

SpellList::RaiseDead::RaiseDead()
	:Spell {
	"Raise Dead",
	"Resurrect the top minion in your graveyard and set its defense to 1", 1}
{}

std::vector<std::unique_ptr<Effect>> SpellList::RaiseDead::onPlay() {
	std::unique_ptr<Effect> eff = std::make_unique<ResEffect>(getOwner(),nullptr);
	eff.get()->setGame(this->getGame());
	// return eff;
	std::vector<std::unique_ptr<Effect>> base;
	base.push_back(std::move(eff));
	return base;
}

SpellList::Unsummon::Unsummon()
	:TargettedSpell {
	"Unsummon",
	"Return target minion to its owners hand", 1}
{}

std::vector<std::unique_ptr<Effect>> SpellList::Unsummon::onPlay(std::unique_ptr<Minion>& target) {
	std::unique_ptr<Effect> eff = std::make_unique<HandEffect>(getOwner(), target);
	// return eff;
	eff.get()->setGame(this->getGame());
	std::vector<std::unique_ptr<Effect>> base;
	base.push_back(std::move(eff));
	return base;
}

SpellList::StrengthPotion::StrengthPotion()
        :Spell {
        "Strength Potion",
        "Give a random friendly minion +4/+4", 2}
{}


std::vector<std::unique_ptr<Effect>> SpellList::StrengthPotion::onPlay() {
	int target = this->getGame()->getActivePlayer()->getBoardSize();
	int target2 = 0;
	if(target != 0) {
	target2 = rand() % target;
	}
	std::unique_ptr<Effect> eff = std::make_unique<SampleEffect>(this->getGame()->getActivePlayer(),this->getGame()->getActivePlayer()->getBoardNum(target2),4,4);
        eff.get()->setGame(this->getGame());

        // return eff;
        std::vector<std::unique_ptr<Effect>> base;
        base.push_back(std::move(eff));
        return base;
}




RitualList::AuraOfPower::AuraOfPower()
	:Ritual {
	"Aura of Power",
	"Whenever a minion enters play under your control, it gains +1/+1", 1,
	std::make_unique<SampleEffect>(nullptr,nullptr, 1, 1), 4, 1}
{}

Effect * RitualList::AuraOfPower::onPlay() {
	if(this->getOwner() != this->getGame()->getActivePlayer()) {
		return nullptr;
	}
	this->getEffect()->setTarget(this->getGame()->getActivePlayer()->getBoardNum(this->getOwner()->getBoardSize()-1));
	return this->getEffect();
}

RitualList::Standstill::Standstill()
	:Ritual {
	"Standstill",
	"Whenever a minion enters play, destroy it", 3,
	std::make_unique<BanishEffect>(nullptr,nullptr), 4, 2}

{}

Effect * RitualList::Standstill::onPlay() {
	this->getEffect()->setTarget(this->getGame()->getActivePlayer()->getBoardNum(this->getGame()->getActivePlayer()->getBoardSize()-1));
	return this->getEffect();
}


RitualList::DarkRitual::DarkRitual()
	: Ritual {
	"Dark ritual",
	"At the start of your turn gain 1 mana", 0,
	std::make_unique<ManaEffect>(nullptr,nullptr), 5, 1}

{}

Effect * RitualList::DarkRitual::onTurnStart() {
	if(this->getOwner() != this->getGame()->getActivePlayer()) {
		return nullptr;
	}
	return this->getEffect();
}





