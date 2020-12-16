#include "reseffect.h"
ResEffect::ResEffect(Player * own, Card * tar) :
	Effect{own, tar}
{}

void ResEffect::run() {
	if(this->getGame()->getActivePlayer()->getRitual() != nullptr) {
		
	}
}
