#ifndef TEAMBUFF_H
#define TEAMBUFF_H
#include "game.h"
#include "player.h"
#include "effect.h"
#include "spell.h"
#include "card.h"
#include "minion.h"
#include "base_minion.h"
class TeamBuff: public Effect{
	int attack;
	int defense;
	public:
	TeamBuff(Player * owner, Card * target, int atk, int def);
	void run() override;
};

#endif
