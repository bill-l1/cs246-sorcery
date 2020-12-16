#ifndef RESEFFECT_H
#define RESEFFECT_H
#include "game.h"
#include "player.h"
#include "effect.h"
#include "spell.h"
#include "card.h"
#include "minion.h"
#include "base_minion.h"
#include <memory>
class ResEffect : public Effect{
	public:
	RitualEffect(Player * owner, Card * target);
	void run() override;
};

#endif
