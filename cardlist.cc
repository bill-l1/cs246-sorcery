#include "cardlist.h"
#include "base_minion.h"

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
	2, 1, 3}
{}

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
	2}
{}

EnchantmentList::MagicFatigue::MagicFatigue()
	: Enchantment{
	"Magic Fatigue",
	"Enchanted minion's activated ability costs 2 more",
	0}
{}

EnchantmentList::MagicFatigue::Silence()
	: Enchantment{
	"Silence",
	"Enchanted minion cannot use abilities",
	1}
{}