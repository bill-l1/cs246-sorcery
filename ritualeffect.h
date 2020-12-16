#ifndef RITUALEFFECT_H
#define RITUALEFFECT_H
#include "game.h"
#include "player.h"
#include "effect.h"
#include "spell.h"
#include "card.h"
#include "minion.h"
#include "base_minion.h"
#include <memory>
#include "ritual.h"
class RitualEffect : public Effect{
	int quantity;
	public:
	RitualEffect(Player * owner, Card * target, const int &quantity);
	void run() override;
};

#endif
