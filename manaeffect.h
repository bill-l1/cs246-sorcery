#ifndef MANAEFFECT_H
#define MANA_H
#include "game.h"
#include "player.h"
#include "effect.h"
#include "spell.h"
#include "card.h"
#include "minion.h"
#include "base_minion.h"
class ManaEffect : public Effect{
	public:
	ManaEffect(Player * owner, Card * target);
	void run() override;
};

#endif
