#ifndef EFFECT_H
#define EFFECT_H
#include "game.h"
#include "player.h"
class Effect{
	Player * owner;
	Card * target;
	public:
		Effect(Player * owner, Card * target);
		~Effect();
		Player * getOwner() const;
		Card * getTarget() const;
		void setTarget(Card * target);
		virtual void run();
};

#endif
