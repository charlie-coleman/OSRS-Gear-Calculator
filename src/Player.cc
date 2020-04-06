#include "Player.h"

#include <cmath>

Player::Player()
{
  m_stats = {0};

  m_potions = {POTIONS_E::Type::NONE};

  m_prayer = {
    ATTACK_PRAYER_E::Type::NONE,
    STRENGTH_PRAYER_E::Type::NONE,
    DEFENSE_PRAYER_E::Type::NONE,
    RANGED_PRAYER_E::Type::NONE,
    MAGIC_PRAYER_E::Type::NONE
  };

  CalculateEffectiveStats();
}

Player::Player(PLAYER_STATS_T i_stats)
{
  m_stats = i_stats;

  m_potions = {POTIONS_E::Type::NONE};

  m_prayer = {
    ATTACK_PRAYER_E::Type::NONE,
    STRENGTH_PRAYER_E::Type::NONE,
    DEFENSE_PRAYER_E::Type::NONE,
    RANGED_PRAYER_E::Type::NONE,
    MAGIC_PRAYER_E::Type::NONE
  };

  CalculateEffectiveStats();
}

Player::Player(PLAYER_STATS_T i_stats, POTIONS_T i_potions, PRAYER_T i_prayer)
  : Player(i_stats)
{
  m_potions = i_potions;
  m_prayer = i_prayer;

  CalculateEffectiveStats();
}

Player::Player(int i_attack, int i_strength, int i_defense, int i_ranged, int i_magic, int i_prayer, int i_hitpoints)
{
  m_stats = {
    i_attack,
    i_strength,
    i_defense,
    i_ranged,
    i_magic,
    i_prayer,
    i_hitpoints
  };

  m_potions = {POTIONS_E::Type::NONE};

  m_prayer = {
    ATTACK_PRAYER_E::Type::NONE,
    STRENGTH_PRAYER_E::Type::NONE,
    DEFENSE_PRAYER_E::Type::NONE,
    RANGED_PRAYER_E::Type::NONE,
    MAGIC_PRAYER_E::Type::NONE
  };

  CalculateEffectiveStats();
}

Player::Player(int i_attack, int i_strength, int i_defense, int i_ranged, int i_magic, int i_prayer, int i_hitpoints,
               POTIONS_E::Type i_attackPotion, POTIONS_E::Type i_strengthPotion, POTIONS_E::Type i_defensePotion, POTIONS_E::Type i_rangedPotion, MAGIC_POTIONS_E::Type i_magicPotion,
               ATTACK_PRAYER_E::Type i_attackPrayer, STRENGTH_PRAYER_E::Type i_strengthPrayer, DEFENSE_PRAYER_E::Type i_defensePrayer, RANGED_PRAYER_E::Type i_rangedPrayer, MAGIC_PRAYER_E::Type i_magicPrayer)
  : Player(i_attack, i_strength, i_defense, i_ranged, i_magic, i_prayer, i_hitpoints)
{
  m_potions = {
    i_attackPotion,
    i_strengthPotion,
    i_defensePotion,
    i_rangedPotion,
    i_magicPotion
  };
  
  m_prayer = {
    i_attackPrayer,
    i_strengthPrayer,
    i_defensePrayer,
    i_rangedPrayer,
    i_magicPrayer
  };

  CalculateEffectiveStats();
}

Player::~Player()
{
}

void Player::SetStats(PLAYER_STATS_T i_stats)
{
  m_stats = i_stats;

  CalculateEffectiveStats();
}
void Player::SetStats(int i_attack, int i_strength, int i_defense, int i_ranged, int i_magic, int i_prayer, int i_hitpoints)
{
  m_stats.Attack = i_attack;
  m_stats.Strength = i_strength;
  m_stats.Defense = i_defense;
  m_stats.Ranged = m_stats.RangedStrength = i_ranged;
  m_stats.Magic = i_magic;
  m_stats.Prayer = i_prayer;
  m_stats.Hitpoints = i_hitpoints;

  CalculateEffectiveStats();
}

void Player::SetPotions(POTIONS_T i_potions)
{
  m_potions = i_potions;

  CalculateEffectiveStats();
}
void Player::SetPotions(POTIONS_E::Type i_attackPotion, POTIONS_E::Type i_strengthPotion, POTIONS_E::Type i_defensePotion, POTIONS_E::Type i_rangedPotion, MAGIC_POTIONS_E::Type i_magicPotion)
{
  m_potions.AttackPotion = i_attackPotion;
  m_potions.StrengthPotion = i_strengthPotion;
  m_potions.DefensePotion = i_defensePotion;
  m_potions.RangedPotion = i_rangedPotion;
  m_potions.MagicPotion = i_magicPotion;

  CalculateEffectiveStats();
}

