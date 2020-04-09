#include "Weapon.h"

Weapon::Weapon()
  : Equipment()
{
  WEAPON_STATS_T temp;

  temp.AttackSpeed = 0;
  temp.Stances.clear();

  m_weaponStats = temp;
}

Weapon::Weapon(std::string i_name, int i_id, EQUIPMENT_STATS_T i_stats, WEAPON_STATS_T i_weaponStats)
  : Equipment(i_name, i_id, i_stats)
{
  m_weaponStats = i_weaponStats;
}

Weapon::Weapon(std::string i_name, int i_id, TYPE_BONUSES_T i_attackBonuses, TYPE_BONUSES_T i_defenceBonuses, OTHER_BONUSES_T i_strengthBonuses, WEAPON_STATS_T i_weaponStats)
  : Equipment(i_name, i_id, i_attackBonuses, i_defenceBonuses, i_strengthBonuses)
{
  m_weaponStats = i_weaponStats;
}

Weapon::~Weapon()
{
}

Weapon::Weapon(std::string i_name, int i_id, int i_stabAttack,  int i_slashAttack,    int i_crushAttack,  int i_rangedAttack,   int i_magicAttack,
                                             int i_stabDefence, int i_slashDefence,   int i_crushDefence, int i_rangedDefence,  int i_magicDefence,
                                             int i_strength,    int i_rangedStrength, int i_magicDamage,  int i_prayer,
                                             int i_attackSpeed, std::vector<STANCE_T> i_stances)
  : Equipment(i_name, i_id, i_stabAttack,  i_slashAttack,    i_crushAttack,  i_rangedAttack,  i_magicAttack,
                            i_stabDefence, i_slashDefence,   i_crushDefence, i_rangedDefence, i_magicDefence,
                            i_strength,    i_rangedStrength, i_magicDamage,  i_prayer)
{
  m_weaponStats.AttackSpeed = i_attackSpeed;

  m_weaponStats.Stances = i_stances;
}

const WEAPON_STATS_T& Weapon::WeaponStats() const
{
  return m_weaponStats;
}