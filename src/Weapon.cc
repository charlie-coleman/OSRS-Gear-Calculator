#include "Weapon.h"

Weapon::Weapon()
  : Equipment(),
    m_stanceIndex(0)
{
  WEAPON_STATS_T temp;

  temp.AttackSpeed = 0;
  temp.Stances.clear();

  m_weaponStats = temp;
  m_twoHanded = false;
}

Weapon::Weapon(std::string i_name, int i_id, EQUIPMENT_STATS_T i_stats, WEAPON_STATS_T i_weaponStats, bool i_twoHanded)
  : Equipment(i_name, i_id, i_stats),
    m_stanceIndex(0)
{
  m_weaponStats = i_weaponStats;
  m_twoHanded = i_twoHanded;
}

Weapon::Weapon(std::string i_name, int i_id, TYPE_BONUSES_T i_attackBonuses, TYPE_BONUSES_T i_defenceBonuses, OTHER_BONUSES_T i_strengthBonuses, WEAPON_STATS_T i_weaponStats, bool i_twoHanded)
  : Equipment(i_name, i_id, i_attackBonuses, i_defenceBonuses, i_strengthBonuses),
    m_stanceIndex(0)
{
  m_weaponStats = i_weaponStats;
}

Weapon::~Weapon()
{
}

Weapon::Weapon(std::string i_name, int i_id, int i_stabAttack,  int i_slashAttack,    int i_crushAttack,  int i_rangedAttack,   int i_magicAttack,
                                             int i_stabDefence, int i_slashDefence,   int i_crushDefence, int i_rangedDefence,  int i_magicDefence,
                                             int i_strength,    int i_rangedStrength, int i_magicDamage,  int i_prayer,
                                             int i_attackSpeed, bool i_twoHanded,     std::vector<STANCE_T> i_stances)
  : Equipment(i_name, i_id, i_stabAttack,  i_slashAttack,    i_crushAttack,  i_rangedAttack,  i_magicAttack,
                            i_stabDefence, i_slashDefence,   i_crushDefence, i_rangedDefence, i_magicDefence,
                            i_strength,    i_rangedStrength, i_magicDamage,  i_prayer),
    m_stanceIndex(0)
{
  m_weaponStats.AttackSpeed = i_attackSpeed;

  m_weaponStats.Stances = i_stances;

  m_twoHanded = i_twoHanded;
}

void Weapon::SetStance(int i_stanceIndex)
{
  m_stanceIndex = i_stanceIndex;
}

void Weapon::SetTwoHanded(bool i_twoHanded)
{
  m_twoHanded = i_twoHanded;
}

COMBAT_STYLE_E::Type Weapon::GetCombatStyle()
{
  STANCE_T stance = m_weaponStats.Stances[m_stanceIndex];

  if (stance.Experience.compare("attack") == 0 ||
      stance.Experience.compare("strength") == 0 ||
      stance.Experience.compare("defence") == 0 ||
      stance.Experience.compare("shared") == 0)
  {
    return COMBAT_STYLE_E::MELEE;
  }
  else if (stance.Experience.compare("ranged") == 0 || stance.Experience.compare("ranged and defence") == 0)
  {
    return COMBAT_STYLE_E::RANGED;
  }
  else if (stance.Experience.compare("magic") == 0 || stance.Experience.compare("magic and defense") == 0)
  {
    return COMBAT_STYLE_E::MAGIC;
  }
  else
  {
    return COMBAT_STYLE_E::SIZE_OF_COMBAT_STYLE;
  }
}

COMBAT_STYLE_E::Type Weapon::GetCombatStyle(int i_stanceIndex)
{
  STANCE_T stance = m_weaponStats.Stances[i_stanceIndex];

  if (stance.Experience.compare("attack") == 0 ||
      stance.Experience.compare("strength") == 0 ||
      stance.Experience.compare("defence") == 0 ||
      stance.Experience.compare("shared") == 0)
  {
    return COMBAT_STYLE_E::MELEE;
  }
  else if (stance.Experience.compare("ranged") == 0 || stance.Experience.compare("ranged and defence") == 0)
  {
    return COMBAT_STYLE_E::RANGED;
  }
  else if (stance.Experience.compare("magic") == 0 || stance.Experience.compare("magic and defense") == 0)
  {
    return COMBAT_STYLE_E::MAGIC;
  }
  else
  {
    return COMBAT_STYLE_E::SIZE_OF_COMBAT_STYLE;
  }
}

MELEE_DAMAGE_TYPE_E::Type Weapon::GetMeleeDamageType()
{
  STANCE_T s = WeaponStats().Stances[m_stanceIndex];

  if (s.AttackType.compare("slash") == 0)
  {
    return MELEE_DAMAGE_TYPE_E::SLASH;
  }
  else if (s.AttackType.compare("stab") == 0)
  {
    return MELEE_DAMAGE_TYPE_E::STAB;
  }
  else if (s.AttackType.compare("crush") == 0)
  {
    return MELEE_DAMAGE_TYPE_E::CRUSH;
  }
  else
  {
    return MELEE_DAMAGE_TYPE_E::SIZE_OF_MELEE_DAMAGE_TYPE;
  }
}

STANCE_T Weapon::GetStance()
{
  return WeaponStats().Stances[m_stanceIndex];
}

float Weapon::GetAttackSpeed()
{
  int baseSpeed = WeaponStats().AttackSpeed;
   
   if (GetCombatStyle() == COMBAT_STYLE_E::RANGED && WeaponStats().Stances[m_stanceIndex].CombatStyle.compare("rapid") == 0)
   {
     baseSpeed--;
   }

   return 0.6 * baseSpeed;
}

int Weapon::GetStanceStrengthBonus()
{
  STANCE_T s = WeaponStats().Stances[m_stanceIndex];
  COMBAT_STYLE_E::Type style = GetCombatStyle();

  if (style == COMBAT_STYLE_E::MELEE)
  {
    if (s.AttackStyle == "aggressive")
    {
      return 3;
    }
    else if (s.AttackStyle == "controlled")
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else if (style == COMBAT_STYLE_E::RANGED)
  {
    if (s.CombatStyle.compare("accurate") == 0)
    {
      return 3;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    return 0;
  }
}

int Weapon::GetStanceAccuracyBonus()
{
  STANCE_T s = WeaponStats().Stances[m_stanceIndex];
  COMBAT_STYLE_E::Type style = GetCombatStyle();

  if (style == COMBAT_STYLE_E::MELEE)
  {
    if (s.AttackStyle.compare("accurate") == 0)
    {
      return 3;
    }
    else if (s.AttackStyle.compare("controlled") == 0)
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else if (style == COMBAT_STYLE_E::RANGED)
  {
    if (s.CombatStyle.compare("accurate") == 0)
    {
      return 3;
    }
    else
    {
      return 0;
    }
  }
  else if (style == COMBAT_STYLE_E::MAGIC)
  {
    if (s.CombatStyle.compare("accurate") == 0)
    {
      return 3;
    }
    else if (s.CombatStyle.compare("longrange") == 0)
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    return 0;
  }
}

WEAPON_STATS_T Weapon::WeaponStats() const
{
  return m_weaponStats;
}

bool Weapon::TwoHanded() const
{
  return m_twoHanded;
}