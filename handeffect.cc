#include "game.h"
#include "player.h"
#include "effect.h"
#include "handeffect.h"
#include "ritual.h"
#include "exceptions.h"
#include <memory>
#include "minion.h"

HandEffect::HandEffect(Player * own, std::unique_ptr<Minion> &b_ref) :
	Effect{own, b_ref.get()},
	b_ref{b_ref}
{}

void HandEffect::run() {
	// BaseMinion * m = dynamic_cast<BaseMinion *>(getTarget());
	Minion * bm = b_ref->getBase(true);
	getTarget()->getOwner()->removeFromBoard(b_ref, true);
	std::unique_ptr<Card> toHand;
	try{
		toHand.reset(bm);
		bm->getOwner()->addToHand(std::move(toHand));
		getGame()->printAlert(bm->getMinionName() + " returned to " + bm->getOwner()->getName() + "'s hand!", 1);
	}catch(HandIsFull &e){
		getGame()->printAlert(bm->getMinionName() + " was destroyed.", 1);
		throw;
	}
}
