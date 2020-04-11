#include "Setup.h"

#include <iostream>
#include <cmath>
#include <algorithm>

Setup::Setup()
  : m_onSlayerTask(false),
    m_isOneHanded(false),
    m_weaponStance(0)
{
}

Setup::Setup(Player i_player,      Monster i_monster,
             Equipment i_ammoSlot, Equipment i_bodySlot,   Equipment i_capeSlot,   Equipment i_feetSlot,
             Equipment i_handSlot, Equipment i_headSlot,   Equipment i_legsSlot,   Equipment i_neckSlot,
             Equipment i_ringSlot, Equipment i_shieldSlot, Weapon i_oneHandedSlot)
  : m_onSlayerTask(false),
    m_isOneHanded(true),
    m_weaponStance(0)
{
  m_player = i_player;
  m_monster = i_monster;
  m_ammoSlot = i_ammoSlot;
  m_bodySlot = i_bodySlot;
  m_capeSlot = i_capeSlot;
  m_feetSlot = i_feetSlot;
  m_handSlot = i_handSlot;
  m_headSlot = i_headSlot;
  m_legsSlot = i_legsSlot;
  m_neckSlot = i_neckSlot;
  m_ringSlot = i_ringSlot;
  m_shieldSlot = i_shieldSlot;
  m_oneHandedSlot = i_oneHandedSlot;

}

Setup::Setup(Player i_player,      Monster i_monster,
             Equipment i_ammoSlot, Equipment i_bodySlot,   Equipment i_capeSlot,   Equipment i_feetSlot,
             Equipment i_handSlot, Equipment i_headSlot,   Equipment i_legsSlot,   Equipment i_neckSlot,
             Equipment i_ringSlot, Weapon i_twoHandedSlot)
  : m_onSlayerTask(false),
    m_isOneHanded(false),
    m_weaponStance(0)
{
  m_player = i_player;
  m_monster = i_monster;
  m_ammoSlot = i_ammoSlot;
  m_bodySlot = i_bodySlot;
  m_capeSlot = i_capeSlot;
  m_feetSlot = i_feetSlot;
  m_handSlot = i_handSlot;
  m_headSlot = i_headSlot;
  m_legsSlot = i_legsSlot;
  m_neckSlot = i_neckSlot;
  m_ringSlot = i_ringSlot;
  m_twoHandedSlot = i_twoHandedSlot;

  m_currentHitpoints = m_player.Stats().Hitpoints;
}

Setup::~Setup()
{
}

int Setup::GetMaxHit()
{
  return CalculateMeleeMaxHit();
}

