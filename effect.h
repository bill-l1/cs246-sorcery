#ifndef EFFECT_H
#define EFFECT_H
#include "game.h"
#include "player.h"
class Effect{
	Player * owner;
	Card * target;
	Game * game;
	public:
		Effect(Player * owner, Card * target);
		virtual ~Effect();
		Player * getOwner() const;
		Card * getTarget() const;
		void setTarget(Card * target);
		virtual void run();
		void setGame(Game * game);
		Game * getGame() const;
};

#endif
