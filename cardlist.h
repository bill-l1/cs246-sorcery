#ifndef CARDLIST_H
#define CARDLIST_H

#include <memory>
#include <vector>

#include "base_minion.h"
#include "enchantment.h"
#include "spell.h"
#include "ritual.h"

class Effect;

#include "handeffect.h"
#include "ritualeffect.h"
#include "reseffect.h"

// #include "sampleeffect.h"
// #include "game.h"
// #include "banisheffect.h"
// #include "teambuff.h"
// #include "allboard.h"
// #include "summoneffect.h"
// #include "disenchanteffect.h"
// #include "manaeffect.h"

//Steps to create a new card:
// 1. add it to header
// 	class NAME : public TYPE_CLASS { public : NAME(); };
// 2. add it to implementation
// 3. define any behavior (triggers, effects, etc.)
// 4. add to card mapping

class MinionList {
	public:
	class AirElemental : public BaseMinion { public: AirElemental(); };
	class EarthElemental : public BaseMinion { public: EarthElemental(); };
	class Bomb : public BaseMinion { public: Bomb();  std::vector<std::unique_ptr<Effect>> onDeath() override;  };
	class FireElemental : public BaseMinion { public: FireElemental(); std::vector<std::unique_ptr<Effect>> onPlay() override; };
	class PotionSeller : public BaseMinion { public: PotionSeller(); std::vector<std::unique_ptr<Effect>> onEndTurn() override; };
	class NovicePyromancer : public BaseMinion { public: NovicePyromancer(); std::vector<std::unique_ptr<Effect>> onActivate(Card * target) override; };
	class ApprenticeSummoner : public BaseMinion { public: ApprenticeSummoner(); std::vector<std::unique_ptr<Effect>> onActivate(Card * target) override;};
	class MasterSummoner : public BaseMinion { public: MasterSummoner(); std::vector<std::unique_ptr<Effect>> onActivate(Card * target) override; };
};

class EnchantmentList {
	public:
	class GiantStrength : public Enchantment { public: GiantStrength(); };
	class Enrage : public Enchantment { public: Enrage(); };
	class Delay : public Enchantment {
		bool toDestroy;
		public: 
		Delay();
		std::vector<std::unique_ptr<Effect>> onEndTurn() override;
		int getActions() const override;
	};
	class MagicFatigue : public Enchantment { 
		public: MagicFatigue(); 
		int getActivateCost() const override;
	};
	class Silence : public Enchantment { 
		public: Silence(); 
		int getActivateCost() const override;
		std::vector<std::unique_ptr<Effect>> onActivate(Card * target = nullptr) override;
	};
};

class SpellList {
	public:
	class Banish : public Spell { 
		public: Banish();  
		std::vector<std::unique_ptr<Effect>> onPlay(std::unique_ptr<Minion>& target) override; 
		std::vector<std::unique_ptr<Effect>> onPlay(std::unique_ptr<Ritual>& target) override; 
	};
	class Blizzard : public Spell { public: Blizzard();  std::vector<std::unique_ptr<Effect>> onPlay() override;};
	class Disenchant : public Spell { public: Disenchant();  std::vector<std::unique_ptr<Effect>> onPlay(std::unique_ptr<Minion>& target) override; };
	class Recharge : public Spell { public: Recharge();  std::vector<std::unique_ptr<Effect>> onPlay() override;};
	class Unsummon : public Spell { public: Unsummon();  std::vector<std::unique_ptr<Effect>> onPlay(std::unique_ptr<Minion>& target) override;};
	class RaiseDead : public Spell { public: RaiseDead();  std::vector<std::unique_ptr<Effect>> onPlay() override;};
};

class RitualList {
	public:
	class auraOfPower : public Ritual { public: auraOfPower(); Effect * onPlay() override; };
	class Standstill : public Ritual { public: Standstill(); Effect * onPlay() override; };
	class DarkRitual : public Ritual { public: DarkRitual(); Effect * onTurnStart() override; };

};

#endif
