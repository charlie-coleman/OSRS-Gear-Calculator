#ifndef MONSTER_H
#define MONSTER_H

#include <types.h>

class Monster
{
public:
  Monster();
  
  Monster(std::string i_name, int i_id, MONSTER_STATS_T i_stats);
  Monster(std::string i_name, int i_id, MONSTER_STATS_T i_stats, std::vector<std::string> i_attributes);
  
  Monster(std::string i_name, int i_id, MONSTER_COMBAT_STATS_T i_combatStats, TYPE_BONUSES_T i_attackBonuses, TYPE_BONUSES_T i_defensiveBonuses, OTHER_BONUSES_T i_otherBonuses);
  Monster(std::string i_name, int i_id, MONSTER_COMBAT_STATS_T i_combatStats, TYPE_BONUSES_T i_attackBonuses, TYPE_BONUSES_T i_defensiveBonuses, OTHER_BONUSES_T i_otherBonuses, std::vector<std::string> i_attributes);
  
  Monster(std::string i_name, int i_id, int i_combatAttack,  int i_combatStrength, int i_combatDefence, int i_combatMagic,  int i_combatRanged,  int i_combatHitpoints, int i_accuracy, int i_size,
                                        int i_attackStab,    int i_attackSlash,    int i_attackCrush,   int i_attackMagic,  int i_attackRanged,
                                        int i_defenceStab,   int i_defenceSlash,   int i_defenceCrush,  int i_defenceMagic, int i_defenceRanged,
                                        int i_meleeStrength, int i_rangedStrength, int i_magicDamage);
  Monster(std::string i_name, int i_id, int i_combatAttack,  int i_combatStrength, int i_combatDefence, int i_combatMagic,  int i_combatRanged,  int i_combatHitpoints, int i_accuracy, int i_size,
                                        int i_attackStab,    int i_attackSlash,    int i_attackCrush,   int i_attackMagic,  int i_attackRanged,
                                        int i_defenceStab,   int i_defenceSlash,   int i_defenceCrush,  int i_defenceMagic, int i_defenceRanged,
                                        int i_meleeStrength, int i_rangedStrength, int i_magicDamage,
                                        std::vector<std::string> i_attributes);  

  ~Monster();

  void SetName(std::string i_name);
  void SetId(int i_id);
  void SetStats(MONSTER_STATS_T i_stats);
  void SetAttributes(std::vector<std::string> i_attributes);

  void AddAttribute(std::string i_attribute);
  void AddAttributes(std::vector<std::string> i_attributes);

  const std::string& Name() const;
  const int& Id() const;
  const MONSTER_STATS_T& Stats() const;
  const std::vector<std::string>& Attributes() const;

  bool HasAttribute(std::string);

protected:
  std::string m_name;
  int m_id;
  MONSTER_STATS_T m_stats;
  std::vector<std::string> m_attributes;
};

#endif