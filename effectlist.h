#ifndef EFFECTLIST_H
#define EFFECTLIST_H
#include <memory>
#include "effect.h"

class Player;
class Card;
class Minion;
class Enchantment;

class AllBoard: public Effect{
	int attack;
	int defense;
	public:
	AllBoard(Player * owner, Card * target, int atk, int def);
	void run() override;
};

class BanishEffect : public Effect{
	public:
	BanishEffect(Player * owner, Card * target);
	void run() override;
};

class DisenchantEffect : public Effect {
    std::unique_ptr<Minion> &b_ref;
    Enchantment * e_target;
    public:
        DisenchantEffect(Player * owner, std::unique_ptr<Minion> &b_ref, Enchantment * e_target);
        virtual ~DisenchantEffect();
        void run() override;
};

class ManaEffect : public Effect{
	public:
	ManaEffect(Player * owner, Card * target);
	void run() override;
};

class SampleEffect : public Effect{
	int attack;
	int defense;
	public:
	SampleEffect(Player * owner, Card * target, int atk, int def);
	void run() override;
};

class SummonEffect : public Effect{
	int quantity;
	public:
	SummonEffect(Player * owner, Card * target, int quantity);
	void run() override;
};

class TeamBuff: public Effect{
	int attack;
	int defense;
	public:
	TeamBuff(Player * owner, Card * target, int atk, int def);
	void run() override;
};

#endif