#include "game.h"
#include "player.h"
#include "effect.h"
#include "manaeffect.h"
#include "ritual.h"
ManaEffect::ManaEffect(Player * own, Card * tar) :
	Effect{own, tar}
{}

void ManaEffect::run() {
	this->getOwner()->setMagic(this->getOwner()->getMagic()+1);
}
