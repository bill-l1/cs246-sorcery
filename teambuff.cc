#include "game.h"
#include "player.h"
#include "effect.h"
#include "teambuff.h"

TeamBuff::TeamBuff(Player * own, Card * tar, int atk, int def) :
	Effect{own, tar},
	attack{atk},
	defense{def}
{}

void TeamBuff::run() {
	BaseMinion * m = dynamic_cast<BaseMinion *>(getTarget());
	if(m != nullptr) {
	for(int i = 0; i < m->getOwner()->getBoardSize(); i++) {
		m->getGame()->buff(m->getGame()->getActivePlayer()->getBoardNum(i),attack,defense);
		
	}
	
	}
}
