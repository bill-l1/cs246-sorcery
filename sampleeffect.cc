#include "game.h"
#include "player.h"
#include "effect.h"
#include "sampleeffect.h"
SampleEffect::SampleEffect(Player * own, Card * tar) {
this->owner = own;
this->target = tar;
}
	void SampleEffect::run() {
	BaseMinion * m = dynamic_cast<BaseMinion *>(getTarget());
	m->setAttack(1);
	m->setDefense(1);
	
	}
