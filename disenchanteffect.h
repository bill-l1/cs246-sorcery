#ifndef DISENCHANTEFFECT_H
#define DISENCHANTEFFECT_H
#include <memory>
#include "player.h"
#include "minion.h"
#include "effect.h"

class DisenchantEffect : public Effect {
    std::unique_ptr<Minion>& t_ref;
    Minion * e_target;
    public:
        DisenchantEffect(Player * owner, std::unique_ptr<Minion> &t_ref, Minion * e_target);
        void run() override;
};

#endif