#ifndef SAMPLEEFFECT_H
#define SAMPLEEFFECT_H
#include "game.h"
#include "player.h"
#include "effect.h"
#include "spell.h"
#include "card.h"
#include "minion.h"
#include "base_minion.h"
class SampleEffect : public Effect{
	Player * owner;
	Card * target;
	public:
	SampleEffect(Player * owner, Card * target);
	void run() override;
};

#endif