void Player::SetPrayer(PRAYER_T i_prayer)
{
  m_prayer = i_prayer;

  CalculateEffectiveStats();
}
void Player::SetPrayer(ATTACK_PRAYER_E::Type i_attackPrayer, STRENGTH_PRAYER_E::Type i_strengthPrayer, DEFENSE_PRAYER_E::Type i_defensePrayer, RANGED_PRAYER_E::Type i_rangedPrayer, MAGIC_PRAYER_E::Type i_magicPrayer)
{
  m_prayer.AttackPrayer = i_attackPrayer;
  m_prayer.StrengthPrayer = i_strengthPrayer;
  m_prayer.DefensePrayer = i_defensePrayer;
  m_prayer.RangedPrayer = i_rangedPrayer;
  m_prayer.MagicPrayer = i_magicPrayer;

  CalculateEffectiveStats();
}

const PLAYER_STATS_T& Player::Stats() const
{
  return m_stats;
}

const PLAYER_STATS_T& Player::EffectiveStats() const
{
  return m_effectiveStats;
}

void Player::CalculateEffectiveStats()
{
  PLAYER_STATS_T newStats = {0};

  newStats.Attack = CalculateEffectiveAttackLevel();
  newStats.Strength = CalculateEffectiveStrengthLevel();
  newStats.Defense = CalculateEffectiveDefenseLevel();
  newStats.Ranged = CalculateEffectiveRangedLevel();
  newStats.RangedStrength = CalculateEffectiveRangedStrength();
  newStats.Magic = CalculateEffectiveMagicLevel();

  m_effectiveStats = newStats;
}

int Player::CalculateEffectiveAttackLevel()
{
  float playerLevel = Stats().Attack;

  float pottedLevel = 0.0f;
  switch (m_potions.AttackPotion)
  {
    case POTIONS_E::Type::REGULAR_POTION:
      pottedLevel = std::floor(1.1 * playerLevel) + 3;
      break;
    case POTIONS_E::Type::SUPER_POTION:
      pottedLevel = std::floor(1.15 * playerLevel) + 5;
      break;
    case POTIONS_E::Type::OVERLOAD_MINUS:
      pottedLevel = std::floor(1.1 * playerLevel) + 4;
      break;
    case POTIONS_E::Type::OVERLOAD:
      pottedLevel = std::floor(1.13 * playerLevel) + 5;
      break;
    case POTIONS_E::Type::OVERLOAD_PLUS:
      pottedLevel = std::floor(1.16 * playerLevel) + 6;
      break;
    case POTIONS_E::Type::NONE:
    default:
      pottedLevel = playerLevel;
      break;
  }

  float effectiveLevel = 0.0f;
  switch (m_prayer.AttackPrayer)
  {
    case ATTACK_PRAYER_E::CLARITY_OF_THOUGHT:
      effectiveLevel = std::floor(1.05 * pottedLevel);
      break;
    case ATTACK_PRAYER_E::IMPROVED_REFLEXES:
      effectiveLevel = std::floor(1.10 * pottedLevel);
      break;
    case ATTACK_PRAYER_E::INCREDIBLE_REFLEXES:
    case ATTACK_PRAYER_E::CHIVALRY:
      effectiveLevel = std::floor(1.15 * pottedLevel);
      break;
    case ATTACK_PRAYER_E::PIETY:
      effectiveLevel = std::floor(1.20 * pottedLevel);
      break;
    case ATTACK_PRAYER_E::NONE:
    default:
      effectiveLevel = pottedLevel;
      break;
  }

  return (int)effectiveLevel;
}

