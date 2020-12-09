#ifndef BANISHEFFECT_H
#define BANISHEFFECT_H
#include "game.h"
#include "player.h"
#include "effect.h"
#include "spell.h"
#include "card.h"
#include "minion.h"
#include "base_minion.h"
class BanishEffect : public Effect{
	public:
	BanishEffect(Player * owner, Card * target);
	void run() override;
};

#endif
