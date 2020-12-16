#include <memory>
#include "cardfactory.h"
#include "cardlist.h"
#include "effectlist.h"
#include "ritual.h"
#include "minion.h"
#include "base_minion.h"
#include "enchantment.h"
#include "effect.h"
#include "player.h"
#include "game.h"

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

BanishEffect::BanishEffect(Player * own, Card * tar) :
	Effect{own, tar}
{}

void BanishEffect::run() {
	BaseMinion * m = dynamic_cast<BaseMinion *>(getTarget());
	if( m!= nullptr) {
	    m->setDefense(0);
	}
	Ritual * r = dynamic_cast<Ritual *>(getTarget());
	if(r != nullptr) {
	    r->setCharges(0);
	}
}

DisenchantEffect::DisenchantEffect(Player * owner, std::unique_ptr<Minion> &b_ref, Enchantment * e_target) 
    : Effect{owner, b_ref.get()},
    b_ref{b_ref},
    e_target{e_target}
{}

DisenchantEffect::~DisenchantEffect() {}

void DisenchantEffect::run(){
    Minion * curr_minion = b_ref.get();
    if(curr_minion == e_target){
        Minion * child = curr_minion->getComponent(true);
        b_ref.reset(child);
    }else{
        while(curr_minion->getComponent() != nullptr){
            if(Enchantment * m_cast = dynamic_cast<Enchantment *>(curr_minion->getComponent())){
                if(Enchantment * parent = dynamic_cast<Enchantment *>(curr_minion)){
                    if(m_cast == e_target){
                        Minion * child = m_cast->getComponent(true);
                        parent->setComponent(child);
                        break;
                    }
                }
            }
            curr_minion = curr_minion->getComponent();
        }
    }
}

ManaEffect::ManaEffect(Player * own, Card * tar) :
	Effect{own, tar}
{}

void ManaEffect::run() {
	this->getOwner()->setMagic(this->getOwner()->getMagic()+1);
}

SampleEffect::SampleEffect(Player * own, Card * tar,int atk, int def) :
	Effect{own, tar},
	attack{atk},
	defense{def}
{}

void SampleEffect::run() {
	BaseMinion * m = dynamic_cast<BaseMinion *>(getTarget());
	if(m != nullptr) {
	m->setAttack(m->getAttack()+attack);
	m->setDefense(m->getDefense()+defense);
	}
}

SummonEffect::SummonEffect(Player * own, Card * tar, int qt) :
	Effect{own, tar},
	quantity{qt}
{}

void SummonEffect::run() {
	this->getGame()->verifyBoardNotFull(getOwner());

	for(int i = 0; i < quantity; i++) {
        std::unique_ptr<Card> card = CardFactory::buildCard<MinionList::AirElemental>();
        std::unique_ptr<BaseMinion> cast_card;
        BaseMinion * ptr = static_cast<BaseMinion *>(card.get());
        card.release();
        cast_card.reset(ptr);
        getOwner()->playCard(std::move(cast_card));
	}
}

TeamBuff::TeamBuff(Player * own, Card * tar, int atk, int def) :
	Effect{own, tar},
	attack{atk},
	defense{def}
{}

void TeamBuff::run() {
	BaseMinion * m = dynamic_cast<BaseMinion *>(getTarget());
	if(m != nullptr) {
	for(int i = 0; i < m->getOwner()->getBoardSize(); i++) {
		m->getGame()->buff(m->getOwner()->getBoardNum(i),attack,defense);
		
	}
	
	}
}
