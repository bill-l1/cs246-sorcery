#ifndef CARDLIST_H
#define CARDLIST_H

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
	class Bomb : public BaseMinion { public: Bomb();  std::unique_ptr<Effect> onDeath() override;  };
	class FireElemental : public BaseMinion { public: FireElemental(); std::unique_ptr<Effect> onPlay() override; };
	class PotionSeller : public BaseMinion { public: PotionSeller(); std::unique_ptr<Effect> onEndTurn() override; };
	class NovicePyromancer : public BaseMinion { public: NovicePyromancer(); std::unique_ptr<Effect> onActivate(Card * target) override; };
	class ApprenticeSummoner : public BaseMinion { public: ApprenticeSummoner(); std::unique_ptr<Effect> onActivate(Card * target) override;};
	class MasterSummoner : public BaseMinion { public: MasterSummoner(); std::unique_ptr<Effect> onActivate(Card * target) override; };
};

class EnchantmentList {
	public:
	class GiantStrength : public Enchantment { public: GiantStrength(); };
	class Enrage : public Enchantment { public: Enrage(); };
	class Delay : public Enchantment {
		bool toDestroy;
		public: 
		Delay();
		std::unique_ptr<Effect> onEndTurn() override;
		int getActions() const override;
	};
	class MagicFatigue : public Enchantment { 
		public: MagicFatigue(); 
		int getActivateCost() const override;
	};
	class Silence : public Enchantment { 
		public: Silence(); 
		int getActivateCost() const override;
		std::unique_ptr<Effect> onActivate(Card * target = nullptr) override;
	};
};

class SpellList {
	public:
	class Banish : public Spell { public: Banish();  std::unique_ptr<Effect> onPlay(Card * target) override; };
	class Blizzard : public Spell { public: Blizzard();  std::unique_ptr<Effect> onPlay(Card * target) override;};
	//class Disenchant : public Spell { public: Disenchant();  std::unique_ptr<Effect> onPlay(Card * target) override; };
	class Recharge : public Spell { public: Recharge();  std::unique_ptr<Effect> onPlay(Card * target) override;};
	class Unsummon : public Spell { public: Unsummon();  std::unique_ptr<Effect> onPlay(Card * target) override;};
	class RaiseDead : public Spell { public: RaiseDead();  std::unique_ptr<Effect> onPlay(Card * target) override;};
};

class RitualList {
	public:
	class auraOfPower : public Ritual { public: auraOfPower(); Effect * onPlay() override; };
	class Standstill : public Ritual { public: Standstill(); Effect * onPlay() override; };
	class DarkRitual : public Ritual { public: DarkRitual(); Effect * onTurnStart() override; };

};

#endif
