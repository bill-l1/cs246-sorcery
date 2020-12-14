#include "game.h"
#include "player.h"
#include "effect.h"
#include "sampleeffect.h"

SampleEffect::SampleEffect(Player * own, Card * tar,int atk, int def) :
	Effect{own, tar},
	attack{atk},
	defense{def}
{}

void SampleEffect::run() {
	BaseMinion * m = dynamic_cast<BaseMinion *>(getTarget());
	if(m != nullptr) {
	m->setAttack(m->getAttack()+attack);
	m->setDefense(m->getDefense()+defense);
	}
}
