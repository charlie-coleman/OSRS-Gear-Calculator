#ifndef TYPES_H
#define TYPES_H

#include "enums.h"
#include <string>
#include <vector>

#include <iostream>

struct TYPE_BONUSES_T
{
  int Stab;
  int Slash;
  int Crush;
  int Magic;
  int Ranged;
};

struct OTHER_BONUSES_T
{
  int Strength;
  int RangedStrength;
  int MagicDamage;
  int Prayer;
};

struct STANCE_T
{
  std::string AttackStyle;
  std::string AttackType;
  std::string Boosts;
  std::string CombatStyle;
  std::string Experience;
};

struct WEAPON_STATS_T
{
  int AttackSpeed;
  std::vector<STANCE_T> Stances;
};

struct EQUIPMENT_STATS_T
{
  TYPE_BONUSES_T AttackBonuses;
  TYPE_BONUSES_T DefenceBonuses;
  OTHER_BONUSES_T OtherBonuses;
};

struct PLAYER_STATS_T
{
  int Attack;
  int Strength;
  int Defence;
  int Ranged;
  int Magic;
  int Prayer;
  int Hitpoints;
  int CurrentHitpoints;

  PLAYER_STATS_T& operator=(PLAYER_STATS_T i_stats)
  {
    Attack = i_stats.Attack;
    Strength = i_stats.Strength;
    Defence = i_stats.Defence;
    Ranged = i_stats.Ranged;
    Magic = i_stats.Magic;
    Prayer = i_stats.Prayer;
    Hitpoints = i_stats.Hitpoints;
    CurrentHitpoints = i_stats.CurrentHitpoints;

    return *this;
  }
};

struct POTIONS_T
{
  POTIONS_E::Type AttackPotion;
  POTIONS_E::Type StrengthPotion;
  POTIONS_E::Type DefencePotion;
  POTIONS_E::Type RangedPotion;
  MAGIC_POTIONS_E::Type MagicPotion;
};

struct PRAYER_T
{
  ATTACK_PRAYER_E::Type AttackPrayer;
  STRENGTH_PRAYER_E::Type StrengthPrayer;
  DEFENCE_PRAYER_E::Type DefencePrayer;
  RANGED_PRAYER_E::Type RangedPrayer;
  MAGIC_PRAYER_E::Type MagicPrayer;
};

struct MONSTER_COMBAT_STATS_T
{
  int Hitpoints;
  int Attack;
  int Strength;
  int Defence;
  int Magic;
  int Ranged;
  int Accuracy;
  int Size;
};

struct MONSTER_STATS_T
{
  MONSTER_COMBAT_STATS_T CombatStats;
  TYPE_BONUSES_T AttackBonuses;
  TYPE_BONUSES_T DefensiveBonuses;
  OTHER_BONUSES_T OtherBonuses;
};

#endif