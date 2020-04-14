#include "Player.h"

#include <iostream>
#include <cmath>

Player::Player()
{
  m_stats = {0};

  m_potions = {POTIONS_E::Type::NONE};

  m_prayer = {
    ATTACK_PRAYER_E::Type::NONE,
    STRENGTH_PRAYER_E::Type::NONE,
    DEFENCE_PRAYER_E::Type::NONE,
    RANGED_PRAYER_E::Type::NONE,
    MAGIC_PRAYER_E::Type::NONE
  };
}

Player::Player(PLAYER_STATS_T i_stats)
{
  m_stats = i_stats;

  m_potions = {POTIONS_E::Type::NONE};

  m_prayer = {
    ATTACK_PRAYER_E::Type::NONE,
    STRENGTH_PRAYER_E::Type::NONE,
    DEFENCE_PRAYER_E::Type::NONE,
    RANGED_PRAYER_E::Type::NONE,
    MAGIC_PRAYER_E::Type::NONE
  };
}

Player::Player(PLAYER_STATS_T i_stats, POTIONS_T i_potions, PRAYER_T i_prayer)
{
  m_stats = i_stats;
  m_potions = i_potions;
  m_prayer = i_prayer;
}

Player::Player(int i_attack, int i_strength, int i_defence, int i_ranged, int i_magic, int i_prayer, int i_hitpoints, int i_currentHitpoints)
{
  m_stats = {0};

  m_stats.Attack = i_attack;
  m_stats.Strength = i_strength;
  m_stats.Defence = i_defence;
  m_stats.Ranged = i_ranged;
  m_stats.Magic = i_magic;
  m_stats.Prayer = i_prayer;
  m_stats.Hitpoints = i_hitpoints;
  m_stats.CurrentHitpoints = i_currentHitpoints;

  m_potions = {POTIONS_E::Type::NONE};

  m_prayer = {
    ATTACK_PRAYER_E::Type::NONE,
    STRENGTH_PRAYER_E::Type::NONE,
    DEFENCE_PRAYER_E::Type::NONE,
    RANGED_PRAYER_E::Type::NONE,
    MAGIC_PRAYER_E::Type::NONE
  };
}

Player::Player(int i_attack, int i_strength, int i_defence, int i_ranged, int i_magic, int i_prayer, int i_hitpoints, int i_currentHitpoints,
               POTIONS_E::Type i_attackPotion, POTIONS_E::Type i_strengthPotion, POTIONS_E::Type i_defencePotion, POTIONS_E::Type i_rangedPotion, MAGIC_POTIONS_E::Type i_magicPotion,
               ATTACK_PRAYER_E::Type i_attackPrayer, STRENGTH_PRAYER_E::Type i_strengthPrayer, DEFENCE_PRAYER_E::Type i_defencePrayer, RANGED_PRAYER_E::Type i_rangedPrayer, MAGIC_PRAYER_E::Type i_magicPrayer)
{
  m_stats = {0};

  m_stats.Attack = i_attack;
  m_stats.Strength = i_strength;
  m_stats.Defence = i_defence;
  m_stats.Ranged = i_ranged;
  m_stats.Magic = i_magic;
  m_stats.Prayer = i_prayer;
  m_stats.Hitpoints = i_hitpoints;
  m_stats.CurrentHitpoints = i_currentHitpoints;

  m_potions = {
    i_attackPotion,
    i_strengthPotion,
    i_defencePotion,
    i_rangedPotion,
    i_magicPotion
  };
  
  m_prayer = {
    i_attackPrayer,
    i_strengthPrayer,
    i_defencePrayer,
    i_rangedPrayer,
    i_magicPrayer
  };
}

Player::~Player()
{
}

Player& Player::operator=(Player i_obj)
{
  if (&i_obj == this)
    return *this;

  m_stats = i_obj.Stats();
  m_potions = i_obj.Potions();
  m_prayer = i_obj.Prayer();

  return *this;
}

void Player::SetStats(PLAYER_STATS_T i_stats)
{
  m_stats = i_stats;
}
void Player::SetStats(int i_attack, int i_strength, int i_defence, int i_ranged, int i_magic, int i_prayer, int i_hitpoints)
{
  m_stats.Attack = i_attack;
  m_stats.Strength = i_strength;
  m_stats.Defence = i_defence;
  m_stats.Ranged = i_ranged;
  m_stats.Magic = i_magic;
  m_stats.Prayer = i_prayer;
  m_stats.Hitpoints = i_hitpoints;
}

