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
		getGame()->printAlert(m->getMinionName() + " returned to " + m->getOwner()->getName() + "'s hand!", 1);
		m->getOwner()->addToHand(m);
		m->getOwner()->removeFromBoard(m);	
	}
}
