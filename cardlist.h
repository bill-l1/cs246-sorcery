#ifndef CARDLIST_H
#define CARDLIST_H

#include "base_minion.h"

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
	class PotionSeller : public BaseMinion { public: PotionSeller(); };
	class NovicePyromancer : public BaseMinion { public: NovicePyromancer(); };
	class ApprenticeSummoner : public BaseMinion { public: ApprenticeSummoner(); };
	class MasterSummoner : public BaseMinion { public: MasterSummoner(); };
};

#endif