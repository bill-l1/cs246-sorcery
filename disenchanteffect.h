#ifndef DISENCHANTEFFECT_H
#define DISENCHANTEFFECT_H
#include <memory>
#include "player.h"
#include "minion.h"
#include "effect.h"

class DisenchantEffect : public Effect {
    std::unique_ptr<Minion> &b_ref;
    Enchantment * e_target;
    public:
        DisenchantEffect(Player * owner, std::unique_ptr<Minion> &b_ref, Enchantment * e_target);
        virtual ~DisenchantEffect();
        void run() override;
};

#endif