int Player::CalculateEffectiveStrengthLevel()
{
  float playerLevel = Stats().Strength;

  float pottedLevel = 0.0f;
  switch (m_potions.StrengthPotion)
  {
    case POTIONS_E::Type::REGULAR_POTION:
      pottedLevel = std::floor(1.1 * playerLevel) + 3;
      break;
    case POTIONS_E::Type::SUPER_POTION:
      pottedLevel = std::floor(1.15 * playerLevel) + 5;
      break;
    case POTIONS_E::Type::OVERLOAD_MINUS:
      pottedLevel = std::floor(1.1 * playerLevel) + 4;
      break;
    case POTIONS_E::Type::OVERLOAD:
      pottedLevel = std::floor(1.13 * playerLevel) + 5;
      break;
    case POTIONS_E::Type::OVERLOAD_PLUS:
      pottedLevel = std::floor(1.16 * playerLevel) + 6;
      break;
    case POTIONS_E::Type::NONE:
    default:
      pottedLevel = playerLevel;
      break;
  }

  float effectiveLevel = 0.0f;
  switch (m_prayer.StrengthPrayer)
  {
    case STRENGTH_PRAYER_E::BURST_OF_STRENGTH:
      effectiveLevel = std::floor(1.05 * pottedLevel);
      break;
    case STRENGTH_PRAYER_E::SUPERHUMAN_STRENGTH:
      effectiveLevel = std::floor(1.10 * pottedLevel);
      break;
    case STRENGTH_PRAYER_E::ULTIMATE_STRENGTH:
      effectiveLevel = std::floor(1.15 * pottedLevel);
      break;
    case STRENGTH_PRAYER_E::CHIVALRY:
      effectiveLevel = std::floor(1.18 * pottedLevel);
      break;
    case STRENGTH_PRAYER_E::PIETY:
      effectiveLevel = std::floor(1.23 * pottedLevel);
      break;
    case STRENGTH_PRAYER_E::NONE:
    default:
      effectiveLevel = pottedLevel;
      break;
  }

  return (int)effectiveLevel;
}

int Player::CalculateEffectiveDefenseLevel()
{
  float playerLevel = Stats().Defense;

  float pottedLevel = 0.0f;
  switch (m_potions.DefensePotion)
  {
    case POTIONS_E::Type::REGULAR_POTION:
      pottedLevel = std::floor(1.1 * playerLevel) + 3;
      break;
    case POTIONS_E::Type::SUPER_POTION:
      pottedLevel = std::floor(1.15 * playerLevel) + 5;
      break;
    case POTIONS_E::Type::OVERLOAD_MINUS:
      pottedLevel = std::floor(1.1 * playerLevel) + 4;
      break;
    case POTIONS_E::Type::OVERLOAD:
      pottedLevel = std::floor(1.13 * playerLevel) + 5;
      break;
    case POTIONS_E::Type::OVERLOAD_PLUS:
      pottedLevel = std::floor(1.16 * playerLevel) + 6;
      break;
    case POTIONS_E::Type::NONE:
    default:
      pottedLevel = playerLevel;
      break;
  }

  float effectiveLevel = 0.0f;
  switch (m_prayer.DefensePrayer)
  {
    case DEFENSE_PRAYER_E::THICK_SKIN:
      effectiveLevel = std::floor(1.05 * pottedLevel);
      break;
    case DEFENSE_PRAYER_E::ROCK_SKIN:
      effectiveLevel = std::floor(1.10 * pottedLevel);
      break;
    case DEFENSE_PRAYER_E::STEEL_SKIN:
      effectiveLevel = std::floor(1.15 * pottedLevel);
      break;
    case DEFENSE_PRAYER_E::CHIVALRY:
      effectiveLevel = std::floor(1.20 * pottedLevel);
      break;
    case DEFENSE_PRAYER_E::PIETY:
      effectiveLevel = std::floor(1.25 * pottedLevel);
      break;
    case DEFENSE_PRAYER_E::NONE:
    default:
      effectiveLevel = pottedLevel;
      break;
  }

  return (int)effectiveLevel;
}

int Player::CalculateEffectiveRangedLevel()
{
  float playerLevel = Stats().Ranged;

  float pottedLevel = 0.0f;
  switch (m_potions.RangedPotion)
  {
    case POTIONS_E::Type::REGULAR_POTION:
      pottedLevel = std::floor(1.1 * playerLevel) + 4;
      break;
    case POTIONS_E::Type::SUPER_POTION:
      pottedLevel = std::floor(1.15 * playerLevel) + 5;
      break;
    case POTIONS_E::Type::OVERLOAD_MINUS:
      pottedLevel = std::floor(1.1 * playerLevel) + 4;
      break;
    case POTIONS_E::Type::OVERLOAD:
      pottedLevel = std::floor(1.13 * playerLevel) + 5;
      break;
    case POTIONS_E::Type::OVERLOAD_PLUS:
      pottedLevel = std::floor(1.16 * playerLevel) + 6;
      break;
    case POTIONS_E::Type::NONE:
    default:
      pottedLevel = playerLevel;
      break;
  }

  float effectiveLevel = 0.0f;
  switch (m_prayer.RangedPrayer)
  {
    case RANGED_PRAYER_E::SHARP_EYE:
      effectiveLevel = std::floor(1.05 * pottedLevel);
      break;
    case RANGED_PRAYER_E::HAWK_EYE:
      effectiveLevel = std::floor(1.10 * pottedLevel);
      break;
    case RANGED_PRAYER_E::EAGLE_EYE:
      effectiveLevel = std::floor(1.15 * pottedLevel);
      break;
    case RANGED_PRAYER_E::RIGOUR:
      effectiveLevel = std::floor(1.20 * pottedLevel);
      break;
    case DEFENSE_PRAYER_E::NONE:
    default:
      effectiveLevel = pottedLevel;
      break;
  }

  return (int)effectiveLevel;
}

