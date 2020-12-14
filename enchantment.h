#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

#include <string>
#include <memory>
#include "minion.h"

class Enchantment : public Minion {
    std::string att_str;
    std::string def_str;
    int statConvert(const int &in, const std::string &s) const;
    protected:
        std::unique_ptr<Minion> component;
    public:
        Enchantment(const std::string &name, const std::string &description, const int &cost, const std::string &att = "", const std::string &def = "");
        virtual ~Enchantment();
        std::string getMinionName() const override;
        std::string getMinionDescription() const override;
        int getMinionCost() const override;
        Minion * getComponent() const override;
        void setComponent(Minion * minion);
        std::string getAttackStr() const;
        virtual int getAttack() const override;
		void setAttack(const int &att) override;
        std::string getDefenseStr() const;
		virtual int getDefense() const override;
		void setDefense(const int &def) override;
		virtual int getActions() const override;
        void setActions(const int &n) override;
		virtual int getActivateCost() const override;
		void buff(const int &att, const int &def) override;
		Minion * getBase() override;
        Effect * getAbility() const override;
        Effect * onEndTurn() override;
		Effect * onDeath() override;
		Effect * onPlay() override;
        std::unique_ptr<Minion>& getBoardRef() const override;
		void setBoardRef(std::unique_ptr<Minion>& ref) override;
};

#endif
