#include "ritualeffect.h"
RitualEffect::RitualEffect(Player * own, Card * tar, int qt) :
	Effect{own, tar},
	quantity{qt}
{}

void RitualEffect::run() {
	if(this->getGame()->getActivePlayer()->getRitual() != nullptr) {
		this->getGame()->getActivePlayer()->getRitual()->setCharges(this->getGame()->getActivePlayer()->getRitual()->getCharges()+quantity);
	}
}
