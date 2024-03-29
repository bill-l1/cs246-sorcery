#ifndef CARDFACTORY_H
#define CARDFACTORY_H
#include <string>
#include <memory>
#include <map>
#include "cardlist.h"

class Card;
class Player;
class BaseMinion;
class Enchantment;

typedef std::unique_ptr<Card>(*build_ptr)();

class CardFactory {
	static std::map<std::string, build_ptr> FUNC_MAP;
	public:
		template<class T>
		static std::unique_ptr<Card> buildCard();
		static std::unique_ptr<Card> getCard(const std::string &name, Player * owner);
};

#endif
