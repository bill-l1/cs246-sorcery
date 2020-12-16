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
		m->getGame()->getActivePlayer()->addToHand(m);
		m->getGame()->getActivePlayer()->removeFromBoard(m);	
	}
}
