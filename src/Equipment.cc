#include "Equipment.h"

Equipment::Equipment()
{
  m_slot = SLOT_E::AMMUNITION;
  m_stats = {0};
}

Equipment::Equipment(std::string i_name, SLOT_E::Type i_slot, EQUIPMENT_STATS_T i_stats)
{
  m_name = i_name;
  m_slot = i_slot;
  m_stats = i_stats;
}

Equipment::Equipment(std::string i_name, SLOT_E::Type i_slot, TYPE_BONUSES_T i_attackBonuses, TYPE_BONUSES_T i_defenseBonuses, OTHER_BONUSES_T i_otherBonuses)
{
  m_name = i_name;
  m_slot = i_slot;
  m_stats = {0};

  m_stats.AttackBonuses = i_attackBonuses;
  m_stats.DefenseBonuses = i_defenseBonuses;
  m_stats.OtherBonuses = i_otherBonuses;
}

Equipment::Equipment(std::string i_name, SLOT_E::Type i_slot, int i_stabAttack, int i_slashAttack, int i_crushAttack, int i_rangedAttack, int i_magicAttack,
                     int i_stabDefense, int i_slashDefense, int i_crushDefense, int i_rangedDefense, int i_magicDefense,
                     int i_strength, int i_rangedStrength, int i_magicDamage, int i_prayer)
{
  m_name = i_name;
  m_slot = i_slot;
  m_stats = {0};

  m_stats.AttackBonuses.Stab = i_stabAttack;
  m_stats.AttackBonuses.Slash = i_slashAttack;
  m_stats.AttackBonuses.Crush = i_crushAttack;
  m_stats.AttackBonuses.Magic = i_magicAttack;
  m_stats.AttackBonuses.Ranged = i_rangedAttack;

  m_stats.DefenseBonuses.Stab = i_stabDefense;
  m_stats.DefenseBonuses.Slash = i_slashDefense;
  m_stats.DefenseBonuses.Crush = i_crushDefense;
  m_stats.DefenseBonuses.Magic = i_magicDefense;
  m_stats.DefenseBonuses.Ranged = i_rangedDefense;

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

void Equipment::SetSlot(SLOT_E::Type i_slot)
{
  m_slot = i_slot;
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

void Equipment::SetDefenseBonuses(TYPE_BONUSES_T i_defenseBonuses)
{
  m_stats.DefenseBonuses = i_defenseBonuses;
}

void Equipment::SetDefenseBonuses(int i_stab, int i_slash, int i_crush, int i_magic, int i_ranged)
{
  m_stats.DefenseBonuses.Stab = i_stab;
  m_stats.DefenseBonuses.Slash = i_slash;
  m_stats.DefenseBonuses.Crush = i_crush;
  m_stats.DefenseBonuses.Magic = i_magic;
  m_stats.DefenseBonuses.Ranged = i_ranged;
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

const SLOT_E::Type &Equipment::Slot() const
{
  return m_slot;
}

const EQUIPMENT_STATS_T &Equipment::Stats() const
{
  return m_stats;
}