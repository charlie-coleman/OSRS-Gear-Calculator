#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "types.h"
#include <ostream>
#include <string>

class Equipment
{
public:
  Equipment();

  Equipment(std::string i_name, int i_id, EQUIPMENT_STATS_T i_stats);
  Equipment(std::string i_name, int i_id, TYPE_BONUSES_T i_attackBonuses, TYPE_BONUSES_T i_defenceBonuses, OTHER_BONUSES_T i_strengthBonuses);
  Equipment(std::string i_name, int i_id, int i_stabAttack,  int i_slashAttack,    int i_crushAttack,  int i_rangedAttack,   int i_magicAttack,
                                          int i_stabDefence, int i_slashDefence,   int i_crushDefence, int i_rangedDefence,  int i_magicDefence,
                                          int i_strength,    int i_rangedStrength, int i_magicDamage,  int i_prayer);
  
  ~Equipment();

  void SetName(std::string i_name);
  void SetId(int i_id);

  void SetAttackBonuses(TYPE_BONUSES_T i_attackBonuses);
  void SetAttackBonuses(int i_stab, int i_slash, int i_crush, int i_magic, int i_ranged);
  
  void SetDefenceBonuses(TYPE_BONUSES_T i_defenceBonuses);
  void SetDefenceBonuses(int i_stab, int i_slash, int i_crush, int i_magic, int i_ranged);

  void SetOtherBonuses(OTHER_BONUSES_T i_otherBonuses);
  void SetOtherBonuses(int i_strength, int i_rangedStrength, float i_magicDamage, int i_prayer);

  const std::string& Name() const;
  const int& Id() const;
  const EQUIPMENT_STATS_T& Stats() const;

  friend std::ostream &operator<<(std::ostream &os, const Equipment& obj)
  {
    os << obj.Name()
      << " Attack Bonuses: [" << obj.Stats().AttackBonuses.Stab
      << ", " << obj.Stats().AttackBonuses.Slash
      << ", " << obj.Stats().AttackBonuses.Crush
      << ", " << obj.Stats().AttackBonuses.Ranged
      << ", " << obj.Stats().AttackBonuses.Magic
      << "], Defence Bonuses: [" << obj.Stats().DefenceBonuses.Stab
      << ", " << obj.Stats().DefenceBonuses.Slash
      << ", " << obj.Stats().DefenceBonuses.Crush
      << ", " << obj.Stats().DefenceBonuses.Ranged
      << ", " << obj.Stats().DefenceBonuses.Magic
      << "], Other Bonuses: [" << obj.Stats().OtherBonuses.Strength
      << ", " << obj.Stats().OtherBonuses.RangedStrength
      << ", " << obj.Stats().OtherBonuses.MagicDamage
      << ", " << obj.Stats().OtherBonuses.Prayer << "]";

    return os;
  }

protected:
  std::string m_name;
  int m_id;
  EQUIPMENT_STATS_T m_stats;
};

#endif