int Setup::CalculateMeleeMaxHit()
{
  int strengthLevel = m_player.Stats().Strength;

  int effectiveStrength = CalculateEffectiveMeleeStrength();

  int strengthBonus = 0;

  strengthBonus += m_ammoSlot.Stats().OtherBonuses.Strength;
  strengthBonus += m_bodySlot.Stats().OtherBonuses.Strength;
  strengthBonus += m_capeSlot.Stats().OtherBonuses.Strength;
  strengthBonus += m_feetSlot.Stats().OtherBonuses.Strength;
  strengthBonus += m_handSlot.Stats().OtherBonuses.Strength;
  strengthBonus += m_headSlot.Stats().OtherBonuses.Strength;
  strengthBonus += m_legsSlot.Stats().OtherBonuses.Strength;
  strengthBonus += m_neckSlot.Stats().OtherBonuses.Strength;
  strengthBonus += m_ringSlot.Stats().OtherBonuses.Strength;

  Weapon weap;
  if (!m_isOneHanded)
  {
    weap = m_twoHandedSlot;
  }
  else
  {
    strengthBonus += m_shieldSlot.Stats().OtherBonuses.Strength;
    weap = m_oneHandedSlot;
  }

  strengthBonus += weap.Stats().OtherBonuses.Strength;

  int baseDamage = std::floor(0.5 + effectiveStrength * (64.0 + strengthBonus) / 640.0);

  // FIRST ROUND OF SPECIAL MODIFIERS
  // PICK ONE BONUS: Salve, Salve (e), or Black Mask
  // Salve has priority over Black Mask

  float firstBonus = 1.0;

  bool isUndead = m_monster.HasAttribute("undead");
  bool isDemon = m_monster.HasAttribute("demon");
  bool isLeafy = m_monster.HasAttribute("leafy");
  bool isShady = m_monster.HasAttribute("shade");
  bool isKalphite = m_monster.HasAttribute("kalphite");

  if (isUndead && (m_neckSlot.Id() == 4081 || m_neckSlot.Id() == 12017)) // Salve
  {
    firstBonus = 7.0/6.0;
  }
  else if (isUndead && (m_neckSlot.Id() == 10588 || m_neckSlot.Id() == 12018)) // Salve (e)
  {
    firstBonus = 1.2;
  }
  else if (m_onSlayerTask &&
    ((m_headSlot.Id() >= 8901 && m_headSlot.Id() <= 8922) || // Black mask (10-0)
     (m_headSlot.Id() >= 11774 && m_headSlot.Id() <= 11784) || // Blackmask (10-0) (i)
     (m_headSlot.Id() == 11864 || m_headSlot.Id() == 11865) || // Reg Slayer helmet + (i)
     (m_headSlot.Id() == 19639 || m_headSlot.Id() == 19641) || // Black Slayer helmet + (i)
     (m_headSlot.Id() == 19643 || m_headSlot.Id() == 19645) || // Green Slayer helmet + (i)
     (m_headSlot.Id() == 19647 || m_headSlot.Id() == 19649) || // Red Slayer helmet + (i)
     (m_headSlot.Id() == 21264 || m_headSlot.Id() == 21266) || // Purple Slayer helmet + (i)
     (m_headSlot.Id() == 21888 || m_headSlot.Id() == 21890) || // Turquoise Slayer helmet + (i)
     (m_headSlot.Id() == 23073 || m_headSlot.Id() == 23075) || // Hydra Slayer helmet + (i)
     (m_headSlot.Id() == 24370 || m_headSlot.Id() == 24444))) // Twisted Slayer helmet + (i)
  {

    std::cout << "on task in mask" << std::endl;
    firstBonus = 7.0/6.0;
  }

  int firstBonusDamage = std::floor(firstBonus * baseDamage);

  // SECOND ROUND OF SPECIAL MODIFIERS
  // Not accounting for special attacks here, the main ones are Arclight, Leaf-bladed battleaxe, and obby armour + obby weapon

  float secondBonus = 1.0;

  if (weap.Id() == 19675 && isDemon) // if weapon == arclight and enemy is a demon
  {
    secondBonus = 1.70;
  }
  else if (weap.Id() == 20727 && isLeafy) // if weapon == leaf-bladed baxe and the enemy is "leafy"
  {
    secondBonus = 1.175;
  }
  else if ((weap.Id() == 6523 || weap.Id() == 6525 || weap.Id() == 6527 || weap.Id() == 6528) && // Obsidian melee weapon
           (m_headSlot.Id() == 21298 && m_bodySlot.Id() == 21301 && m_legsSlot.Id() == 21304))   // Obsidian armour set
  {
    secondBonus = 1.10;
  }

  int secondBonusDamage = std::floor(secondBonus * firstBonusDamage);

  // THIRD ROUND OF SPECIAL MODIFIERS
  // Again, not accounting for special attacks here. Main items are darklight, dharok's, zerker neck

  float thirdBonus = 1.0;

  if ((m_headSlot.Id() == 4716 || (m_headSlot.Id() >= 4880 && m_headSlot.Id() <= 4884)) && // Dharok's helm (100/75/50/25/0)
      (weap.Id()       == 4718 || (weap.Id()       >= 4886 && weap.Id()       <= 4890)) && // Dharok's greataxe (100/75/50/25/0)
      (m_bodySlot.Id() == 4720 || (m_bodySlot.Id() >= 4892 && m_bodySlot.Id() <= 4896)) && // Dharok's platebody (100/75/50/25/0)
      (m_legsSlot.Id() == 4722 || (m_legsSlot.Id() >= 4898 && m_legsSlot.Id() <= 4902)))   // Dharok's platelegs (100/75/50/25/0)
  {
    int maxHP = m_player.Stats().Hitpoints;

    int missingHitpoints = maxHP - m_currentHitpoints;
    missingHitpoints = (missingHitpoints < 0) ? 0 : missingHitpoints;
    
    thirdBonus = 1.0 + ((missingHitpoints / 100.0) * (maxHP / 100.0));
  }
  else if ((weap.Id() == 6523 || weap.Id() == 6525 || weap.Id() == 6527 || weap.Id() == 6528) && // Obsidian weapons
           (m_neckSlot.Id() == 11128 || m_neckSlot.Id() == 23240))                               // Berserker necklace or Berserker necklace (or)
  {
    thirdBonus = 1.20;   
  }
  else if (weap.Id() == 6746 && isDemon) // if weapon == darklight and enemy is a demon
  {
    thirdBonus = 1.60;
  }
  else if (weap.Id() == 7668 && isShady) // if weapon == gadderhammer and enemy is a shade (morton)
  {
    thirdBonus = 1.25;
  }
  else if ((weap.Id() >= 10581 && weap.Id() <= 10584) && isKalphite) // if weapon == keris (p/p+/p++) and enemy is a kalphite creature
  {
    thirdBonus = 4.0/3.0;
  }

  int maxHit = std::floor(thirdBonus * secondBonusDamage);

  return maxHit;
}

