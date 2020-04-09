#include "Equipment.h"

Equipment::Equipment()
{
  m_name = "";
  m_stats = {0};
}

Equipment::Equipment(std::string i_name, int i_id, EQUIPMENT_STATS_T i_stats)
{
  m_name = i_name;
  m_id = i_id;
  m_stats = i_stats;
}

Equipment::Equipment(std::string i_name, int i_id, TYPE_BONUSES_T i_attackBonuses, TYPE_BONUSES_T i_defenceBonuses, OTHER_BONUSES_T i_otherBonuses)
{
  m_name = i_name;
  m_id = i_id;
  m_stats = {0};

  m_stats.AttackBonuses = i_attackBonuses;
  m_stats.DefenceBonuses = i_defenceBonuses;
  m_stats.OtherBonuses = i_otherBonuses;
}

Equipment::Equipment(std::string i_name, int i_id, int i_stabAttack, int i_slashAttack, int i_crushAttack, int i_rangedAttack, int i_magicAttack,
                     int i_stabDefence, int i_slashDefence, int i_crushDefence, int i_rangedDefence, int i_magicDefence,
                     int i_strength, int i_rangedStrength, int i_magicDamage, int i_prayer)
{
  m_name = i_name;
  m_id = i_id;
  m_stats = {0};

  m_stats.AttackBonuses.Stab = i_stabAttack;
  m_stats.AttackBonuses.Slash = i_slashAttack;
  m_stats.AttackBonuses.Crush = i_crushAttack;
  m_stats.AttackBonuses.Magic = i_magicAttack;
  m_stats.AttackBonuses.Ranged = i_rangedAttack;

  m_stats.DefenceBonuses.Stab = i_stabDefence;
  m_stats.DefenceBonuses.Slash = i_slashDefence;
  m_stats.DefenceBonuses.Crush = i_crushDefence;
  m_stats.DefenceBonuses.Magic = i_magicDefence;
  m_stats.DefenceBonuses.Ranged = i_rangedDefence;

  m_stats.OtherBonuses.Strength = i_strength;
  m_stats.OtherBonuses.RangedStrength = i_rangedStrength;
  m_stats.OtherBonuses.MagicDamage = i_magicDamage;
  m_stats.OtherBonuses.Prayer = i_prayer;
}

Equipment::~Equipment()
{
}

void Equipment::SetName(std::string i_name)
{
  m_name = i_name;
}

void Equipment::SetId(int i_id)
{
  m_id = i_id;
}

void Equipment::SetAttackBonuses(TYPE_BONUSES_T i_attackBonuses)
{
  m_stats.AttackBonuses = i_attackBonuses;
}

void Equipment::SetAttackBonuses(int i_stab, int i_slash, int i_crush, int i_magic, int i_ranged)
{
  m_stats.AttackBonuses.Stab = i_stab;
  m_stats.AttackBonuses.Slash = i_slash;
  m_stats.AttackBonuses.Crush = i_crush;
  m_stats.AttackBonuses.Magic = i_magic;
  m_stats.AttackBonuses.Ranged = i_ranged;
}

void Equipment::SetDefenceBonuses(TYPE_BONUSES_T i_defenceBonuses)
{
  m_stats.DefenceBonuses = i_defenceBonuses;
}

void Equipment::SetDefenceBonuses(int i_stab, int i_slash, int i_crush, int i_magic, int i_ranged)
{
  m_stats.DefenceBonuses.Stab = i_stab;
  m_stats.DefenceBonuses.Slash = i_slash;
  m_stats.DefenceBonuses.Crush = i_crush;
  m_stats.DefenceBonuses.Magic = i_magic;
  m_stats.DefenceBonuses.Ranged = i_ranged;
}

void Equipment::SetOtherBonuses(OTHER_BONUSES_T i_otherBonuses)
{
  m_stats.OtherBonuses = i_otherBonuses;
}

void Equipment::SetOtherBonuses(int i_strength, int i_rangedStrength, float i_magicDamage, int i_prayer)
{
  m_stats.OtherBonuses.Strength = i_strength;
  m_stats.OtherBonuses.RangedStrength = i_rangedStrength;
  m_stats.OtherBonuses.MagicDamage = i_magicDamage;
  m_stats.OtherBonuses.Prayer = i_prayer;
}

const std::string &Equipment::Name() const
{
  return m_name;
}

const int& Equipment::Id() const
{
  return m_id;
}

const EQUIPMENT_STATS_T &Equipment::Stats() const
{
  return m_stats;
}