#include <memory>
#include "disenchanteffect.h"
#include "player.h"
#include "minion.h"
#include "enchantment.h"

DisenchantEffect::DisenchantEffect(Player * owner, std::unique_ptr<Minion> &t_ref, Minion * e_target) 
    : Effect{owner, t_ref.get()},
    t_ref{t_ref},
    e_target{e_target}
{}

void DisenchantEffect::run(){
    // if (auto minion = dynamic_cast<Minion *>(getTarget())){
    //     if(auto enchant = dynamic_cast<Enchantment *>(e_target)){
    //         Minion * curr_enchant = minion;

    //         while(curr_enchant != nullptr && curr_enchant->getComponent() != e_target){
    //             curr_enchant = curr_enchant->getComponent();
    //         }

    //         if(curr_enchant != nullptr){

    //         }
    //     }
    // }
    if(t_ref->getComponent() != nullptr){
        Minion * component = t_ref->getComponent();
        t_ref.release();
        t_ref.reset(component);
    }
}