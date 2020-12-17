#ifndef CARDLIST_H
#define CARDLIST_H

#include <memory>
#include <vector>

#include "base_minion.h"
#include "enchantment.h"
#include "spell.h"
#include "ritual.h"

class Effect;

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
	class DrillSergeant : public BaseMinion { public: DrillSergeant(); std::vector<std::unique_ptr<Effect>> onActivate(Card * target) override; };
	class ClumsyGunner : public BaseMinion { public: ClumsyGunner(); std::vector<std::unique_ptr<Effect>> onEndTurn() override; };
	class StormElemental : public BaseMinion { public: StormElemental(); std::vector<std::unique_ptr<Effect>> onDeath() override; };

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
	class Steadfast : public Enchantment { 
		public: Steadfast(); 
		std::vector<std::unique_ptr<Effect>> onEndTurn() override;
	};
	class Retaliate : public Enchantment { 
		public: Retaliate(); 
		//int getActivateCost() const override;
		std::vector<std::unique_ptr<Effect>> onDeath() override;
	};
	class Bolster : public Enchantment { 
		public: Bolster(); 
		//int getActivateCost() const override;
		std::vector<std::unique_ptr<Effect>> onPlay() override;
	};


};

class SpellList {
	public:
	class Banish : public TargettedSpell { 
		public: Banish();  
		std::vector<std::unique_ptr<Effect>> onPlay(std::unique_ptr<Minion>& target) override; 
		std::vector<std::unique_ptr<Effect>> onPlay(std::unique_ptr<Ritual>& target) override; 
	};
	class Blizzard : public Spell { public: Blizzard();  std::vector<std::unique_ptr<Effect>> onPlay() override;};
	class Disenchant : public TargettedSpell { public: Disenchant();  std::vector<std::unique_ptr<Effect>> onPlay(std::unique_ptr<Minion>& target) override; };
	class Recharge : public Spell { public: Recharge();  std::vector<std::unique_ptr<Effect>> onPlay() override;};
	class Unsummon : public TargettedSpell { public: Unsummon();  std::vector<std::unique_ptr<Effect>> onPlay(std::unique_ptr<Minion>& target) override;};
	class RaiseDead : public Spell { public: RaiseDead();  std::vector<std::unique_ptr<Effect>> onPlay() override;};
	class StrengthPotion : public Spell { public: StrengthPotion();  std::vector<std::unique_ptr<Effect>> onPlay() override;};
	class Wipe : public Spell { public: Wipe();  std::vector<std::unique_ptr<Effect>> onPlay() override;};
};

class RitualList {
	public:
	class AuraOfPower : public Ritual { public: AuraOfPower(); Effect * onPlay() override; };
	class Standstill : public Ritual { public: Standstill(); Effect * onPlay() override; };
	class DarkRitual : public Ritual { public: DarkRitual(); Effect * onTurnStart() override; };

};

#endif
