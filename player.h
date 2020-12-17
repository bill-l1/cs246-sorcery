#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <memory>
#include <vector>
#include <stack>

class Card;
class Minion;
class BaseMinion;
class Enchantment;

class Spell;
class Ritual;
class Player  {
	std::string name;
	int life;
	int magic;
	std::stack<std::unique_ptr<Card> > deck;
	std::vector<std::unique_ptr<Card> > hand;
	std::vector<std::unique_ptr<Minion>> board;
	std::stack<std::unique_ptr<BaseMinion>> graveyard;
	std::unique_ptr<Ritual> ritual;
	public:
		Player(const std::string &name);
		std::string getName() const;
		int getLife() const;
		void setLife(const int &n);
		int getMagic() const;
		void setMagic(const int &n);
		int getDeckSize() const;
		void setDeck(std::stack<std::unique_ptr<Card>> d);
		int getHandSize() const;
		int getBoardSize() const;
		Ritual * getRitual() const;
		void draw();
		void playCard(std::unique_ptr<BaseMinion> card);
		void playCard(std::unique_ptr<Enchantment> card, std::unique_ptr<Minion>& target);
		void playCard(std::unique_ptr<Ritual> card);
		
		std::unique_ptr<BaseMinion>& graveyardTop();
		void graveyardPop();
		void addToHand(std::unique_ptr<Card> card);
		void addToBoard(std::unique_ptr<Minion> target);
		void removeFromBoard(std::unique_ptr<Minion>& target, const bool &release = false);
		Minion * getBoardNum(int num) const;
		//void runOnPlay(); //iterate through all board/rituals for onPlay effects
		//void runOnStartTurn(); 
		//void runOnEndTurn();
		friend class Game;
		friend class View;
};

#endif
