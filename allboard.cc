#include "allboard.h"

AllBoard::AllBoard(Player * own, Card * tar, int atk, int def) :
	Effect{own, tar},
	attack{atk},
	defense{def}
{}

void AllBoard::run() {
	for(int i = 0; i < this->getGame()->getActivePlayer()->getBoardSize(); i++) {
		this->getGame()->buff(this->getGame()->getActivePlayer()->getBoardNum(i),attack,defense);
		
	}

	for(int j = 0; j < this->getGame()->getNonActivePlayer()->getBoardSize(); j++) {
		this->getGame()->buff(this->getGame()->getNonActivePlayer()->getBoardNum(j),attack,defense);
		
	}
	
	
}
