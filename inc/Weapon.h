#ifndef WEAPON_H
#define WEAPON_H

#include "Equipment.h"

class Weapon : public Equipment
{
public:
  Weapon();

  Weapon(std::string i_name, int i_id, EQUIPMENT_STATS_T i_stats, WEAPON_STATS_T i_weaponStats, bool i_twoHanded);
  Weapon(std::string i_name, int i_id, TYPE_BONUSES_T i_attackBonuses, TYPE_BONUSES_T i_defenceBonuses, OTHER_BONUSES_T i_strengthBonuses, WEAPON_STATS_T i_weaponStats, bool i_twoHanded);
  Weapon(std::string i_name, int i_id, int i_stabAttack,  int i_slashAttack,    int i_crushAttack,  int i_rangedAttack,   int i_magicAttack,
                                       int i_stabDefence, int i_slashDefence,   int i_crushDefence, int i_rangedDefence,  int i_magicDefence,
                                       int i_strength,    int i_rangedStrength, int i_magicDamage,  int i_prayer,
                                       int i_attackSpeed, bool i_twoHanded,     std::vector<STANCE_T> i_stances);

  ~Weapon();

  void SetStance(int i_stanceIndex);
  void SetTwoHanded(bool i_twoHanded);

  COMBAT_STYLE_E::Type GetCombatStyle();
  COMBAT_STYLE_E::Type GetCombatStyle(int i_stanceIndex);
  MELEE_DAMAGE_TYPE_E::Type GetMeleeDamageType();
  STANCE_T GetStance();
  int GetStanceStrengthBonus();
  int GetStanceAccuracyBonus();
  float GetAttackSpeed();

  WEAPON_STATS_T WeaponStats() const;
  bool TwoHanded() const;

  friend std::ostream &operator<<(std::ostream &os, const Weapon& obj)
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
      << ", " << obj.Stats().OtherBonuses.Prayer
      << "], Weapon Stats: [" << obj.WeaponStats().AttackSpeed;

    for (int i = 0; i < obj.WeaponStats().Stances.size(); ++i)
    {
      os << ", " << obj.WeaponStats().Stances[0].Experience;
    }
    os << "]";

    return os;
  }

protected:
  int m_stanceIndex;
  bool m_twoHanded;
  WEAPON_STATS_T m_weaponStats;
};

#endif