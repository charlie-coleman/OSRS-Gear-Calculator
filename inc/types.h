#ifndef TYPES_H
#define TYPES_H

#include "enums.h"

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

struct EQUIPMENT_STATS_T
{
  TYPE_BONUSES_T AttackBonuses;
  TYPE_BONUSES_T DefenseBonuses;
  OTHER_BONUSES_T OtherBonuses;
};

struct PLAYER_STATS_T
{
  int Attack;
  int Strength;
  int Defense;
  int Ranged;
  int RangedStrength;
  int Magic;
  int Prayer;
  int Hitpoints;
};

struct POTIONS_T
{
  POTIONS_E::Type AttackPotion;
  POTIONS_E::Type StrengthPotion;
  POTIONS_E::Type DefensePotion;
  POTIONS_E::Type RangedPotion;
  MAGIC_POTIONS_E::Type MagicPotion;
};

struct PRAYER_T
{
  ATTACK_PRAYER_E::Type AttackPrayer;
  STRENGTH_PRAYER_E::Type StrengthPrayer;
  DEFENSE_PRAYER_E::Type DefensePrayer;
  RANGED_PRAYER_E::Type RangedPrayer;
  MAGIC_PRAYER_E::Type MagicPrayer;
};

#endif