int Setup::CalculateEffectiveMeleeStrength()
{
  int strLevel = m_player.Stats().Strength;

  int potionBonus = 0;
  switch(m_player.Potions().StrengthPotion)
  {
    case POTIONS_E::REGULAR_POTION:
      potionBonus = 3 + std::floor(0.10 * strLevel);
      break;
    case POTIONS_E::SUPER_POTION:
      potionBonus = 5 + std::floor(0.15 * strLevel);
      break;
    case POTIONS_E::OVERLOAD_MINUS:
      potionBonus = 4 + std::floor(0.10 * strLevel);
      break;
    case POTIONS_E::OVERLOAD:
      potionBonus = 5 + std::floor(0.13 * strLevel);
      break;
    case POTIONS_E::OVERLOAD_PLUS:
      potionBonus = 6 + std::floor(0.16 * strLevel);
      break;
    case POTIONS_E::NONE:
    default:
      potionBonus = 0;
  }

  float prayerBonus = 1.0;
  switch (m_player.Prayer().StrengthPrayer)
  {
    case STRENGTH_PRAYER_E::BURST_OF_STRENGTH:
      prayerBonus = 1.05;
      break;
    case STRENGTH_PRAYER_E::SUPERHUMAN_STRENGTH:
      prayerBonus = 1.10;
      break;
    case STRENGTH_PRAYER_E::ULTIMATE_STRENGTH:
      prayerBonus = 1.15;
      break;
    case STRENGTH_PRAYER_E::CHIVALRY:
      prayerBonus = 1.18;
      break;
    case STRENGTH_PRAYER_E::PIETY:
      prayerBonus = 1.23;
      break;
    case STRENGTH_PRAYER_E::NONE:
    default:
      prayerBonus = 1.0;
      break;
  }

  float otherBonus = 1.0;

  if (m_headSlot.Id() == 11665 && // Void melee helm
     (m_bodySlot.Id() == 8839 || m_bodySlot.Id() == 13072) &&  // Void knight top or Elite void top
     (m_legsSlot.Id() == 8840 || m_legsSlot.Id() == 13073) &&  // Void knight robe or Elite void robe
      m_handSlot.Id() == 8842)    // Void knight gloves
  {
    otherBonus *= 1.1;
  }

  int styleBonus = 0;

  Weapon weap;
  if (!m_isOneHanded)
  {
    weap = m_twoHandedSlot;
  }
  else
  {
    weap = m_oneHandedSlot;
  }

  STANCE_T stance = weap.WeaponStats().Stances[m_weaponStance];

  if (stance.AttackStyle == "aggressive")
  {
    styleBonus = 11;
  }
  else if (stance.AttackStyle == "controlled")
  {
    styleBonus = 9;
  }
  else
  {
    styleBonus = 8;
  }

  int effectiveStrength = std::floor((strLevel + potionBonus) * prayerBonus * otherBonus) + styleBonus;
  return effectiveStrength;
}

float Setup::CalculateMeleeAccuracy()
{
  return 0.0f;
}

