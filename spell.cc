
#include <memory>
#include "spell.h"

Spell::Spell(const std::string &name, const std::string &description, const int &cost) : 
	Card{name, description, cost, "Spell"}
{}

Spell::~Spell() {};

std::vector<std::unique_ptr<Effect>> Spell::onPlay() {
	std::vector<std::unique_ptr<Effect>> empty;
    return empty;
}

TargettedSpell::TargettedSpell(const std::string &name, const std::string &description, const int &cost) : 
	Spell{name, description, cost}
{}

TargettedSpell::~TargettedSpell() {};

std::vector<std::unique_ptr<Effect>> TargettedSpell::onPlay(std::unique_ptr<Minion>& target) {
	std::vector<std::unique_ptr<Effect>> empty;
    return empty;
}

std::vector<std::unique_ptr<Effect>> TargettedSpell::onPlay(std::unique_ptr<Ritual>& target) {
	std::vector<std::unique_ptr<Effect>> empty;
    return empty;
}
