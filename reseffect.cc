#include "reseffect.h"
RitualEffect::RitualEffect(Player * own, Card * tar) :
	Effect{own, tar}
{}

void ResEffect::run() {
	if(this->getGame()->getActivePlayer()->getRitual() != nullptr) {
		
	}
}
