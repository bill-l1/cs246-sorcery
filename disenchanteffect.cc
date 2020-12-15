#include <memory>
#include <iostream>
#include "disenchanteffect.h"
#include "player.h"
#include "minion.h"
#include "enchantment.h"

DisenchantEffect::DisenchantEffect(Player * owner, std::unique_ptr<Minion> &b_ref, Enchantment * e_target) 
    : Effect{owner, b_ref.get()},
    b_ref{b_ref},
    e_target{e_target}
{}

DisenchantEffect::~DisenchantEffect() {}

void DisenchantEffect::run(){
    Minion * curr_minion = b_ref.get();
    if(curr_minion == e_target){
        std::cout << "run disenchant" << std::endl;
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
