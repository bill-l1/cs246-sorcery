#include "game.h"
#include "player.h"
#include "effect.h"
#include "banisheffect.h"
#include "ritual.h"
BanishEffect::BanishEffect(Player * own, Card * tar) :
	Effect{own, tar}
{}

void BanishEffect::run() {
	BaseMinion * m = dynamic_cast<BaseMinion *>(getTarget());
	if( m!= nullptr) {
	m->setDefense(0);
	}
	Ritual * r = dynamic_cast<Ritual *>(getTarget());
	if(r != nullptr) {
	r->setCharges(0);
	}
}
