#ifndef HANDEFFECT_H
#define HANDEFFECT_H
#include <memory>
#include "game.h"
#include "player.h"
#include "effect.h"
#include "spell.h"
#include "card.h"
#include "minion.h"
#include "base_minion.h"

class HandEffect : public Effect{
	std::unique_ptr<Minion>& b_ref;
	public:
	HandEffect(Player * owner, std::unique_ptr<Minion> &b_ref);
	void run() override;
};

#endif