void Player::SetPotions(POTIONS_T i_potions)
{
  m_potions = i_potions;
}
void Player::SetPotions(POTIONS_E::Type i_attackPotion, POTIONS_E::Type i_strengthPotion, POTIONS_E::Type i_defencePotion, POTIONS_E::Type i_rangedPotion, MAGIC_POTIONS_E::Type i_magicPotion)
{
  m_potions.AttackPotion = i_attackPotion;
  m_potions.StrengthPotion = i_strengthPotion;
  m_potions.DefencePotion = i_defencePotion;
  m_potions.RangedPotion = i_rangedPotion;
  m_potions.MagicPotion = i_magicPotion;
}

void Player::SetPrayer(PRAYER_T i_prayer)
{
  m_prayer = i_prayer;
}
void Player::SetPrayer(ATTACK_PRAYER_E::Type i_attackPrayer, STRENGTH_PRAYER_E::Type i_strengthPrayer, DEFENCE_PRAYER_E::Type i_defencePrayer, RANGED_PRAYER_E::Type i_rangedPrayer, MAGIC_PRAYER_E::Type i_magicPrayer)
{
  m_prayer.AttackPrayer = i_attackPrayer;
  m_prayer.StrengthPrayer = i_strengthPrayer;
  m_prayer.DefencePrayer = i_defencePrayer;
  m_prayer.RangedPrayer = i_rangedPrayer;
  m_prayer.MagicPrayer = i_magicPrayer;
}

PLAYER_STATS_T Player::Stats() const
{
  return m_stats;
}

POTIONS_T Player::Potions() const
{
  return m_potions;
}

PRAYER_T Player::Prayer() const
{
  return m_prayer;
}

void Player::SetAttack(int i_attack)
{
  m_stats.Attack = i_attack;
}
void Player::SetStrength(int i_strength)
{
  m_stats.Strength = i_strength;
}
void Player::SetDefence(int i_defence)
{
  m_stats.Defence = i_defence;
}
void Player::SetRanged(int i_ranged)
{
  m_stats.Ranged = i_ranged;
}
void Player::SetMagic(int i_magic)
{
  m_stats.Magic = i_magic;
}
void Player::SetPrayer(int i_prayer)
{
  m_stats.Prayer = i_prayer;
}
void Player::SetHitpoints(int i_hitpoints)
{
  m_stats.Hitpoints = i_hitpoints;
}
void Player::SetCurrentHitpoints(int i_currentHitpoints)
{
  m_stats.CurrentHitpoints = i_currentHitpoints;
}

void Player::SetAttackPotion(POTIONS_E::Type i_attackPotion)
{
  m_potions.AttackPotion = i_attackPotion;
}
void Player::SetStrengthPotion(POTIONS_E::Type i_strengthPotion)
{
  m_potions.StrengthPotion = i_strengthPotion;
}
void Player::SetDefencePotion(POTIONS_E::Type i_defencePotion)
{
  m_potions.DefencePotion = i_defencePotion;
}
void Player::SetRangedPotion(POTIONS_E::Type i_rangedPotion)
{
  m_potions.RangedPotion = i_rangedPotion;
}
void Player::SetMagicPotion(MAGIC_POTIONS_E::Type i_magicPotion)
{
  m_potions.MagicPotion = i_magicPotion;
}

void Player::SetAttackPrayer(ATTACK_PRAYER_E::Type i_attackPrayer)
{
  m_prayer.AttackPrayer = i_attackPrayer;
}
void Player::SetStrengthPrayer(STRENGTH_PRAYER_E::Type i_strengthPrayer)
{
  m_prayer.StrengthPrayer = i_strengthPrayer;
}
void Player::SetDefencePrayer(DEFENCE_PRAYER_E::Type i_defencePrayer)
{
  m_prayer.DefencePrayer = i_defencePrayer;
}
void Player::SetRangedPrayer(RANGED_PRAYER_E::Type i_rangedPrayer)
{
  m_prayer.RangedPrayer = i_rangedPrayer;
}
void Player::SetMagicPrayer(MAGIC_PRAYER_E::Type i_magicPrayer)
{
  m_prayer.MagicPrayer = i_magicPrayer;
}