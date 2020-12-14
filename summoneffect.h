#ifndef SUMMONEFFECT_H
#define SUMMONEFFECT_H
#include "game.h"
#include "player.h"
#include "effect.h"
#include "spell.h"
#include "card.h"
#include "minion.h"
#include "base_minion.h"
#include <memory>
class SummonEffect : public Effect{
	int quantity;
	public:
	SummonEffect(Player * owner, Card * target, int quantity);
	void run() override;
};

#endif
