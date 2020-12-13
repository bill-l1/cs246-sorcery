#include "cardfactory.h"
#include "summoneffect.h"
SummonEffect::SummonEffect(Player * own, Card * tar, int qt) :
	Effect{own, tar},
	quantity{qt}
{}

void SummonEffect::run() {
	
	//std::unique_ptr<Card> buildcard = CardFactory::getCard("Air Elemental",this->getGame()->getActivePlayer());
	std::unique_ptr<BaseMinion> card = std::make_unique<BaseMinion>("Air Elemental", "",0,1,1);

	this->getGame()->verifyBoardNotFull(this->getGame()->getActivePlayer());

	for(int i = 0; i < quantity; i++) {
	this->getGame()->getActivePlayer()->playCard(std::move(card));

	}
}
