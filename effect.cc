#include "effect.h"
#include "game.h"
#include "player.h"

Effect::Effect(Player * own, Card * tar) {
	owner = own;
	target = tar;
}

Effect::~Effect() {}

Player * Effect::getOwner() const {
	return owner;
}
Card * Effect::getTarget() const {
	return target;
}
void Effect::setTarget(Card * newtarget) {
	target = newtarget;
}
void Effect::run() {
}

Game * Effect::getGame() const {
return game;
}

void Effect::setGame(Game * newgame) {
	game = newgame;
}
