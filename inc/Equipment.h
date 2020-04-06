#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "types.h"
#include <ostream>
#include <string>

class Equipment
{
  public:
    Equipment();

    Equipment(std::string i_name, SLOT_E::Type i_slot, EQUIPMENT_STATS_T i_stats);
    Equipment(std::string i_name, SLOT_E::Type i_slot, TYPE_BONUSES_T i_attackBonuses, TYPE_BONUSES_T i_defenseBonuses, OTHER_BONUSES_T i_strengthBonuses);
    Equipment(std::string i_name, SLOT_E::Type i_slot, int i_stabAttack,  int i_slashAttack,    int i_crushAttack,  int i_rangedAttack,   int i_magicAttack,
                                                       int i_stabDefense, int i_slashDefense,   int i_crushDefense, int i_rangedDefense,  int i_magicDefense,
                                                       int i_strength,    int i_rangedStrength, int i_magicDamage,  int i_prayer);
    
    ~Equipment();

    void SetName(std::string i_name);
    void SetSlot(SLOT_E::Type i_slot);

    void SetAttackBonuses(TYPE_BONUSES_T i_attackBonuses);
    void SetAttackBonuses(int i_stab, int i_slash, int i_crush, int i_magic, int i_ranged);
    
    void SetDefenseBonuses(TYPE_BONUSES_T i_defenseBonuses);
    void SetDefenseBonuses(int i_stab, int i_slash, int i_crush, int i_magic, int i_ranged);

    void SetOtherBonuses(OTHER_BONUSES_T i_otherBonuses);
    void SetOtherBonuses(int i_strength, int i_rangedStrength, float i_magicDamage, int i_prayer);

    const std::string& Name() const;
    const SLOT_E::Type& Slot() const;
    const EQUIPMENT_STATS_T& Stats() const;

    friend std::ostream &operator<<(std::ostream &os, const Equipment& obj)
    {
      os << obj.Name()
        << " Attack Bonuses: [" << obj.Stats().AttackBonuses.Stab
        << ", " << obj.Stats().AttackBonuses.Slash
        << ", " << obj.Stats().AttackBonuses.Crush
        << ", " << obj.Stats().AttackBonuses.Ranged
        << ", " << obj.Stats().AttackBonuses.Magic
        << "], Defense Bonuses: [" << obj.Stats().DefenseBonuses.Stab
        << ", " << obj.Stats().DefenseBonuses.Slash
        << ", " << obj.Stats().DefenseBonuses.Crush
        << ", " << obj.Stats().DefenseBonuses.Ranged
        << ", " << obj.Stats().DefenseBonuses.Magic
        << "], Other Bonuses: [" << obj.Stats().OtherBonuses.Strength
        << ", " << obj.Stats().OtherBonuses.RangedStrength
        << ", " << obj.Stats().OtherBonuses.MagicDamage
        << ", " << obj.Stats().OtherBonuses.Prayer << "]";

      return os;
    }

  private:
    std::string m_name;
    SLOT_E::Type m_slot;
    EQUIPMENT_STATS_T m_stats;
};

#endif