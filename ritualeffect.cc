#include "ritualeffect.h"
RitualEffect::RitualEffect(Player * own, Card * tar, const int &qt) :
	Effect{own, tar},
	quantity{qt}
{}

void RitualEffect::run() {
	if(getOwner() != nullptr && getOwner()->getRitual() != nullptr) {
		getOwner()->getRitual()->setCharges(getOwner()->getRitual()->getCharges()+quantity);
	}
}
