#ifndef HANDEFFECT_H
#define HANDEFFECT_H
#include "game.h"
#include "player.h"
#include "effect.h"
#include "spell.h"
#include "card.h"
#include "minion.h"
#include "base_minion.h"
class HandEffect : public Effect{
	public:
	HandEffect(Player * owner, Card * target);
	void run() override;
};

#endif
