#ifndef CARDLIST_H
#define CARDLIST_H

#include "base_minion.h"
#include "enchantment.h"

#include "spell.h"
#include "sampleeffect.h"
#include "game.h"
#include "ritual.h"
#include "banisheffect.h"
#include "teambuff.h"
#include "allboard.h"
#include "summoneffect.h"
#include "disenchanteffect.h"
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
	class Bomb : public BaseMinion { public: Bomb(); };
	class FireElemental : public BaseMinion { public: FireElemental(); };
	class PotionSeller : public BaseMinion { public: PotionSeller(); std::unique_ptr<Effect> onEndTurn() override; };
	class NovicePyromancer : public BaseMinion { public: NovicePyromancer(); std::unique_ptr<Effect> onActivate(Card * target) override; };
	class ApprenticeSummoner : public BaseMinion { public: ApprenticeSummoner(); std::unique_ptr<Effect> onActivate(Card * target) override;};
	class MasterSummoner : public BaseMinion { public: MasterSummoner(); };
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
	class Banish : public Spell { public: Banish(); };
	class Blizzard : public Spell { public: Blizzard(); };
	//class Unsummon : public Spell { public: Unsummon(Player * owner, Card * Target); };
	class Disenchant : public Spell { public: Disenchant(); };

};

class RitualList {
	public:
	class auraOfPower : public Ritual { public: auraOfPower(); Effect * onPlay() override; };

};

#endif
