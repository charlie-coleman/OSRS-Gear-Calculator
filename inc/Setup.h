#ifndef SETUP_H
#define SETUP_H

#include "Equipment.h"
#include "Weapon.h"
#include "Monster.h"
#include "Player.h"
 
class Setup
{
public:
  Setup();

  Setup(Player i_player,      Monster i_monster,
        Equipment i_ammoSlot, Equipment i_bodySlot,   Equipment i_capeSlot,   Equipment i_feetSlot,
        Equipment i_handSlot, Equipment i_headSlot,   Equipment i_legsSlot,   Equipment i_neckSlot,
        Equipment i_ringSlot, Equipment i_shieldSlot, Weapon i_weapon);

  ~Setup();

  void SetPlayer(Player i_player);
  void SetMonster(Monster i_monster);
  void SetAmmunition(Equipment i_ammo);
  void SetBody(Equipment i_body);
  void SetCape(Equipment i_cape);
  void SetFeet(Equipment i_feet);
  void SetHand(Equipment i_hand);
  void SetHead(Equipment i_head);
  void SetLegs(Equipment i_legs);
  void SetNeck(Equipment i_neck);
  void SetRing(Equipment i_ring);
  void SetShield(Equipment i_shield);
  void SetWeapon(Weapon i_oneHanded);

  void SetOnTask(bool i_onSlayerTask);
  void SetStance(int i_stance);

  Player GetPlayer() const;
  Monster GetMonster() const;

  Equipment AmmoSlot() const;
  Equipment BodySlot() const;
  Equipment CapeSlot() const;
  Equipment FeetSlot() const;
  Equipment HandSlot() const;
  Equipment HeadSlot() const;
  Equipment LegsSlot() const;
  Equipment NeckSlot() const;
  Equipment RingSlot() const;
  Equipment ShieldSlot() const;
  Weapon WeaponSlot() const;

  void Recalculate();

  bool IsOnTask() const;
  int MaxDamage() const;
  float Accuracy() const;
  float DPS() const;

protected:
  void CalculateMaxHit();

  int CalculateMeleeMaxHit();
  int CalculateRangedMaxHit();
  int CalculateMagicMaxHit();

  float CalculateMeleeAccuracy();
  float CalculateRangedAccuracy();
  float CalculateMagicAccuracy();

  int CalculateEnemyMaxRoll();

  int CalculateEffectiveMeleeAttackLevel();
  int CalculateEffectiveMeleeStrength();

  int CalculateEffectiveRangedLevel();
  int CalculateEffectiveRangedStrength();

  Equipment m_ammoSlot,
            m_bodySlot,
            m_capeSlot,
            m_feetSlot,
            m_handSlot,
            m_headSlot,
            m_legsSlot,
            m_neckSlot,
            m_ringSlot,
            m_shieldSlot;

  Weapon    m_weaponSlot;

  int m_effectiveMeleeStrength, m_effectiveRangedStrength;
  int m_baseMeleeDamage, m_baseRangedDamage;

  bool m_onSlayerTask;

  int m_maxDamage;
  float m_accuracy, m_dps;

  int m_maxDamageRoll;
  float m_postDamageRollMultiplier;

  Monster m_monster;

  Player m_player;
};

#endif