int Player::CalculateEffectiveRangedStrength()
{
  float playerLevel = Stats().RangedStrength;

  float pottedLevel = 0.0f;
  switch (m_potions.RangedPotion)
  {
    case POTIONS_E::Type::REGULAR_POTION:
      pottedLevel = std::floor(1.1 * playerLevel) + 4;
      break;
    case POTIONS_E::Type::SUPER_POTION:
      pottedLevel = std::floor(1.15 * playerLevel) + 5;
      break;
    case POTIONS_E::Type::OVERLOAD_MINUS:
      pottedLevel = std::floor(1.1 * playerLevel) + 4;
      break;
    case POTIONS_E::Type::OVERLOAD:
      pottedLevel = std::floor(1.13 * playerLevel) + 5;
      break;
    case POTIONS_E::Type::OVERLOAD_PLUS:
      pottedLevel = std::floor(1.16 * playerLevel) + 6;
      break;
    case POTIONS_E::Type::NONE:
    default:
      pottedLevel = playerLevel;
      break;
  }

  float effectiveLevel = 0.0f;
  switch (m_prayer.RangedPrayer)
  {
    case RANGED_PRAYER_E::SHARP_EYE:
      effectiveLevel = std::floor(1.05 * pottedLevel);
      break;
    case RANGED_PRAYER_E::HAWK_EYE:
      effectiveLevel = std::floor(1.10 * pottedLevel);
      break;
    case RANGED_PRAYER_E::EAGLE_EYE:
      effectiveLevel = std::floor(1.15 * pottedLevel);
      break;
    case RANGED_PRAYER_E::RIGOUR:
      effectiveLevel = std::floor(1.23 * pottedLevel);
      break;
    case DEFENSE_PRAYER_E::NONE:
    default:
      effectiveLevel = pottedLevel;
      break;
  }

  return (int)effectiveLevel;
}

int Player::CalculateEffectiveMagicLevel()
{
  float playerLevel = Stats().Magic;

  float pottedLevel = 0.0f;
  switch (m_potions.MagicPotion)
  {
    case MAGIC_POTIONS_E::Type::REGULAR_POTION:
      pottedLevel = playerLevel + 4;
      break;
    case MAGIC_POTIONS_E::Type::SUPER_POTION:
      pottedLevel = std::floor(1.15 * playerLevel) + 5;
      break;
    case MAGIC_POTIONS_E::Type::IMBUED_HEART:
      pottedLevel = std::floor(1.1 * playerLevel) + 1;
      break;
    case MAGIC_POTIONS_E::Type::OVERLOAD_MINUS:
      pottedLevel = std::floor(1.1 * playerLevel) + 4;
      break;
    case MAGIC_POTIONS_E::Type::OVERLOAD:
      pottedLevel = std::floor(1.13 * playerLevel) + 5;
      break;
    case MAGIC_POTIONS_E::Type::OVERLOAD_PLUS:
      pottedLevel = std::floor(1.16 * playerLevel) + 6;
      break;
    case MAGIC_POTIONS_E::Type::NONE:
    default:
      pottedLevel = playerLevel;
      break;
  }

  float effectiveLevel = 0.0f;
  switch (m_prayer.MagicPrayer)
  {
    case MAGIC_PRAYER_E::MYSTIC_WILL:
      effectiveLevel = std::floor(1.05 * pottedLevel);
      break;
    case MAGIC_PRAYER_E::MYSTIC_LORE:
      effectiveLevel = std::floor(1.10 * pottedLevel);
      break;
    case MAGIC_PRAYER_E::MYSTIC_MIGHT:
      effectiveLevel = std::floor(1.15 * pottedLevel);
      break;
    case MAGIC_PRAYER_E::AUGURY:
      effectiveLevel = std::floor(1.25 * pottedLevel);
      break;
    case MAGIC_PRAYER_E::NONE:
    default:
      effectiveLevel = pottedLevel;
      break;
  }

  return (int)effectiveLevel;
}