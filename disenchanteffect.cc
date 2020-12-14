#include <memory>
#include "disenchanteffect.h"
#include "player.h"
#include "minion.h"
#include "enchantment.h"

DisenchantEffect::DisenchantEffect(Player * owner, std::unique_ptr<Minion> &b_ref, Enchantment * e_target) 
    : Effect{owner, b_ref.get()},
    b_ref{b_ref},
    e_target{e_target}
{}

void DisenchantEffect::run(){
    Minion * curr_minion = b_ref.get();
    if(curr_minion == e_target){
        Minion * child = curr_minion->getComponent();
        b_ref.release();
        b_ref.reset(child);
    }else{
        //TODO
        // Minion * curr_minion = target;
        // while(curr_minion->getComponent() != nullptr){

        // }
    }
}