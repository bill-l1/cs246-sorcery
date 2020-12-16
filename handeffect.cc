#include "game.h"
#include "player.h"
#include "effect.h"
#include "handeffect.h"
#include "ritual.h"
HandEffect::HandEffect(Player * own, Card * tar) :
	Effect{own, tar}
{}

void HandEffect::run() {
	BaseMinion * m = dynamic_cast<BaseMinion *>(getTarget());
	if( m != nullptr) {
		Minion * bm = m->getBase();
		//m->getGame()->getActivePlayer()->hand.push_back(bm);	
	}
}