int Setup::CalculateEffectiveAttackLevel()
{
  int attackLevel = m_player.Stats().Attack;

  int potionBonus = 0;
  switch (m_player.Potions().AttackPotion)
  {
    case POTIONS_E::REGULAR_POTION:
      potionBonus = 3 + std::floor(0.10 * attackLevel);
      break;
    case POTIONS_E::SUPER_POTION:
      potionBonus = 5 + std::floor(0.15 * attackLevel);
      break;
    case POTIONS_E::OVERLOAD_MINUS:
      potionBonus = 4 + std::floor(0.10 * attackLevel);
      break;
    case POTIONS_E::OVERLOAD:
      potionBonus = 5 + std::floor(0.13 * attackLevel);
      break;
    case POTIONS_E::OVERLOAD_PLUS:
      potionBonus = 6 + std::floor(0.16 * attackLevel);
      break;
    case POTIONS_E::NONE:
    default:
      potionBonus = 0;
      break;
  }

  float prayerBonus = 1.0;
  switch (m_player.Prayer().AttackPrayer)
  {
    case ATTACK_PRAYER_E::CLARITY_OF_THOUGHT:
      prayerBonus = 1.05;
      break;
    case ATTACK_PRAYER_E::IMPROVED_REFLEXES:
      prayerBonus = 1.10;
      break;
    case ATTACK_PRAYER_E::INCREDIBLE_REFLEXES:
      prayerBonus = 1.15;
      break;
    case ATTACK_PRAYER_E::CHIVALRY:
      prayerBonus = 1.15;
      break;
    case ATTACK_PRAYER_E::PIETY:
      prayerBonus = 1.20;
      break;
    case ATTACK_PRAYER_E::NONE:
    default:
      prayerBonus = 1.0;
      break;
  }

  int stanceBonus = 8;

  Weapon w;
  if (m_isOneHanded)
  {
    w = m_oneHandedSlot;
  }
  else
  {
    w = m_twoHandedSlot;
  }

  STANCE_T s = w.WeaponStats().Stances[m_weaponStance];

  if (s.AttackStyle.compare("accurate") == 0)
  {
    stanceBonus = 11;
  }
  else if (s.AttackStyle.compare("controlled") == 0)
  {
    stanceBonus = 9;
  }

  float voidBonus = 1.0;

  if (m_headSlot.Id() == 11665 && // Void melee helm
     (m_bodySlot.Id() == 8839 || m_bodySlot.Id() == 13072) &&  // Void knight top or Elite void top
     (m_legsSlot.Id() == 8840 || m_legsSlot.Id() == 13073) &&  // Void knight robe or Elite void robe
      m_handSlot.Id() == 8842)    // Void knight gloves
  {
    voidBonus = 1.1;
  }

  int effectiveLevel = std::floor((std::floor((attackLevel + potionBonus) * prayerBonus) + stanceBonus) * voidBonus);
  return effectiveLevel;
}

void Setup::SetPlayer(Player i_player)
{
  m_player = i_player;
}
void Setup::SetMonster(Monster i_monster)
{
  m_monster = i_monster;
}

void Setup::SetAmmunition(Equipment i_ammo)
{
  m_ammoSlot = i_ammo;
}
void Setup::SetBody(Equipment i_body)
{
  m_bodySlot = i_body;
}
void Setup::SetCape(Equipment i_cape)
{
  m_capeSlot = i_cape;
}
void Setup::SetFeet(Equipment i_feet)
{
  m_feetSlot = i_feet;
}
void Setup::SetHand(Equipment i_hand)
{
  m_handSlot = i_hand;
}
void Setup::SetHead(Equipment i_head)
{
  m_headSlot = i_head;
}
void Setup::SetLegs(Equipment i_legs)
{
  m_legsSlot = i_legs;
}
void Setup::SetNeck(Equipment i_neck)
{
  m_neckSlot = i_neck;
}
void Setup::SetRing(Equipment i_ring)
{
  m_ringSlot = i_ring;
}
void Setup::SetShield(Equipment i_shield)
{
  m_shieldSlot = i_shield;
}

void Setup::SetOneHanded(Weapon i_oneHanded)
{
  m_oneHandedSlot = i_oneHanded;
  m_isOneHanded = true;
}
void Setup::SetTwoHanded(Weapon i_twoHanded)
{
  m_twoHandedSlot = i_twoHanded;
  m_isOneHanded = false;
}

void Setup::SetCurrentHitpoints(int i_currentHitpoints)
{
  m_currentHitpoints = i_currentHitpoints;
}

void Setup::SetOnTask(bool i_onSlayerTask)
{
  m_onSlayerTask = i_onSlayerTask;
}

void Setup::SetStance(int i_stance)
{
  m_weaponStance = i_stance;
}

const Player& Setup::GetPlayer() const
{
  return m_player;
}
const Monster& Setup::GetMonster() const
{
  return m_monster;
}

const Equipment& Setup::AmmoSlot() const
{
  return m_ammoSlot;
}
const Equipment& Setup::BodySlot() const
{
  return m_bodySlot;
}
const Equipment& Setup::CapeSlot() const
{
  return m_capeSlot;
}
const Equipment& Setup::FeetSlot() const
{
  return m_feetSlot;
}
const Equipment& Setup::HandSlot() const
{
  return m_handSlot;
}
const Equipment& Setup::HeadSlot() const
{
  return m_headSlot;
}
const Equipment& Setup::LegsSlot() const
{
  return m_legsSlot;
}
const Equipment& Setup::NeckSlot() const
{
  return m_neckSlot;
}
const Equipment& Setup::RingSlot() const
{
  return m_ringSlot;
}
const Equipment& Setup::ShieldSlot() const
{
  return m_shieldSlot;
}

const Weapon& Setup::OneHandedSlot() const
{
  return m_oneHandedSlot;
}
const Weapon& Setup::TwoHandedSlot() const
{
  return m_twoHandedSlot;
}

const int& Setup::CurrentHitpoints() const
{
  return m_currentHitpoints;
}

const bool& Setup::IsOnTask() const
{
  return m_onSlayerTask;
}