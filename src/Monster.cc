#include "Monster.h"

Monster::Monster()
{
  m_name = "";
  m_id = 0;
  m_stats = {0};
  m_attributes.clear();
}

Monster::Monster(std::string i_name, int i_id, MONSTER_STATS_T i_stats)
{
  m_name = i_name;
  m_id = i_id;
  m_stats = i_stats;
  m_attributes.clear();
}

Monster::Monster(std::string i_name, int i_id, MONSTER_STATS_T i_stats, std::vector<std::string> i_attributes)
  : Monster(i_name, i_id, i_stats)
{
  m_attributes = i_attributes;
}

Monster::Monster(std::string i_name, int i_id, MONSTER_COMBAT_STATS_T i_combatStats, TYPE_BONUSES_T i_attackBonuses, TYPE_BONUSES_T i_defensiveBonuses, OTHER_BONUSES_T i_otherBonuses)
{
  m_name = i_name;
  m_id = i_id;
  m_stats = {0};

  m_stats.CombatStats = i_combatStats;
  m_stats.AttackBonuses = i_attackBonuses;
  m_stats.DefensiveBonuses = i_defensiveBonuses;
  m_stats.OtherBonuses = i_otherBonuses;

  m_attributes.clear();
}

Monster::Monster(std::string i_name, int i_id, MONSTER_COMBAT_STATS_T i_combatStats, TYPE_BONUSES_T i_attackBonuses, TYPE_BONUSES_T i_defensiveBonuses, OTHER_BONUSES_T i_otherBonuses, std::vector<std::string> i_attributes)
  : Monster(i_name, i_id, i_combatStats, i_attackBonuses, i_defensiveBonuses, i_otherBonuses)
{
  m_attributes = i_attributes;
}

Monster::Monster(std::string i_name, int i_id, int i_combatAttack,  int i_combatStrength, int i_combatDefence, int i_combatMagic,  int i_combatRanged,  int i_combatHitpoints, int i_accuracy, int i_size,
                                               int i_attackStab,    int i_attackSlash,    int i_attackCrush,   int i_attackMagic,  int i_attackRanged,
                                               int i_defenceStab,   int i_defenceSlash,   int i_defenceCrush,  int i_defenceMagic, int i_defenceRanged,
                                               int i_meleeStrength, int i_rangedStrength, int i_magicDamage)
{
  m_name = i_name;
  m_id = i_id;
  m_stats = {0};

  m_stats.CombatStats.Attack     = i_combatAttack;
  m_stats.CombatStats.Strength   = i_combatStrength;
  m_stats.CombatStats.Defence    = i_combatDefence;
  m_stats.CombatStats.Ranged     = i_combatRanged;
  m_stats.CombatStats.Magic      = i_combatMagic;
  m_stats.CombatStats.Hitpoints  = i_combatHitpoints;
  m_stats.CombatStats.Accuracy   = i_accuracy;
  m_stats.CombatStats.Size       = i_size;
 
  m_stats.AttackBonuses.Stab     = i_attackStab;
  m_stats.AttackBonuses.Slash    = i_attackSlash;
  m_stats.AttackBonuses.Crush    = i_attackCrush;
  m_stats.AttackBonuses.Magic    = i_attackMagic;
  m_stats.AttackBonuses.Ranged   = i_attackRanged;

  m_stats.DefensiveBonuses.Stab   = i_defenceStab;
  m_stats.DefensiveBonuses.Slash  = i_defenceSlash;
  m_stats.DefensiveBonuses.Crush  = i_defenceCrush;
  m_stats.DefensiveBonuses.Magic  = i_defenceMagic;
  m_stats.DefensiveBonuses.Ranged = i_defenceRanged;

  m_stats.OtherBonuses.Strength = i_meleeStrength;
  m_stats.OtherBonuses.RangedStrength = i_rangedStrength;
  m_stats.OtherBonuses.MagicDamage = i_magicDamage;

  m_attributes.clear();
}

Monster::Monster(std::string i_name, int i_id, int i_combatAttack,  int i_combatStrength, int i_combatDefence, int i_combatMagic,  int i_combatRanged,  int i_combatHitpoints, int i_accuracy, int i_size,
                                               int i_attackStab,    int i_attackSlash,    int i_attackCrush,   int i_attackMagic,  int i_attackRanged,
                                               int i_defenceStab,   int i_defenceSlash,   int i_defenceCrush,  int i_defenceMagic, int i_defenceRanged,
                                               int i_meleeStrength, int i_rangedStrength, int i_magicDamage,
                                               std::vector<std::string> i_attributes)
  : Monster(i_name, i_id, i_combatAttack,  i_combatStrength, i_combatDefence, i_combatMagic,  i_combatRanged,  i_combatHitpoints, i_accuracy, i_size,
                          i_attackStab,    i_attackSlash,    i_attackCrush,   i_attackMagic,  i_attackRanged,
                          i_defenceStab,   i_defenceSlash,   i_defenceCrush,  i_defenceMagic, i_defenceRanged,
                          i_meleeStrength, i_rangedStrength, i_magicDamage)
{
  m_attributes = i_attributes;
}

Monster::~Monster()
{
}

void Monster::SetName(std::string i_name)
{
  m_name = i_name;
}

void Monster::SetId(int i_id)
{
  m_id = i_id;
}

void Monster::SetStats(MONSTER_STATS_T i_stats)
{
  m_stats = i_stats;
}

void Monster::SetAttributes(std::vector<std::string> i_attributes)
{
  m_attributes = i_attributes;
}

void Monster::AddAttribute(std::string i_attribute)
{
  m_attributes.push_back(i_attribute);
}

void Monster::AddAttributes(std::vector<std::string> i_attributes)
{
  m_attributes.insert(m_attributes.end(), i_attributes.begin(), i_attributes.end());
}

const std::string& Monster::Name() const
{
  return m_name;
}

const int& Monster::Id() const
{
  return m_id;
}

const MONSTER_STATS_T& Monster::Stats() const
{
  return m_stats;
}

const std::vector<std::string>& Monster::Attributes() const
{
  return m_attributes;
}