#include "reseffect.h"
ResEffect::ResEffect(Player * own, Card * tar) :
	Effect{own, tar}
{}

void ResEffect::run() {
	if(this->getGame()->getActivePlayer()->graveyardTop() != nullptr) {
	std::unique_ptr<Minion> m = this->getGame()->getActivePlayer()->graveyardTop();
	std::unique_ptr<BaseMinion> cast_m;
	BaseMinion * ptr = static_cast<BaseMinion *>(m.get());
	m.release();
	cast_m.reset(ptr);
	this->getGame()->getActivePlayer()->graveyardPop();
	this->getGame()->getActivePlayer()->playCard(std::move(cast_m));
	}
}
