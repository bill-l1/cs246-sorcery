#include "reseffect.h"
#include "exceptions.h"
#include <iostream>
ResEffect::ResEffect(Player * own, Card * tar) :
	Effect{own, tar}
{}

void ResEffect::run() {
	if(getOwner() != nullptr && getOwner() != nullptr) {
		getGame()->verifyBoardNotFull(getOwner());
		std::unique_ptr<BaseMinion>& m = getOwner()->graveyardTop();
		std::unique_ptr<BaseMinion> cast_m;
		BaseMinion * ptr = static_cast<BaseMinion *>(m.get());
		ptr->setDefense(1);
		getGame()->printAlert(ptr->getMinionName()+" is resurrected with 1 defense.", 2);
		m.release();
		cast_m.reset(ptr);
		getOwner()->graveyardPop();
		getOwner()->playCard(std::move(cast_m));
	}else{
		throw InvalidTarget();
	}
}
